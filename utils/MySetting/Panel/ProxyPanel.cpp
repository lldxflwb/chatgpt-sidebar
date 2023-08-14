//
// Created by 陈嘉乐 on 2023/8/14.
//

#include <QNetworkAccessManager>
#include "ProxyPanel.h"
#include "utils/MySetting/Proxy/ProxyHttp.h"
#include "utils/MySetting/Proxy/ProxySocks5.h"

extern AutoConfig::StoragePolicy storagePolicy;
extern QNetworkAccessManager * networkManager;
AutoConfig * pannelConfig;

ProxyPanel::ProxyPanel(
        ProxyType proxyType,
        QWidget *parent,
const Qt::WindowFlags &f)
        : ConfigQWidget(new AutoConfigQt("ProxyPanel.json",storagePolicy), parent, f){
    networkManager = new QNetworkAccessManager(this);
    this->layout = new QVBoxLayout(this);
    auto proxyTypeItem = autoConfigQt->addItems("proxyType",proxyType);
    this->proxyType = new LabelComboBox("代理类型",
                                        {
                                                {"无",ProxyType::None},
                                                {"HTTP",ProxyType::HTTP},
                                                {"Socks5",ProxyType::SOCKS5}
                                        },proxyTypeItem,this,
                                        "请选择你的代理类型");
    auto defaultGptProxyItem = autoConfigQt->addItems("defaultGptProxy",ProxyType::HTTP);
    this->defaultGptProxy = new LabelComboBox("默认Gpt代理类型",
                                              {
                                                      {"无",ProxyType::None},
                                                      {"HTTP",ProxyType::HTTP},
                                                      {"Socks5",ProxyType::SOCKS5}
                                              },defaultGptProxyItem,this,
                                              "请选择你的默认Gpt代理类型");
    this->proxyMap[ProxyType::None] = nullptr;
    auto proxyHttp = new ProxyHttp();
    this->proxyMap[ProxyType::HTTP] = proxyHttp;
    auto proxySocks5 = new ProxySocks5();
    this->proxyMap[ProxyType::SOCKS5] = proxySocks5;
    this->widgetMap[ProxyType::None] = nullptr;
    this->widgetMap[ProxyType::HTTP] = proxyHttp;
    this->widgetMap[ProxyType::SOCKS5] = proxySocks5;
    proxySocks5->RegisterFatherConfig(autoConfigQt);
    proxyHttp->RegisterFatherConfig(autoConfigQt);
    this->currentProxyType = proxyType;
    this->currentProxy = this->proxyMap[proxyType];
    QHBoxLayout * hLayout = new QHBoxLayout(this);
    hLayout->addLayout(this->proxyType);
    hLayout->addLayout(this->defaultGptProxy);
    this->layout->addLayout(hLayout);
    this->layout->addWidget(proxySocks5);
    this->layout->addWidget(proxyHttp);
    this->setLayout(this->layout);
    this->proxyType->value->addObserver([this](const ConfigValue& value){
        this->OnProxyTypeChange((ProxyType)std::get<int>(value));
    });
    pannelConfig = autoConfigQt;
}
void ProxyPanel::OnProxyTypeChange(ProxyType proxyType){
    qDebug() << "OnProxyTypeChange" << proxyType;
    if(this->currentProxyType != ProxyType::None){
        this->currentProxy->OnEnd();
        this->widgetMap[this->currentProxyType]->hide();
    }
    this->currentProxyType = proxyType;
    this->currentProxy = this->proxyMap[proxyType];
    if(ProxyType::None != proxyType){
        this->currentProxy->OnStart();
        this->widgetMap[proxyType]->show();
    }
}