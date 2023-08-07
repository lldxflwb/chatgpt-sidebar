//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "LabelEditLine.h"

void LabelEditLine::setEditContent(const QString &content) {
    edit->setText(content);
}

QString LabelEditLine::getEditContent() {
    return edit->text();
}

LabelEditLine::LabelEditLine(const QString& labelText, const QString& editContent,QWidget *parent , const QString& promptText){
    label = new QLabel(labelText,parent);
    edit = new QLineEdit(editContent,parent);
    edit->setToolTip(promptText);
    this->addWidget(label);
    this->addWidget(edit);
}