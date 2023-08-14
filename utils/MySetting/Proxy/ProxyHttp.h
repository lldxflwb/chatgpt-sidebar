//
// Created by 陈嘉乐 on 2023/8/14.
//

#ifndef CHATGPT_SIDEBAR_PROXYHTTP_H
#define CHATGPT_SIDEBAR_PROXYHTTP_H

#include "utils/MySetting/ConfigQWidget.h"
#include "utils/Ui/layout/UiImport.h"

class ProxyHttp : public ConfigQWidget{
public:
    LabelEditLine * ip;
    LabelEditLine * port;
    LabelEditLine * username;
    LabelEditLine * password;
    QVBoxLayout * layout;
    ProxyHttp(QString ip = "127.0.0.1", int port = 7890,
              QString username = "",QString password = "",
              QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags());
};


#endif //CHATGPT_SIDEBAR_PROXYHTTP_H
