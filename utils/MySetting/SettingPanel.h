//
// Created by 陈嘉乐 on 2023/8/15.
//

#ifndef CHATGPT_SIDEBAR_SETTINGPANEL_H
#define CHATGPT_SIDEBAR_SETTINGPANEL_H

#include "ConfigQWidget.h"
#include "QVBoxLayout"
#include "utils/MySetting/Panel/EnginePanel.h"
#include "utils/MySetting/Panel/ProxyPanel.h"

class SettingPanel : public ConfigQWidget{
public:
    SettingPanel(QWidget *parent = nullptr);
    QVBoxLayout * layout;
    EnginePanel * engine_panel;
    ProxyPanel * proxy_panel;
    // 单例模式
    static SettingPanel * GetInstance(){
        static SettingPanel * instance = nullptr;
        if(instance == nullptr){
            instance = new SettingPanel();
        }
        return instance;
    }
};


#endif //CHATGPT_SIDEBAR_SETTINGPANEL_H
