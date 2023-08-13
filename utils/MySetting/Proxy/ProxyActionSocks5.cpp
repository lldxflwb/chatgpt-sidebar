//
// Created by 陈嘉乐 on 2023/8/6.
//

#include "ProxyActionSocks5.h"
#include <QNetworkAccessManager>
#include <QNetworkProxy>

void ProxyActionSocks5::setProxy() {
    // 设置代理
    QNetworkProxy proxy;
    auto proxyConfig = std::dynamic_pointer_cast<ProxyConfigSocks5>(this->proxyConfig);
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName(proxyConfig->host);
    proxy.setPort(proxyConfig->port);
    proxy.setUser(proxyConfig->username);
    proxy.setPassword(proxyConfig->password);
    QNetworkProxy::setApplicationProxy(proxy);
    qDebug() << "代理初始化";
}

