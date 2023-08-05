//
// Created by 陈嘉乐 on 2023/8/6.
//

#ifndef CHATGPT_SIDEBAR_PROXYACTION_H
#define CHATGPT_SIDEBAR_PROXYACTION_H

#include "ProxyConfig.h"
#include <memory>

// 代理设置的基础类
class ProxyAction {
public:
    // attributes
    std::shared_ptr<ProxyConfig> proxyConfig;
    // generated implementation
    ProxyAction(std::shared_ptr<ProxyConfig> proxyConfig):proxyConfig(proxyConfig){
        setProxy();
    };
    // zero param
    ProxyAction()=default;
    // virtual destruct
    virtual ~ProxyAction(){
        uninstallProxy();
    }
    virtual void setProxyConfig(std::shared_ptr<ProxyConfig> proxyConfig){
        this->proxyConfig = proxyConfig;
    }
    virtual void setProxy();
    virtual void uninstallProxy();
};


#endif //CHATGPT_SIDEBAR_PROXYACTION_H
