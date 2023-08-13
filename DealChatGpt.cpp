//
// Created by 48449 on 2023/4/15.
//

#include "DealChatGpt.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkReply>
#include <QJsonArray>
#include "utils/MySetting/Proxy/ProxyManager.h"

extern ProxyManager * proxyManager;

QNetworkAccessManager * networkManager;

DealChatGpt::DealChatGpt() {

}

void DealChatGpt::TalkWithGpt(QString text, QTextEdit *out) {
    fetchAnswerFromGPT3(text);
}

void DealChatGpt::setupNetworkManager(QObject *parent ) {
    proxyManager->SetSocks5Proxy(
            m_setting->value("ip").toString(),
            m_setting->value("port").toString().toInt());
}

void DealChatGpt::OnSettingChanged(QSettings *settings) {
    proxyManager->SetSocks5Proxy(
            m_setting->value("ip").toString(),
            m_setting->value("port").toString().toInt());
}

