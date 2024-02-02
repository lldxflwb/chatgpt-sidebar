//
// Created by lldx on 2024/2/2.
//

#include "ZhiPuEngine.h"
#include <QNetworkRequest>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include "utils/AutoConfig/AutoConfig.h"
#include <QDebug>
#include <QUrlQuery>
#include <QMessageAuthenticationCode>
#include "jwt-cpp/jwt.h"

extern AutoConfig * zhipuConfig;
extern QNetworkAccessManager * networkManager;
extern QWidget * aiNetwork;
void ZhiPuEngine::OnStop() {

}
QString base64UrlEncode(const QByteArray &data) {
    QString base64 = data.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
    return base64;
}

QByteArray hmacSha256(const QByteArray &key, const QByteArray &data) {
    return QMessageAuthenticationCode::hash(data, key, QCryptographicHash::Sha256);
}

QString generateJwtToken(const QString &apiKey, int expSeconds,QJsonObject & payloadObj,QByteArray &payloadEncoded ) {
    QStringList parts = apiKey.split('.');
    if (parts.length() != 2) {
        qDebug() << "API key format is invalid";
        return "";
    }
    QString id = parts[0];
    QString secret = parts[1];

    // Header
    QJsonObject headerObj{{"alg", "HS256"}, {"sign_type", "SIGN"}};
    QByteArray headerEncoded = base64UrlEncode(QJsonDocument(headerObj).toJson(QJsonDocument::Compact)).toUtf8();

    // Payload
    qint64 currentTimeMs = QDateTime::currentMSecsSinceEpoch();
    payloadObj["api_key"] = id;
    payloadObj["exp"] = currentTimeMs + static_cast<qint64>(expSeconds) * 1000;
    payloadObj["timestamp"] = currentTimeMs;

    payloadEncoded = base64UrlEncode(QJsonDocument(payloadObj).toJson(QJsonDocument::Compact)).toUtf8();

    // Signature
    QByteArray toSign = headerEncoded + "." + payloadEncoded;
    QByteArray signature = hmacSha256(secret.toUtf8(), toSign);
    QString signatureEncoded = base64UrlEncode(signature);

    // Assemble JWT
    QString jwt = headerEncoded + "." + payloadEncoded + "." + signatureEncoded;
    return jwt;
}
#include <QString>
#include <QDateTime>
#include <jwt-cpp/jwt.h>

std::string generate_token(const QString& apikey, int exp_seconds) {
    // 将QString转换为std::string
    auto apikey_std = apikey.toStdString();
    size_t pos = apikey_std.find(".");
    if(pos == std::string::npos) {
        throw std::runtime_error("invalid apikey");
    }

    std::string id = apikey_std.substr(0, pos);
    std::string secret = apikey_std.substr(pos + 1);

    // 构造payload
    auto now = std::chrono::system_clock::now();
    auto exp = now + std::chrono::seconds(exp_seconds);
    // real use is in milliseconds , in string
    auto now_ms = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());
    auto exp_ms = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(exp.time_since_epoch()).count());
    // 生成并返回JWT令牌
    std::string alg = "HS256";
    std::string sign_type = "SIGN";
    auto token = jwt::create()
            .set_payload_claim("api_key", jwt::claim(id))
            .set_payload_claim("exp", jwt::claim(exp_ms))
            .set_payload_claim("timestamp", jwt::claim(now_ms))
            .set_issued_at(std::chrono::system_clock::now()) // 签发时间
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds(3600)) // 过期时间
            .set_header_claim("alg", jwt::claim(alg))
            .set_header_claim("sign_type", jwt::claim(sign_type))
            .sign(jwt::algorithm::hs256{secret});
    return token;
}

void ZhiPuEngine::OnInput(const QString &input) {
    this->Notify("",ApiStatus::start);
    QUrl url("https://open.bigmodel.cn/api/paas/v4/chat/completions");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto keyValue = zhipuConfig->getItem("api_key")->getValue();
    auto key = "Bearer " + std::get<std::string>(keyValue);

    QJsonObject jsonBody;
    jsonBody["model"] = "glm-4";
    QJsonArray messages;
    QJsonObject message;
    message["role"] = "user";
    message["content"] = input;
    messages.append(message);
    jsonBody["messages"] = messages;
    jsonBody["stream"] = true;
    // json to string
    QJsonDocument jsonDoc(jsonBody);
    QByteArray payloadEncoded = jsonDoc.toJson(QJsonDocument::Compact);
//    auto token = generateJwtToken(QString::fromStdString(key).toUtf8(), 3600,jsonBody,payloadEncoded);
    qDebug() << "payloadEncoded" << payloadEncoded;
    auto token = key;
    // log token
    qDebug() << token;
    // set header
    request.setRawHeader("Authorization", QString::fromStdString(token).toUtf8());
//    {“alg”:“HS256”,“sign_type”:“SIGN”}
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("alg", "HS256");
    request.setRawHeader("sign_type", "SIGN");

    QNetworkReply *reply = networkManager->post(request,  payloadEncoded);

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
                    // debug info
                    qDebug() << line;
                    if (line.startsWith("data:")) {
                        QString jsonStr = line.mid(5);

                        // 将 JSON 字符串转换为 QJsonDocument
                        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

                        // 如果 JSON 文档不为空且不是空对象，则进行解析
                        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                            QJsonObject jsonObject = jsonDoc.object();
                            QJsonArray array =jsonObject["choices"].toArray();
                            QString result = array[0].toObject()["delta"].toObject()["content"].toString();
                            // 解析响应中的字段
//                            QString result = jsonObject["choices"].toString();

                            // 通知订阅者结果
                            this->Notify(result, ApiStatus::sending);
                        }
                    }
                }
            });
}
