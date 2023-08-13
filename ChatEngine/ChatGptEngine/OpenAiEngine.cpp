//
// Created by 陈嘉乐 on 2023/8/12.
//

#include "OpenAiEngine.h"
#include <QNetworkRequest>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include "utils/AutoConfig/AutoConfig.h"
#include <QDebug>
extern AutoConfig * chatGptConfig;
extern QNetworkAccessManager * networkManager;
extern QWidget * aiNetwork;
void OpenAiEngine::OnInput(const QString &input) {
    QUrl url("https://api.openai.com/v1/chat/completions");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto keyValue = chatGptConfig->getItem("key")->getValue();
    auto key = "Bearer " + std::get<std::string>(keyValue);
    request.setRawHeader("Authorization", QString::fromStdString(key).toUtf8());
    QJsonObject jsonBody;
    jsonBody["model"] = "gpt-3.5-turbo";
    QJsonArray messages;
    QJsonObject message;
    message["role"] = "user";
    message["content"] = input;
    messages.append(message);
    jsonBody["messages"] = messages;
    jsonBody["stream"] = true;
    QByteArray jsonString = QJsonDocument(jsonBody).toJson();
    // 转换为 QObject* 类型
    const QObject *receiver = aiNetwork;
    QNetworkReply *reply = networkManager->post(request, jsonString);
    QAbstractSocket::connect(reply, &QNetworkReply::readyRead, aiNetwork, [this,reply](){
//        QNetworkReply *reply = qobject_cast<QNetworkReply *>(aiNetwork);

        // 检查网络错误
        if (reply->error() != QNetworkReply::NoError) {
//            QMessageBox::critical(this, "发生错误", "网络错误", QMessageBox::Discard);
            qDebug() << "Error:" << reply->errorString();
            return;
        }

        // 读取响应数据
        QByteArray data = reply->readAll();
        {
            // 将 JSON 字符串转换为 QJsonDocument
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

            // 如果 JSON 文档不为空且不是空对象，则进行解析
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();

                // 检查是否存在 error 对象
                if (jsonObject.contains("error")) {
                    QJsonObject errorObject = jsonObject["error"].toObject();
                    QString errorMessage = errorObject["message"].toString();
                    QString errorType = errorObject["type"].toString();

                    // 在此处处理错误消息和错误类型，例如显示在消息框中
//                    QMessageBox::critical(this, , errorMessage, QMessageBox::Close);
                } else {
//                qDebug() <<"未包含error";
//                QMessageBox::critical(this, tr("发生错误"), tr("未处理"), QMessageBox::Close);
                }
            } else {
//            qDebug() << "序列化失败";
//            QMessageBox::critical(this, tr("发生错误"), tr("消息序列化失败"), QMessageBox::Close);
            }
        }
        qDebug() << "111";
        QTextStream stream(data);
// 解析数据字段
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            qDebug() << "line:" << line;
            if (line.startsWith("data:")) {
                QString jsonStr = line.mid(5);
//            qDebug() << "one line:" << jsonStr;

                // 将 JSON 字符串转换为 QJsonDocument
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

                // 如果 JSON 文档不为空且不是空对象，则进行解析
                if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                    QJsonObject jsonObject = jsonDoc.object();

                    QString id = jsonObject["id"].toString();
                    QString object = jsonObject["object"].toString();
                    qint64 created = jsonObject["created"].toDouble();
                    QString model = jsonObject["model"].toString();

                    QJsonArray choicesArray = jsonObject["choices"].toArray();

                    // 遍历 choices 数组
                    for (int i = 0; i < choicesArray.size(); ++i) {
                        QJsonObject choiceObject = choicesArray[i].toObject();

                        QJsonObject deltaObject = choiceObject["delta"].toObject();
                        QString role = deltaObject["role"].toString();
                        QString content = deltaObject["content"].toString();

                        int index = choiceObject["index"].toInt();
                        QString finishReason = choiceObject["finish_reason"].toString();
                        this->Notify(content,ApiStatus::sending);
                        qDebug() << content;
                    }
                }
            } else if (line == "") {
                continue;
            } else {

            }
        }
    });
}

void OpenAiEngine::OnStop() {

}
