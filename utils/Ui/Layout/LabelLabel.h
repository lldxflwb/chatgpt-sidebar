//
// Created by 陈嘉乐 on 2023/8/14.
//

#ifndef CHATGPT_SIDEBAR_LABELLABEL_H
#define CHATGPT_SIDEBAR_LABELLABEL_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include "utils/AutoConfigQt/AutoConfigItemQt.h"

class LabelLabel : public QHBoxLayout{
public:
    QLabel * key_label,*value_label;
    AutoConfigItemQt * value;
    LabelLabel
            (
                    const QString& labelText,
                    AutoConfigItem * value,
                    QWidget *parent = nullptr,
                    const QString& promptText="");
    ~LabelLabel();

};

#endif //CHATGPT_SIDEBAR_LABELLABEL_H
