//
// Created by 陈嘉乐 on 2023/8/6.
//

#ifndef CHATGPT_SIDEBAR_PROXYCONFIG_H
#define CHATGPT_SIDEBAR_PROXYCONFIG_H

// 代理配置类 基础类
class ProxyConfig {
public:
    // 支持的类型
    enum ProxyType {
        None,
        Http,
        Socks5,
        Socks5H,
        Socks4,
        Socks4A,
        Socks4H,
        Socks4AH,
        Unknown
    };
    // virtual destruct
    virtual ~ProxyConfig() = default;
    ProxyType proxyType;
};


#endif //CHATGPT_SIDEBAR_PROXYCONFIG_H
