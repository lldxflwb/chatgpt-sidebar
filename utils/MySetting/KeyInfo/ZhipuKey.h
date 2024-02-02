//
// Created by lldx on 2024/2/2.
//

#ifndef CHATGPT_SIDEBAR_ZHIPUKEY_H
#define CHATGPT_SIDEBAR_ZHIPUKEY_H

#include "utils/MySetting/ConfigQWidget.h"
#include "utils/Ui/Layout/LabelEditLine.h"
#include "utils/Ui/Layout/LabelLabel.h"
class ZhipuKey :public ConfigQWidget{
public:
    LabelEditLine * key;
    QVBoxLayout * layout;
    ZhipuKey(
            QString api_key = "" ,
            QWidget *parent = nullptr,
    const Qt::WindowFlags &f = Qt::WindowFlags ());
};



#endif //CHATGPT_SIDEBAR_ZHIPUKEY_H
