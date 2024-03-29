//
// Created by 陈嘉乐 on 2023/8/14.
//

#include "ProxySocks5.h"

extern AutoConfig::StoragePolicy storagePolicy;
AutoConfigQt * socks5Config ;
ProxySocks5::ProxySocks5(QString ip, int port, QString username, QString password, QWidget *parent,
                         const Qt::WindowFlags &f) :
        ConfigQWidget(new AutoConfigQt("Socks5.json",storagePolicy), parent, f) {
    this->layout = new QVBoxLayout(this);
    auto * ipItem = autoConfigQt->addQString("ip",ip);
    this->ip = new LabelEditLine("ip",ipItem,this,"请填入主机地址");
    auto * portItem = autoConfigQt->addQString("port",
                                               QString::fromStdString(std::to_string(port)));
    this->port = new LabelEditLine("port",portItem,this,"请填入端口");
    auto * usernameItem = autoConfigQt->addQString("username",username);
    this->username = new LabelEditLine("username",usernameItem,this,"请填入用户名");
    auto * passwordItem = autoConfigQt->addQString("password",password);
    this->password = new LabelEditLine("password",passwordItem,this,"请填入密码");
    layout->addLayout(this->ip);
    layout->addLayout(this->port);
    layout->addLayout(this->username);
    layout->addLayout(this->password);
    socks5Config = this->autoConfigQt;
}

void ProxySocks5::OnProxy() {
    UnUseProxy();
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName(autoConfigQt->getItemAsQString("ip"));
    proxy.setPort(autoConfigQt->getItemAsQString("port").toInt());
    proxy.setUser(autoConfigQt->getItemAsQString("username"));
    proxy.setPassword(autoConfigQt->getItemAsQString("password"));
    UseProxy(proxy);
}

void ProxySocks5::OnStart() {
    this->OnProxySubscriberId = autoConfigQt->RegisterObserver(
            [this](const AutoConfig& config, ConfigEvent event) {
        if(ConfigEvent::EventItemValueChange == event){
            this->OnProxy();
        }
    });
    this->OnProxy();
}

void ProxySocks5::OnEnd() {
    if (this->OnProxySubscriberId == -1)
    {
        return;
    }
    autoConfigQt->RemoveObserver(this->OnProxySubscriberId);
    this->OnProxySubscriberId = -1;
}
