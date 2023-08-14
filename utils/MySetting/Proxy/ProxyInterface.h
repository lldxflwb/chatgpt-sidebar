//
// Created by 陈嘉乐 on 2023/8/15.
//

#ifndef CHATGPT_SIDEBAR_PROXYINTERFACE_H
#define CHATGPT_SIDEBAR_PROXYINTERFACE_H

#include <QNetworkProxy>

class ProxyInterface{
public:
    ProxyInterface() {}

    virtual ~ProxyInterface() {

    }

    void UseProxy(QNetworkProxy proxy){
        QNetworkProxy::setApplicationProxy(proxy);
    }
    void UnUseProxy(){
        QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
    }
    virtual void OnProxy() = 0;
    virtual void OnStart() = 0;
    virtual void OnEnd() = 0;
};

#endif //CHATGPT_SIDEBAR_PROXYINTERFACE_H
