//
// Created by 陈嘉乐 on 2023/8/14.
//

#ifndef CHATGPT_SIDEBAR_PROXYPANEL_H
#define CHATGPT_SIDEBAR_PROXYPANEL_H

#include "utils/MySetting/ConfigQWidget.h"
#include "utils/Ui/layout/UiImport.h"
#include "utils/MySetting/Proxy/ProxyInterface.h"
enum ProxyType{
    None,
    HTTP,
    SOCKS5,
};
class ProxyPanel : public ConfigQWidget{
public:
    QVBoxLayout * layout;
    LabelComboBox * proxyType,*defaultGptProxy;
    ProxyInterface * currentProxy;
    ProxyType currentProxyType;
    std::map<ProxyType,ProxyInterface*> proxyMap;
    std::map<ProxyType,ConfigQWidget*> widgetMap;
    ProxyPanel(
            ProxyType proxyType = ProxyType::None,
            QWidget *parent = nullptr,
            const Qt::WindowFlags &f = Qt::WindowFlags ());
    void OnProxyTypeChange(ProxyType proxyType);
    // 单例模式
    static ProxyPanel * GetInstance(){
        static ProxyPanel * proxyPanel = nullptr;
        if(proxyPanel == nullptr){
            proxyPanel = new ProxyPanel();
        }
        return proxyPanel;
    }
};


#endif //CHATGPT_SIDEBAR_PROXYPANEL_H
