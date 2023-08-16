//
// Created by 陈嘉乐 on 2023/8/14.
//

#include "LabelLabel.h"

LabelLabel::LabelLabel(const QString &labelText, AutoConfigItem *value, QWidget *parent, const QString &promptText) {
    std::string editContent = std::get<std::string>(value->getValue());
    key_label = new QLabel(labelText,parent);
    value_label = new QLabel(QString::fromStdString(editContent),parent);
    value_label->setToolTip(promptText);
    this->addWidget(key_label);
    this->addWidget(value_label);
    this->value=static_cast<AutoConfigItemQt*>(value);
    this->value->RegisterObserver([=](const ConfigValue &value,ConfigValueType type) {
        qDebug() << "value changed" << std::get<std::string>(value);
        std::string currValue = std::get<std::string>(value);
        this->value_label->setText(QString::fromStdString(currValue));
    });

}

LabelLabel::~LabelLabel() {

}
