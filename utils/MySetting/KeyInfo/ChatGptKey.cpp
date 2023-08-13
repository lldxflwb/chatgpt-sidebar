//
// Created by 陈嘉乐 on 2023/8/12.
//

#include "ChatGptKey.h"

extern AutoConfig::StoragePolicy storagePolicy;
AutoConfig * chatGptConfig ;

ChatGptKey::ChatGptKey( QString key, QWidget *parent, const Qt::WindowFlags &f)
        : ConfigQWidget(new AutoConfigQt("ChatGpt.ini",storagePolicy), parent, f){
    auto item = autoConfigQt->addQString("key", key);
    this->keyEditLine = new LabelEditLine("key",item,this,"");
    this->setLayout(this->keyEditLine);
    chatGptConfig = this->autoConfigQt;
}
