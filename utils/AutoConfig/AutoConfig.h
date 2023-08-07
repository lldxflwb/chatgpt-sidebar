//
// Created by 陈嘉乐 on 2023/8/7.
//

#ifndef CHATGPT_SIDEBAR_AUTOCONFIG_H
#define CHATGPT_SIDEBAR_AUTOCONFIG_H

#include "AutoConfigItem.h"
#include <string>
#include <unordered_map>

class AutoConfig {
private:
    std::unordered_map<std::string, AutoConfigItem> items;
    std::string fileName;

public:
    AutoConfig(const std::string& fileName);
    const AutoConfigItem* getItem(const std::string& key) const;
    const std::unordered_map<std::string, AutoConfigItem>& getItems() const; // 新增
    void readFromFile();
    void saveToFile();
    // addItems() 新增
    AutoConfigItem * addItems(const std::string& key, const ConfigValue & value);
};





#endif //CHATGPT_SIDEBAR_AUTOCONFIG_H
