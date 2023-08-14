//
// Created by 陈嘉乐 on 2023/8/14.
//
#include "ConfigQWidget.h"

ConfigQWidget::ConfigQWidget(
        AutoConfigQt *autoConfigQt ,
        QWidget *parent, const Qt::WindowFlags &f )
: QWidget(parent, f), autoConfigQt(autoConfigQt) {}

void ConfigQWidget::RegisterFatherConfig(AutoConfigQt * _fatherConfig){
    _fatherConfig->addChild(autoConfigQt);
    autoConfigQt->parent=_fatherConfig;
}