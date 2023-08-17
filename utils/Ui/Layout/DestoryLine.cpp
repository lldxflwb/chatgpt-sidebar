//
// Created by 陈嘉乐 on 2023/8/17.
//

#include "DestoryLine.h"

DestroyLine::DestroyLine(QWidget *parent) : QHBoxLayout(parent) {
    destroyButton = new QPushButton("-",parent);
    this->addWidget(destroyButton);
    QObject::connect(destroyButton,&QPushButton::clicked,[=](){
        for(auto value:values){
            auto p = value->getValueAsPair();
            value->Notify(p.second,p.first,AutoConfigItemEvent::NodeBeDeleted);
        }
    });

}

void DestroyLine::AddValues(AutoConfigItem * value) {
    for(auto value:values){
        this->values.push_back(value);
    }
}
