//
// Created by 陈嘉乐 on 2023/8/13.
//

#include "BaiduEngine.h"
#include <QNetworkRequest>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include "utils/AutoConfig/AutoConfig.h"
#include <QDebug>
#include <QUrlQuery>

extern AutoConfig * baiduConfig;
extern QNetworkAccessManager * networkManager;
extern QWidget * aiNetwork;

void BaiduEngine::getAccessToken(const QString &api_key, const QString &secret_key) {
    this->access_token="24.cfa334a87b2af287f572753f6aa8a52c.2592000.1694508340.282335-37513416";
    baiduConfig->getItem("token")->setString(this->access_token.toStdString());
//    QUrl url("https://aip.baidubce.com/oauth/2.0/token");
//    QUrlQuery query;
//    query.addQueryItem("grant_type", "client_credentials");
//    query.addQueryItem("client_id", api_key);
//    query.addQueryItem("client_secret", secret_key);
//    url.setQuery(query);
//
//    QNetworkRequest request(url);
//    QNetworkReply *reply = networkManager->get(request);
//
//    connect(reply, &QNetworkReply::finished, [this, reply]() {
//        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
//        this->access_token = jsonObject["access_token"].toString();
//        reply->deleteLater();
//    });
}

void BaiduEngine::OnInput(const QString &input) {
    this->Notify("",ApiStatus::start);
    getAccessToken("","");
    QUrl url("https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions");
    QUrlQuery query;
    query.addQueryItem("access_token", access_token);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonBody;
    QJsonArray messages;
    QJsonObject message;
    message["role"] = "user";
    message["content"] = input;
    messages.append(message);
    jsonBody["messages"] = messages;
    jsonBody["stream"] = true;
    QByteArray jsonString = QJsonDocument(jsonBody).toJson();

    QNetworkReply *reply = networkManager->post(request, jsonString);

    QAbstractSocket::connect(
            reply,
            &QNetworkReply::readyRead,
            aiNetwork,
            [this, reply]() {
        // 解析响应，并根据需要处理结果
        // 您可以根据百度流式接口的响应格式进行解析
        QByteArray data = reply->readAll();
        QTextStream stream(data);

        // 解析数据字段
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            if (line.startsWith("data:")) {
                QString jsonStr = line.mid(5);

                // 将 JSON 字符串转换为 QJsonDocument
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

                // 如果 JSON 文档不为空且不是空对象，则进行解析
                if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                    QJsonObject jsonObject = jsonDoc.object();

                    // 解析响应中的字段
                    QString result = jsonObject["result"].toString();

                    // 通知订阅者结果
                    this->Notify(result, ApiStatus::sending);
                }
            }
        }
    });
}

void BaiduEngine::OnStop() {
    // 停止会话的代码实现
}
