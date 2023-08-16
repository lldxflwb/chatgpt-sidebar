//
// Created by 陈嘉乐 on 2023/8/15.
//

#include "LineEditLabel.h"

LineEditLabel::LineEditLabel(const QString& keyText, const QString& valueText, QWidget *parent)
        : QHBoxLayout(parent) {
    keyLabel = new QLabel(keyText, parent);
    valueLabel = new QLabel(valueText, parent);
    valueEdit = new QLineEdit(valueText, parent);
    valueEdit->hide(); // 默认隐藏编辑框
    this->addWidget(keyLabel);
    this->addWidget(valueLabel);
    this->addWidget(valueEdit);

    connect(valueLabel, &QLabel::linkActivated, this, &LineEditLabel::labelClicked);
    connect(valueEdit, &QLineEdit::editingFinished, this, &LineEditLabel::finishEditing);

    this->value=static_cast<AutoConfigItemQt*>(value);
    this->value->RegisterObserver([=](const ConfigValue &value,ConfigValueType type) {
        qDebug() << "value changed" << std::get<std::string>(value);
        std::string currValue = std::get<std::string>(value);
        this->valueLabel->setText(QString::fromStdString(currValue));
        this->valueEdit->setText(QString::fromStdString(currValue));
    });
}

void LineEditLabel::labelClicked() {
    valueLabel->hide();
    valueEdit->show();
    valueEdit->setFocus();
    this->value->setValue(this->valueEdit->text());
}

void LineEditLabel::finishEditing() {
    valueLabel->setText(valueEdit->text());
    valueLabel->show();
    valueEdit->hide();
}

QString LineEditLabel::getValueContent() {
    return valueLabel->text();
}

void LineEditLabel::setValueContent(const QString& content) {
    valueLabel->setText(content);
}

