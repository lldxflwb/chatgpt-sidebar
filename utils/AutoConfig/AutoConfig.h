//
// Created by 陈嘉乐 on 2023/8/7.
//

#ifndef CHATGPT_SIDEBAR_AUTOCONFIG_H
#define CHATGPT_SIDEBAR_AUTOCONFIG_H

#include "AutoConfigItem.h"
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "utils/PubSub.h"

typedef std::unordered_map<std::string, AutoConfigItem *> ConfigValues;
class AutoConfig;
enum class ConfigEvent{
    EventSave,
    EventRead,
    EventItemValueChange,
    EventSonValueChange,
};
typedef Publisher<const AutoConfig&, ConfigEvent> AutoConfigPublisher;

class AutoConfig : public AutoConfigPublisher{
public:
    typedef std::function<void(const AutoConfig&,ConfigEvent)> ObserversFunc;
    enum class StoragePolicy{
        SingleFile,
        MultiFile
    };
private:
    ConfigValues items;
    std::string fileName;
//    std::vector<ObserversFunc> observers;
    StoragePolicy storagePolicy;
public:
    AutoConfig * parent;
    std::vector<AutoConfig*> children;
    AutoConfig(const std::string &fileName, StoragePolicy _storagePolicy = StoragePolicy::SingleFile, AutoConfig *_parent = nullptr);
    AutoConfigItem* getItem(const std::string& key);
    const ConfigValues & getItems() const; // 新增
    void readFile();
    void saveFile();
    void saveSingleFile();
    void saveMultiFile();
    void readFromMultiFile();
    void readFromSingleFile();
    // addItems() 新增
    AutoConfigItem * addItems(const std::string& key, const ConfigValue & value);
    AutoConfigItem * addItems(const std::string& key, AutoConfigItem * item );
    bool fileIsExist();
    void addChild(AutoConfig * child);
    // 发布订阅
    nlohmann::json ObjectToJson();
    nlohmann::json CurrObjectToJson();
    void ReadConfigFromJson(nlohmann::json j);
    void ReadCurrConfigFromJson(nlohmann::json j);
    void EventDeal(ConfigEvent configEvent);
private:
    void valueChange();
};





#endif //CHATGPT_SIDEBAR_AUTOCONFIG_H
