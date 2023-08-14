//
// Created by 陈嘉乐 on 2023/8/15.
//

#include "SettingPanel.h"

extern AutoConfig::StoragePolicy storagePolicy;

SettingPanel::SettingPanel(QWidget *parent)
    : ConfigQWidget(new AutoConfigQt("SettingPanel.json",storagePolicy),parent){
    this->layout = new QVBoxLayout(this);
    this->engine_panel = EnginePanel::GetInstance();
    this->proxy_panel = ProxyPanel::GetInstance();
    this->layout->addWidget(this->engine_panel);
    this->layout->addWidget(this->proxy_panel);
    this->engine_panel->RegisterFatherConfig(autoConfigQt);
    this->engine_panel->show();
    this->proxy_panel->RegisterFatherConfig(autoConfigQt);
    this->proxy_panel->show();
    this->setLayout(this->layout);
    this->show();
}
