//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "AutoConfig.h"
#include <fstream>


AutoConfig::AutoConfig(const std::string &fileName, StoragePolicy _storagePolicy, AutoConfig *_parent)
: fileName(fileName) ,parent(_parent){
    if(_parent){
        _parent->addChild(this);
        this->addObserver([this](const AutoConfig& parent, ConfigEvent configEvent){
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
        item->addObserver([this](const ConfigValue& newValue) {
            this->valueChange();
        });
        auto * currItem = new AutoConfigItem(*item);
        items[key] = currItem;
        return currItem;
    }
    return items[key];
}

bool AutoConfig::fileIsExist(){
    std::ifstream file(fileName);
    return file.good();
}

void AutoConfig::addChild(AutoConfig *child) {
    this->children.push_back(child);
}

void AutoConfig::addObserver(const ObserversFunc &observer) {
    observers.push_back(observer);
}

void AutoConfig::notify(const AutoConfig &value, ConfigEvent configEvent) const {
    for (const auto& observer : observers) {
        observer(value,configEvent);
    }
}

void AutoConfig::valueChange() {
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
        std::string key = item.first;
        auto& itemValue = *item.second;
        const auto& value = itemValue.getValue();
        std::visit([&](const auto& val) {
            curr[key] = val;
        }, value);
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
        if (value.is_number_integer()) {
            addItems(key, value.get<int>());
        } else if (value.is_number_float()) {
            addItems(key,value.get<double>());
        } else if (value.is_string()) {
            addItems(key, value.get<std::string>());
        }
        else{
            throw std::runtime_error("Failed to open file " + fileName);
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
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Failed to open file " + fileName);
    }
    nlohmann::json j;
    file >> j;
    this->ReadCurrConfigFromJson(j);
}

void AutoConfig::readFromSingleFile() {
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

void AutoConfig::EventDeal(AutoConfig::ConfigEvent configEvent) {
    switch (configEvent) {
        case ConfigEvent::EventRead:
            this->readFile();
            break;
        case ConfigEvent::EventSave:
            this->saveFile();
            break;
    }
}
