//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "LabelComboBox.h"

LabelComboBox::LabelComboBox(
                const QString& labelText,
                std::vector<std::pair<QString,QVariant>> comboBoxContentData,
                QWidget *parent ,
                const QString& promptText){
    label = new QLabel(labelText,parent);
    comboBox = new QComboBox(parent);
    comboBox->setToolTip(promptText);
    for (auto & i : comboBoxContentData) {
        comboBox->addItem(i.first,i.second);
    }
    this->addWidget(label);
    this->addWidget(comboBox);
}

QVariant LabelComboBox::getComboBoxContent() {
    return comboBox->currentData();
}

void LabelComboBox::setComboBoxContent(const QString &content) {

}
