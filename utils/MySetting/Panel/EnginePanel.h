//
// Created by 陈嘉乐 on 2023/8/13.
//

#ifndef CHATGPT_SIDEBAR_ENGINEPANEL_H
#define CHATGPT_SIDEBAR_ENGINEPANEL_H

#include "utils/MySetting/KeyInfo/BaiduKey.h"
#include "utils/Ui/Layout/labelComboBox.h"
#include "utils/MySetting/KeyInfo/ChatGptKey.h"
#include "ChatEngine/ChatInterface.h"
#include "utils/MySetting/proxy/ProxyConfig.h"
enum EngineType{
    Baidu,
    ChatGpt
};
class EnginePanel : public ConfigQWidget{
    std::map<EngineType,ConfigQWidget*> engineConfigMap;
    std::map<EngineType,ChatInterface*> engineMap;
    ConfigQWidget * currentEngine;
    EngineType engineTypeValue;
    LabelComboBox * engineType;
    QVBoxLayout * layout;
    void initEngine();
    std::shared_ptr<ProxyConfig> lastProxy;
public:
    QString cacheText;
    EnginePanel(
            EngineType engineType = EngineType::ChatGpt,
            QWidget *parent = nullptr,
            const Qt::WindowFlags &f = Qt::WindowFlags ());
    ChatInterface * GetEngine();
};


#endif //CHATGPT_SIDEBAR_ENGINEPANEL_H
