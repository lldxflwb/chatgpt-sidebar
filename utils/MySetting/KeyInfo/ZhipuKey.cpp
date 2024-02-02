//
// Created by lldx on 2024/2/2.
//

#include "ZhipuKey.h"
extern AutoConfig::StoragePolicy storagePolicy;
AutoConfig * zhipuConfig;

ZhipuKey::ZhipuKey(QString api_key,
                   QWidget *parent, const Qt::WindowFlags &f)
        : ConfigQWidget(new AutoConfigQt("Zhipu.ini",storagePolicy), parent, f){
    auto keyItem = autoConfigQt->addQString("api_key", api_key);
    this->key = new LabelEditLine("api_key",keyItem,this,"");
    this->layout = new QVBoxLayout();
    this->layout->addLayout(this->key);
    this->setLayout(this->layout);
    zhipuConfig = this->autoConfigQt;
    this->hide();
}
