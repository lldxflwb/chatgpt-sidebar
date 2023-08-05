//
// Created by 陈嘉乐 on 2023/8/6.
//

#ifndef CHATGPT_SIDEBAR_PROXYACTIONHTTP_H
#define CHATGPT_SIDEBAR_PROXYACTIONHTTP_H

#include "ProxyAction.h"
#include <QString>
#include <memory>

class ProxyActionHttp : public ProxyAction{
public:
    class ProxyConfigHttp : public ProxyConfig{
    public:
        QString host;
        int port;
        QString username;
        QString password;
        ProxyConfigHttp(QString host, int port, QString username, QString password) {
            this->host = host;
            this->port = port;
            this->username = username;
            this->password = password;
            this->proxyType = ProxyType::Http;
        }
    };

    void setProxy() override;
    ProxyActionHttp(std::shared_ptr<ProxyConfig> config) {
        this->proxyConfig = config;
    };

};


#endif //CHATGPT_SIDEBAR_PROXYACTIONHTTP_H
