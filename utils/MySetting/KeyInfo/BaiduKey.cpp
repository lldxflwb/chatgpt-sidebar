//
// Created by 陈嘉乐 on 2023/8/13.
//

#include "BaiduKey.h"

extern AutoConfig::StoragePolicy storagePolicy;
AutoConfig * baiduConfig;

BaiduKey::BaiduKey(
        QString accessKey , QString keySecret ,
        QWidget *parent ,
        const Qt::WindowFlags &f )
        : ConfigQWidget(new AutoConfigQt("Baidu.ini",storagePolicy), parent, f)
{
    auto keyItem = autoConfigQt->addQString("accessKey", accessKey);
    this->accessKey = new LabelEditLine("accessKey",keyItem,this,"");
    auto secretItem = autoConfigQt->addQString("keySecret", keySecret);
    this->keySecret = new LabelEditLine("keySecret",secretItem,this,"");
    auto tokenItem = autoConfigQt->addQString("token", "");
    this->token = new LabelLabel("token",tokenItem,this,"");
    this->layout = new QVBoxLayout();
    this->layout->addLayout(this->accessKey);
    this->layout->addLayout(this->keySecret);
    this->layout->addLayout(this->token);
    this->setLayout(this->layout);
    baiduConfig = this->autoConfigQt;
//    baiduConfig->readFile();
    this->hide();
}