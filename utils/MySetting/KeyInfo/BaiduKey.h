//
// Created by 陈嘉乐 on 2023/8/13.
//

#ifndef CHATGPT_SIDEBAR_BAIDUKEY_H
#define CHATGPT_SIDEBAR_BAIDUKEY_H

#include "utils/MySetting/ConfigQWidget.h"
#include "utils/Ui/Layout/LabelEditLine.h"
#include "utils/Ui/Layout/LabelLabel.h"
class BaiduKey :public ConfigQWidget{
public:
    LabelEditLine * accessKey;
    LabelEditLine * keySecret;
    LabelLabel * token;
    QVBoxLayout * layout;
    BaiduKey(
            QString accessKey = "" ,
            QString keySecret = "" ,
            QWidget *parent = nullptr,
            const Qt::WindowFlags &f = Qt::WindowFlags ());
};


#endif //CHATGPT_SIDEBAR_BAIDUKEY_H
