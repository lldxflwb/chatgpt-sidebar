//
// Created by 陈嘉乐 on 2023/8/7.
//

#ifndef CHATGPT_SIDEBAR_LABELCOMBOBOX_H
#define CHATGPT_SIDEBAR_LABELCOMBOBOX_H

#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QWidget>
#include <vector>
#include "utils/AutoConfig/AutoConfigItemQt.h"
class LabelComboBox : public QHBoxLayout{
public:
    QLabel * label;
    QComboBox * comboBox;
    AutoConfigItemQt * value;
    std::vector<std::pair<QString,QVariant>> comboBoxContentData;
    int ChangeValue;

    LabelComboBox
    (
            const QString& labelText,
            std::vector<std::pair<QString,QVariant>> comboBoxContentData,
            AutoConfigItem * value,
            QWidget *parent = nullptr,
            const QString& promptText="");
    // set get
    QVariant getComboBoxContent();
    void setComboBoxContent(const QString& content);
};


#endif //CHATGPT_SIDEBAR_LABELCOMBOBOX_H
