//
// Created by 陈嘉乐 on 2023/8/12.
//

#ifndef CHATGPT_SIDEBAR_CONFIGQWIDGET_H
#define CHATGPT_SIDEBAR_CONFIGQWIDGET_H

#include "utils/AutoConfigQt/AutoConfigQt.h"
#include <QWidget>

class ConfigQWidget : public QWidget{
public:
    AutoConfigQt * autoConfigQt;
    ConfigQWidget(AutoConfigQt *autoConfigQt ,QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags());
    void RegisterFatherConfig(AutoConfigQt * _fatherConfig);
};


#endif //CHATGPT_SIDEBAR_CONFIGQWIDGET_H
