//
// Created by 陈嘉乐 on 2023/8/12.
//

#ifndef CHATGPT_SIDEBAR_CHATGPTKEY_H
#define CHATGPT_SIDEBAR_CHATGPTKEY_H

#include "utils/MySetting/ConfigQWidget.h"
#include "utils/Ui/Layout/LabelEditLine.h"

class ChatGptKey : public ConfigQWidget{
public:
    LabelEditLine * keyEditLine;

    ChatGptKey(QString key, QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags ());
};


#endif //CHATGPT_SIDEBAR_CHATGPTKEY_H
