//
// Created by 陈嘉乐 on 2023/8/6.
//

#ifndef CHATGPT_SIDEBAR_PROXYMANAGER_H
#define CHATGPT_SIDEBAR_PROXYMANAGER_H

#include "ProxyActionHttp.h"
#include "ProxyActionSocks5.h"

class ProxyManager {
    ProxyConfig::ProxyType proxyType;
    std::shared_ptr<ProxyConfig> proxyConfig;
    ProxyAction * proxyAction;
public:
    ProxyManager()
    {
      proxyType = ProxyConfig::ProxyType::None;
      init();
    };
    void init();
    void SetProxy();
    void UninstallProxy();
    void SetProxyConfig(std::shared_ptr<ProxyConfig> config);
    void SetHttpProxy(QString ip, int port,QString username = "",QString password = "");
    void SetSocks5Proxy(QString ip, int port,QString username = "",QString password = "");
};


#endif //CHATGPT_SIDEBAR_PROXYMANAGER_H
