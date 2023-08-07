//
// Created by 陈嘉乐 on 2023/8/7.
//

#ifndef CHATGPT_SIDEBAR_LABELEDITLINE_H
#define CHATGPT_SIDEBAR_LABELEDITLINE_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class LabelEditLine : public QHBoxLayout{
public:
    QLabel * label;
    QLineEdit * edit;
    LabelEditLine
    (
            const QString& labelText,
            const QString& editContent,
            QWidget *parent = nullptr,
            const QString& promptText="");
    // set get
    QString getEditContent();
    void setEditContent(const QString& content);

};

#endif //CHATGPT_SIDEBAR_LABELEDITLINE_H
