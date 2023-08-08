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
        QString port;
        QString username;
        QString password;

        ProxyConfigHttp(QString host, QString port, QString username, QString password) {
            autoConfigQt = new AutoConfigQt("proxyHttp.ini");
            if(autoConfigQt->fileIsExist()){
                autoConfigQt->readFromFile();
                this->host = autoConfigQt->getItemAsQString("Host");
                this->port = autoConfigQt->getItemAsQString("Port");
                this->username = autoConfigQt->getItemAsQString("Username");
                this->password = autoConfigQt->getItemAsQString("Password");
                this->proxyType = static_cast<ProxyType>(std::get<int>(autoConfigQt->getItem("ProxyType")->getValue()));
            }
            else{
                ConfigValue chost = host.toStdString();
                autoConfigQt->addItems("Host", chost);
                this->host = host;
                ConfigValue cport = port.toStdString();
                autoConfigQt->addItems("Port", cport);
                this->port = port;
                ConfigValue cusername = username.toStdString();
                autoConfigQt->addItems("Username", cusername);
                this->username = username;
                ConfigValue cpassword = password.toStdString();
                autoConfigQt->addItems("Password", cpassword);
                this->password = password;
                ConfigValue cProxyType = static_cast<int>(ProxyType::Http);
                autoConfigQt->addItems("ProxyType", cProxyType);
                this->proxyType = ProxyType::Http;
                autoConfigQt->saveToFile();
            }
        }
    };

    void setProxy() override;
    ProxyActionHttp(std::shared_ptr<ProxyConfig> config) {
        this->proxyConfig = config;
    };

};


#endif //CHATGPT_SIDEBAR_PROXYACTIONHTTP_H
