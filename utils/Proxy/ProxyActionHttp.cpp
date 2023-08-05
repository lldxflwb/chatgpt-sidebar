//
// Created by 陈嘉乐 on 2023/8/6.
//

#include "ProxyActionHttp.h"
#include <QNetworkAccessManager>
#include <QNetworkProxy>

void ProxyActionHttp::setProxy() {
    // 设置代理
    QNetworkProxy proxy;
    auto proxyConfig = std::dynamic_pointer_cast<ProxyConfigHttp>(this->proxyConfig);
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName(proxyConfig->host);
    proxy.setPort(proxyConfig->port);
    proxy.setUser(proxyConfig->username);
    proxy.setPassword(proxyConfig->password);
    QNetworkProxy::setApplicationProxy(proxy);
    qDebug() << "代理初始化";
}

