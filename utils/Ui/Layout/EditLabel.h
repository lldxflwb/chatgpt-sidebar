//
// Created by 陈嘉乐 on 2023/8/15.
//

#ifndef CHATGPT_SIDEBAR_EDITLABEL_H
#define CHATGPT_SIDEBAR_EDITLABEL_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include "utils/AutoConfigQt/AutoConfigItemQt.h"

class EditLabel : public QHBoxLayout{
public:
    AutoConfigItemQt * value;
    EditLabel(const QString& keyText, const QString& valueText, QWidget *parent = nullptr);
    QString getValueContent();
    void setValueContent(const QString& content);

public slots:
    void labelClicked();
    void finishEditing();

private:
    QLabel *keyLabel;
    QLabel *valueLabel;
    QLineEdit *valueEdit;
};


#endif //CHATGPT_SIDEBAR_EDITLABEL_H
