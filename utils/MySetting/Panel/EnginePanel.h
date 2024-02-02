//
// Created by 陈嘉乐 on 2023/8/13.
//

#ifndef CHATGPT_SIDEBAR_ENGINEPANEL_H
#define CHATGPT_SIDEBAR_ENGINEPANEL_H

#include "utils/MySetting/KeyInfo/BaiduKey.h"
#include "utils/Ui/Layout/labelComboBox.h"
#include "utils/MySetting/KeyInfo/ChatGptKey.h"
#include "ChatEngine/ChatInterface.h"
#include "ProxyPanel.h"
enum EngineType{
    Baidu,
    ChatGpt,
    Zhipu
};
class EnginePanel : public ConfigQWidget{
    std::map<EngineType,ConfigQWidget*> engineConfigMap;
    std::map<EngineType,ChatInterface*> engineMap;
    ConfigQWidget * currentEngine;
    EngineType engineTypeValue;
    LabelComboBox * engineType;
    QVBoxLayout * layout;
    void initEngine();
public:
    QString cacheText;
    EnginePanel(
            EngineType engineType = EngineType::ChatGpt,
            QWidget *parent = nullptr,
            const Qt::WindowFlags &f = Qt::WindowFlags ());
    ChatInterface * GetEngine();
    // 单例模式
    static EnginePanel * GetInstance(){
        static EnginePanel * instance = nullptr;
        if(instance == nullptr){
            instance = new EnginePanel();
        }
        return instance;
    }
};


#endif //CHATGPT_SIDEBAR_ENGINEPANEL_H
