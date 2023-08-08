//
// Created by 陈嘉乐 on 2023/8/7.
//

#ifndef CHATGPT_SIDEBAR_LABELEDITLINE_H
#define CHATGPT_SIDEBAR_LABELEDITLINE_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include "utils/AutoConfig/AutoConfigItemQt.h"

class LabelEditLine : public QHBoxLayout{
public:
    QLabel * label;
    QLineEdit * edit;
    AutoConfigItemQt * value;
    std::string ChangeValue;
    LabelEditLine
    (
            const QString& labelText,
            AutoConfigItem * value,
            QWidget *parent = nullptr,
            const QString& promptText="");
    // set get
    QString getEditContent();
    void setEditContent(const QString& content);
    ~LabelEditLine();

};

#endif //CHATGPT_SIDEBAR_LABELEDITLINE_H
