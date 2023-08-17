//
// Created by 陈嘉乐 on 2023/8/13.
//

#include "EnginePanel.h"
#include "utils/MySetting/KeyInfo/BaiduKey.h"
#include "utils/MySetting/KeyInfo/ChatGptKey.h"
#include "ChatEngine/BaiduEngine/BaiduEngine.h"
#include "ChatEngine/ChatGptEngine/OpenAiEngine.h"
#include <QTextEdit>
extern AutoConfig::StoragePolicy storagePolicy;
extern QTextEdit * outPutTextArea;
AutoConfig * engineConfig;


EnginePanel::EnginePanel(
        EngineType engineType ,
        QWidget *parent,
        const Qt::WindowFlags &f )
        : ConfigQWidget(new AutoConfigQt("EnginePanel.json",storagePolicy), parent, f){
    cacheText = "";
    auto engineTypeItem = autoConfigQt->addItems("engineType",engineType);
    this->engineConfigMap[EngineType::Baidu] = new BaiduKey();
    this->engineMap[EngineType::Baidu] = new BaiduEngine();
    this->engineConfigMap[EngineType::Baidu]->RegisterFatherConfig(autoConfigQt);
    this->engineConfigMap[EngineType::ChatGpt] = new ChatGptKey("");
    this->engineMap[EngineType::ChatGpt] = new OpenAiEngine();
    this->engineConfigMap[EngineType::ChatGpt]->RegisterFatherConfig(autoConfigQt);
    this->engineTypeValue = engineType;
    this->currentEngine = this->engineConfigMap[engineType];
    this->engineType =
            new LabelComboBox("engineType",
                              {
                                        {"文心一言",EngineType::Baidu},
                                        {"ChatGpt3.5",EngineType::ChatGpt}
                },
                              engineTypeItem,
                              this);
    this->layout = new QVBoxLayout();
    this->layout->addLayout(this->engineType);
    this->layout->addWidget(this->engineConfigMap[EngineType::Baidu]);
    this->layout->addWidget(this->engineConfigMap[EngineType::ChatGpt]);
    this->currentEngine->show();
    this->setLayout(this->layout);
    if(  ProxyPanel::GetInstance()->currentProxy && EngineType::ChatGpt != engineType){
        ProxyPanel::GetInstance()->autoConfigQt->getItem("proxyType")->setValue(ProxyType::None);
    }
    engineTypeItem->RegisterObserver([this](
            const ConfigValue &value,
            ConfigValueType type,
            AutoConfigItemEvent event) {
        auto proxyPanel = ProxyPanel::GetInstance();
        EngineType engineType = (EngineType) std::get<int>(value);
        this->currentEngine->hide();
        this->currentEngine = this->engineConfigMap[engineType];
        this->currentEngine->show();
        this->engineTypeValue = engineType;
        AutoConfigItem *v = proxyPanel->proxyType->value;
        if (this->engineTypeValue == EngineType::ChatGpt) {
            // use proxy default
            v->setValue(
                    proxyPanel->defaultGptProxy->value->getValue()
            );
        } else {
            v->setValue(ProxyType::None);
        }
    });
    this->autoConfigQt->readFile();
    this->initEngine();
    engineConfig= this->autoConfigQt;
}

ChatInterface *EnginePanel::GetEngine() {
    return this->engineMap[this->engineTypeValue];
}

void EnginePanel::initEngine() {
    for(auto item : this->engineMap){
       item.second->RegisterObserver([this](QString text,ApiStatus status){
           if(ApiStatus::start == status){
               this->cacheText = "";
               outPutTextArea->clear();
           }
           this->cacheText = this->cacheText + text;
           outPutTextArea->setText( this->cacheText);
           outPutTextArea->moveCursor(QTextCursor::End);
       });
    }
}

