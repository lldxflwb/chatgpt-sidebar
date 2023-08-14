//
// Created by 陈嘉乐 on 2023/8/14.
//

#include "ProxyHttp.h"

extern AutoConfig::StoragePolicy storagePolicy;
AutoConfigQt * httpConfig ;

ProxyHttp::ProxyHttp(QString ip, int port ,
        QString username ,QString password ,
        QWidget *parent , const Qt::WindowFlags &f )
        : ConfigQWidget(new AutoConfigQt("Http.json",storagePolicy), parent, f)
{
    layout = new QVBoxLayout(this);
    auto * ipItem = autoConfigQt->addQString("ip",ip);
    this->ip = new LabelEditLine("ip",ipItem,this,"请填入主机地址");
    auto portString = QString::fromStdString(std::to_string(port));
    auto * portItem = autoConfigQt->addQString("port",portString);
    this->port = new LabelEditLine("port",portItem,this,"请填入端口");
    auto * usernameItem = autoConfigQt->addQString("username",username);
    this->username = new LabelEditLine("username",usernameItem,this,"请填入用户名");
    auto * passwordItem = autoConfigQt->addQString("password",password);
    this->password = new LabelEditLine("password",passwordItem,this,"请填入密码");
    layout->addLayout(this->ip);
    layout->addLayout(this->port);
    layout->addLayout(this->username);
    layout->addLayout(this->password);
    httpConfig = this->autoConfigQt;
}

void ProxyHttp::OnProxy() {
    UnUseProxy();
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName(autoConfigQt->getItemAsQString("ip"));
    proxy.setPort(autoConfigQt->getItemAsQString("port").toInt());
    proxy.setUser(autoConfigQt->getItemAsQString("username"));
    proxy.setPassword(autoConfigQt->getItemAsQString("password"));
    UseProxy(proxy);
}

void ProxyHttp::OnStart() {
    this->OnProxySubscriberId = autoConfigQt->RegisterObserver(
            [this](const AutoConfig& config, ConfigEvent event) {
        if(ConfigEvent::EventItemValueChange == event){
            this->OnProxy();
        }
    });
    this->OnProxy();
}

void ProxyHttp::OnEnd() {
    if (this->OnProxySubscriberId == -1)
    {
        return;
    }
    autoConfigQt->RemoveObserver(this->OnProxySubscriberId);
    this->OnProxySubscriberId = -1;
}
