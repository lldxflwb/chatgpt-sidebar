//
// Created by 48449 on 2023/4/15.
//

#include "DealChatGpt.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkReply>
#include <QJsonArray>
DealChatGpt::DealChatGpt() {

}

void DealChatGpt::TalkWithGpt(QString text, QTextEdit *out) {
    fetchAnswerFromGPT3(text);
}

void DealChatGpt::setupNetworkManager(QObject *parent ) {
    networkManager = new QNetworkAccessManager(parent);

    // 设置代理
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName(m_setting->value("ip").toString());
    proxy.setPort(m_setting->value("port").toString().toInt());
    QNetworkProxy::setApplicationProxy(proxy);
    qDebug() << "代理初始化";
}

