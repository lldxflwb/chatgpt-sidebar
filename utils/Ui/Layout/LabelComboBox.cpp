//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "LabelComboBox.h"

LabelComboBox::LabelComboBox(
                const QString& labelText,
                std::vector<std::pair<QString,QVariant>> comboBoxContentData,
                AutoConfigItem * value,
                QWidget *parent ,
                const QString& promptText){
    label = new QLabel(labelText,parent);
    comboBox = new QComboBox(parent);
    comboBox->setToolTip(promptText);
    this->comboBoxContentData = comboBoxContentData;
    for (auto & i : comboBoxContentData) {
        comboBox->addItem(i.first,i.second);
    }
    this->addWidget(label);
    this->addWidget(comboBox);
    this->value=static_cast<AutoConfigItemQt*>(value);
    connect(comboBox,&QComboBox::currentIndexChanged,this,[=](int index){
        qDebug() << "index changed" << index;
        int number = this->comboBox->currentData().toInt();
        this->ChangeValue = number;
        this->value->setInt(number);
    });
    this->value->RegisterObserver([=](const ConfigValue &value,ConfigValueType type) {
        qDebug() << "value changed" << std::get<int>(value);
        int currValue = std::get<int>(value);
        if (this->ChangeValue != currValue) {
            // loop comboBoxContentData to find the index of currValue
            for (int i = 0; i < this->comboBoxContentData.size(); ++i) {
                if (this->comboBoxContentData[i].second.toInt() == currValue) {
                    this->comboBox->setCurrentIndex(i);
                    return;
                }
            }
        }
    });
    int configVaule = std::get<int>(value->getValue());
    for (int i = 0; i < this->comboBoxContentData.size(); ++i) {
        if(this->comboBoxContentData[i].second.toInt()==configVaule){
            this->comboBox->setCurrentIndex(i);
            return ;
        }
    }
}

QVariant LabelComboBox::getComboBoxContent() {
    return comboBox->currentData();
}

void LabelComboBox::setComboBoxContent(const QString &content) {

}
