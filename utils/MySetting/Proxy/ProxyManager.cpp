//
// Created by 陈嘉乐 on 2023/8/6.
//

#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include "ProxyManager.h"
#include "ProxyActionHttp.h"
#include "ProxyActionSocks5.h"

extern QNetworkAccessManager * networkManager;

ProxyManager * proxyManager;

void ProxyManager::SetProxy() {
    if(proxyAction != nullptr){
        delete proxyAction;
    }
    switch(proxyType) {
        case ProxyConfig::ProxyType::Http:
            proxyAction = new ProxyActionHttp(proxyConfig);
            break;
        case ProxyConfig::ProxyType::Socks5:
            proxyAction = new ProxyActionSocks5(proxyConfig);
            break;
        default:
            break;
    }
    if (proxyAction == nullptr){
        this->UninstallProxy();
        return;
    }
    proxyAction->setProxy();
}

void ProxyManager::UninstallProxy() {
    // uninstall proxy
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::NoProxy);
    QNetworkProxy::setApplicationProxy(proxy);
    qDebug() << "代理卸载";
}

void ProxyManager::SetProxyConfig(std::shared_ptr<ProxyConfig> config) {
    proxyConfig = config;
    proxyType = config->proxyType;
    SetProxy();
}

void ProxyManager::SetHttpProxy(QString ip, int port, QString username, QString password) {
    auto proxyConfig = std::make_shared<ProxyActionHttp::ProxyConfigHttp>
            (ip,QString::fromStdString(std::to_string(port)),username,password);
    SetProxyConfig(proxyConfig);
}

void ProxyManager::SetSocks5Proxy(QString ip, int port, QString username, QString password) {
    auto proxyConfig = std::make_shared<ProxyActionSocks5::ProxyConfigSocks5>
            (ip,port,username,password);
    SetProxyConfig(proxyConfig);

}

void ProxyManager::init() {
    networkManager = new QNetworkAccessManager();
}
