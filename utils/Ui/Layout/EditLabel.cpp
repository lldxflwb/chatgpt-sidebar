//
// Created by 陈嘉乐 on 2023/8/15.
//

#include "EditLabel.h"

EditLabel::EditLabel(const QString& keyText, const QString& valueText, QWidget *parent)
        : QHBoxLayout(parent) {
    valueLabel = new QLabel(valueText, parent);
    valueEdit = new QLineEdit(valueText, parent);
    valueEdit->hide(); // 默认隐藏编辑框
    this->addWidget(valueLabel);
    this->addWidget(valueEdit);

    connect(valueLabel, &QLabel::linkActivated, this, &EditLabel::labelClicked);
    connect(valueEdit, &QLineEdit::editingFinished, this, &EditLabel::finishEditing);

    this->value=static_cast<AutoConfigItemQt*>(value);
    this->value->RegisterObserver([=](
            const ConfigValue &value,
            ConfigValueType type,
            AutoConfigItemEvent event) {
        qDebug() << "value changed" << std::get<std::string>(value);
        std::string currValue = std::get<std::string>(value);
        this->valueLabel->setText(QString::fromStdString(currValue));
        this->valueEdit->setText(QString::fromStdString(currValue));
    });
}

void EditLabel::labelClicked() {
    valueLabel->hide();
    valueEdit->show();
    valueEdit->setFocus();
    this->value->setValue(this->valueEdit->text());
}

void EditLabel::finishEditing() {
    valueLabel->setText(valueEdit->text());
    valueLabel->show();
    valueEdit->hide();
}

QString EditLabel::getValueContent() {
    return valueLabel->text();
}

void EditLabel::setValueContent(const QString& content) {
    valueLabel->setText(content);
}

