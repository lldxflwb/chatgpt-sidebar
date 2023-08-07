//
// Created by 陈嘉乐 on 2023/8/6.
//

#ifndef CHATGPT_SIDEBAR_PROXYCONFIGWIDGETPUBLIC_H
#define CHATGPT_SIDEBAR_PROXYCONFIGWIDGETPUBLIC_H

#include <QWidget>
#include <QLabel>
#include "ProxyConfig.h"
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include "utils/Ui/Layout/LabelEditLine.h"
#include "utils/Ui/Layout/LabelComboBox.h"

class ProxyConfigWidgetPublic : public QWidget {
protected:
    std::shared_ptr<ProxyConfig> proxyConfig;
    QVBoxLayout * layout;
    LabelEditLine * host, * port, * username, * password;
    LabelComboBox * comboProxyType;
public:
    ProxyConfigWidgetPublic(std::shared_ptr<ProxyConfig> proxyConfig);
};


#endif //CHATGPT_SIDEBAR_PROXYCONFIGWIDGETPUBLIC_H
