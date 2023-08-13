//
// Created by 陈嘉乐 on 2023/8/6.
//

#ifndef CHATGPT_SIDEBAR_PROXYACTIONSOCKS5_H
#define CHATGPT_SIDEBAR_PROXYACTIONSOCKS5_H

#include "ProxyAction.h"
#include <QString>

class ProxyActionSocks5 : public ProxyAction{
public:
    class ProxyConfigSocks5 : public ProxyConfig{
    public:
        QString host;
        int port;
        QString username;
        QString password;
        ProxyConfigSocks5(QString host, int port, QString username, QString password) {
            this->host = host;
            this->port = port;
            this->username = username;
            this->password = password;
            this->proxyType = ProxyType::Socks5;
        }
    };

    void setProxy() override;
    ProxyActionSocks5(std::shared_ptr<ProxyConfig> config) : ProxyAction(config) {};
};


#endif //CHATGPT_SIDEBAR_PROXYACTIONSOCKS5_H
