//
// Created by 陈嘉乐 on 2023/8/14.
//

#ifndef CHATGPT_SIDEBAR_PROXYSOCKS5_H
#define CHATGPT_SIDEBAR_PROXYSOCKS5_H

#include "utils/MySetting/ConfigQWidget.h"
#include "utils/Ui/layout/UiImport.h"
#include "ProxyInterface.h"
class ProxySocks5 :public ConfigQWidget,public ProxyInterface{
public:
    LabelEditLine * ip;
    LabelEditLine * port;
    LabelEditLine * username;
    LabelEditLine * password;
    QVBoxLayout * layout;
    SubscriberId OnProxySubscriberId = -1 ;
    ProxySocks5(
            QString ip = "" ,
            int port = 7890 ,
            QString username = "" ,
            QString password = "" ,
            QWidget *parent = nullptr,
            const Qt::WindowFlags &f = Qt::WindowFlags ());

    void OnProxy() override;

    void OnStart() override;

    void OnEnd() override;
};


#endif //CHATGPT_SIDEBAR_PROXYSOCKS5_H
