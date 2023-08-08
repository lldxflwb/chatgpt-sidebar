//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "AutoConfig.h"
#include <nlohmann/json.hpp>
#include <fstream>


AutoConfig::AutoConfig(const std::string& fileName) : fileName(fileName) {}

AutoConfigItem* AutoConfig::getItem(const std::string& key) {
    if(items.find(key) == items.end()) {
        return nullptr;
    }
    return items.at(key);
}

void AutoConfig::readFromFile() {
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Failed to open file " + fileName);
    }

    nlohmann::json j;
    file >> j;

    for (const auto& [key, value] : j.items()) {
        if (value.is_number_integer()) {
            addItems(key, value.get<int>());
        } else if (value.is_number_float()) {
            addItems(key,value.get<double>());
        } else if (value.is_string()) {
            addItems(key, value.get<std::string>());
        }
    }
}

void AutoConfig::saveToFile() {
    std::ofstream file(fileName);
    if (!file) {
        throw std::runtime_error("Failed to open file " + fileName);
    }

    nlohmann::json j;

    for (const auto& itemPair : items) {
        std::string key = itemPair.first;
        auto& item = *itemPair.second;
        const auto& value = item.getValue();

        std::visit([&, key](const auto& val) {
            j[key] = val;
        }, value);
    }

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
            this->saveToFile();
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