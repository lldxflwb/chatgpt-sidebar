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

LabelEditLine::LabelEditLine(
        const QString& labelText,
        AutoConfigItem * value,
        QWidget *parent , const QString& promptText){
    std::string editContent = std::get<std::string>(value->getValue());
    label = new QLabel(labelText,parent);
    edit = new QLineEdit(QString::fromStdString(editContent),parent);
    edit->setToolTip(promptText);
    this->addWidget(label);
    this->addWidget(edit);
    this->value=static_cast<AutoConfigItemQt*>(value);
    connect(edit,&QLineEdit::textChanged,[=](const QString& text){
        qDebug() << "text changed" << text;
        this->ChangeValue = text.toStdString();
        this->value->setValue(text);
    });
    this->value->addObserver([=](const ConfigValue& value){
        qDebug() << "value changed" << std::get<std::string>(value);
        std::string currValue = std::get<std::string>(value);
        if(this->ChangeValue!= currValue){
            this->edit->setText(QString::fromStdString(currValue));
        }
    });
}

LabelEditLine::~LabelEditLine() {
}
