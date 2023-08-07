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

class LabelComboBox : public QHBoxLayout{
public:
    QLabel * label;
    QComboBox * comboBox;
    LabelComboBox
    (
            const QString& labelText,
            std::vector<std::pair<QString,QVariant>> comboBoxContentData,
            QWidget *parent = nullptr,
            const QString& promptText="");
    // set get
    QVariant getComboBoxContent();
    void setComboBoxContent(const QString& content);
};


#endif //CHATGPT_SIDEBAR_LABELCOMBOBOX_H
