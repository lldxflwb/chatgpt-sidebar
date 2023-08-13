//
// Created by 陈嘉乐 on 2023/8/6.
//

#include "ProxyAction.h"
#include <QNetworkAccessManager>
#include <QNetworkProxy>

void ProxyAction::uninstallProxy() {
    // uninstall proxy
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::NoProxy);
    QNetworkProxy::setApplicationProxy(proxy);
    qDebug() << "代理卸载";
}

void ProxyAction::setProxy() {
}
