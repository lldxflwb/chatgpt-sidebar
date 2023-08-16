//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "AutoConfig.h"
#include <fstream>

AutoConfig::StoragePolicy storagePolicy = AutoConfig::StoragePolicy::SingleFile;

AutoConfig::AutoConfig(const std::string &fileName, StoragePolicy _storagePolicy, AutoConfig *_parent)
: fileName(fileName) ,parent(_parent){
    if(_parent){
        _parent->addChild(this);
        this->RegisterObserver([this](const AutoConfig &parent, ConfigEvent configEvent) {
            this->EventDeal(configEvent);
        });
    }
}

AutoConfigItem* AutoConfig::getItem(const std::string& key) {
    if(items.find(key) == items.end()) {
        return nullptr;
    }
    return items.at(key);
}



void AutoConfig::saveSingleFile() {
    std::ofstream file(fileName);
    if (!file) {
        throw std::runtime_error("Failed to open file " + fileName);
    }

    nlohmann::json j = this->ObjectToJson();
    file << j;
}

//    const std::unordered_map<std::string, AutoConfigItem>& getItems() const; // 新增
const ConfigValues& AutoConfig::getItems() const {
    return items;
}

AutoConfigItem * AutoConfig::addItems(const std::string& key, const ConfigValue & value) {
    if(items.find(key) == items.end()) {
        auto item = new AutoConfigItem();
        item->setValue(value);
        return addItems(key, item);
    }
    return items[key];
}

bool AutoConfig::fileIsExist(){
    std::ifstream file(fileName);
    return file.good();
}

void AutoConfig::addChild(AutoConfig *child) {
    child->RegisterObserver([this](const AutoConfig &child, ConfigEvent configEvent) {
        switch(configEvent){
            case ConfigEvent::EventItemValueChange:
            case ConfigEvent::EventSonValueChange:
                this->Notify(*this, ConfigEvent::EventSonValueChange);
                break;
            default:
                break;
        }
    });
    this->children.push_back(child);
}

void AutoConfig::valueChange() {
    this->Notify(*this, ConfigEvent::EventItemValueChange);
    this->saveFile();
}


nlohmann::json AutoConfig::ObjectToJson() {
    nlohmann::json j,son = nlohmann::json::array();
    for (auto item : children ) {
        son.push_back(item->ObjectToJson());
    }
    j=this->CurrObjectToJson();
    j["son"]=son;
    return j;
}

nlohmann::json AutoConfig::CurrObjectToJson() {
    nlohmann::json j,curr;
    for( auto & item : this->items){
        item.second->toJson(curr,item.first);
    }
    j["name"]=this->fileName;
    j["values"]=curr;
    return j;
}

void AutoConfig::ReadCurrConfigFromJson(nlohmann::json j) {
    // 校验name
    if(j["name"] != this->fileName){
        throw std::runtime_error("Failed to open file " + fileName);
    }
    for (const auto& [key, value] : j["values"].items()) {
        // 如果key已经存在，则替换
        if(items.find(key) != items.end() ){
            items[key]->fromJson(j["values"],key);
            continue;
        }
        else{
            AutoConfigItem * item;
            item->toJson(j["values"],key);
            this->addItems(key,item);
        }
    }
}


void AutoConfig::ReadConfigFromJson(nlohmann::json j) {
    this->ReadCurrConfigFromJson(j);
    for (auto item : j["son"]) {
        std::string name = item["name"];
        bool isExist = false;
        for(auto child : this->children){
            if(child->fileName == name){
                child->ReadConfigFromJson(item);
                isExist = true;
                break;
            }
        }
        if(!isExist){
            // error !
            throw std::runtime_error("Failed to open file " + fileName);
        }
    }
}

void AutoConfig::saveMultiFile() {
    std::ofstream file(fileName);
    if (!file) {
        throw std::runtime_error("Failed to open file " + fileName);
    }
    nlohmann::json j = this->CurrObjectToJson();
    file << j;
}

void AutoConfig::readFromMultiFile() {
    if(!this->fileIsExist()){
        this->saveSingleFile();
    }
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Failed to open file " + fileName);
    }
    nlohmann::json j;
    file >> j;
    this->ReadCurrConfigFromJson(j);
}

void AutoConfig::readFromSingleFile() {
    // 文件不存在 则创建
    if(!this->fileIsExist()){
        this->saveSingleFile();
    }
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Failed to open file " + fileName);
    }
    nlohmann::json j;
    file >> j;
    this->ReadConfigFromJson(j);
}

void AutoConfig::readFile() {
    switch(this->storagePolicy){
        case StoragePolicy::SingleFile:
        {
            if(this->parent){
                this->parent->readFile();
            }
            else{
                this->readFromSingleFile();
            }
        }
        break;
        case StoragePolicy::MultiFile:
        {
            this->readFromMultiFile();
        }
        break;
    }
}
void AutoConfig::saveFile() {
    switch(this->storagePolicy){
        case StoragePolicy::SingleFile:
        {
            if(this->parent){
                this->parent->saveFile();
            }
            else{
                this->saveSingleFile();
            }
        }
        break;
        case StoragePolicy::MultiFile:
        {
            this->saveMultiFile();
        }
        break;
    }
}

void AutoConfig::EventDeal(ConfigEvent configEvent) {
    switch (configEvent) {
        case ConfigEvent::EventRead:
            this->readFile();
            break;
        case ConfigEvent::EventSave:
            this->saveFile();
            break;
        case ConfigEvent::EventItemValueChange:
//            this->saveFile();
            break;
        case ConfigEvent::EventSonValueChange:
//            this->saveFile();
            break;
        default:
            break;
    }
}

AutoConfigItem *AutoConfig::addItems(const std::string &key, AutoConfigItem *item) {
    item->RegisterObserver([this,item](const ConfigValue &newValue,ConfigValueType type) {
        this->valueChange();
    });
    auto * currItem = new AutoConfigItem(*item);
    items[key] = currItem;
    return currItem;
}
