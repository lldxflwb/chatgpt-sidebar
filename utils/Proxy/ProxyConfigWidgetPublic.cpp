//
// Created by 陈嘉乐 on 2023/8/6.
//

#include "ProxyConfigWidgetPublic.h"

extern QObject * globalWindow;

ProxyConfigWidgetPublic::ProxyConfigWidgetPublic(std::shared_ptr<ProxyConfig> proxyConfig) {
    this->proxyConfig = proxyConfig;
    this->autoConfigQt = proxyConfig->autoConfigQt;
    this->proxyConfig->proxyType;
    host = new LabelEditLine("Host", autoConfigQt->getItem("Host"), this,"填代理机器的ip地址");
    port = new LabelEditLine("Port", autoConfigQt->getItem("Port"), this,"填代理机器的端口号");
    username = new LabelEditLine("Username", autoConfigQt->getItem("Username"), this,"填代理机器的用户名，没有则为空");
    password = new LabelEditLine("Password", autoConfigQt->getItem("Password"), this,"填代理机器的密码，没有则为空");
    comboProxyType = new LabelComboBox(
            "Proxy Type",
            {
                {"None",ProxyConfig::ProxyType::None},
                {"Http",ProxyConfig::ProxyType::Http},
                {"Socks5",ProxyConfig::ProxyType::Socks5}
            },
            autoConfigQt->getItem("ProxyType")
            , this
            , "选择代理类型");
    layout = new QVBoxLayout(this);

    layout->addLayout(host);
    layout->addLayout(port);
    layout->addLayout(username);
    layout->addLayout(password);
    layout->addLayout(comboProxyType);
    this->setLayout(layout);
}
