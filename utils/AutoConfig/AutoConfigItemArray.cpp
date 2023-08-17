//
// Created by 陈嘉乐 on 2023/8/16.
//

#include "AutoConfigItemArray.h"

AutoConfigItemArray::AutoConfigItemArray(ConfigValueType type) : type(type){
    items.clear();
}

AutoConfigItem *AutoConfigItemArray::addItem(AutoConfigItem *item) {
    if(item && (observers.find(item) == observers.end() || observers[item] != -1)){
        items.push_back(item);
        auto id= item->RegisterObserver([this](
                const ConfigValue & item,
                ConfigValueType t,
                AutoConfigItemEvent event) {
            this->Notify(
                this,
                this->getItem(item),
                AutoConfigItemArrayEvent::ItemValueChange,
                t);
        });
        this->observers[item] = id;
        this->Notify(
                this,
                item,
                AutoConfigItemArrayEvent::AddItem,
                type);
    }
    return item;
}

AutoConfigItem *AutoConfigItemArray::addItem(ConfigValue item, ConfigValueType type) {
    AutoConfigItem * autoConfigItem = new AutoConfigItem();
    assert(type==ConfigValueType::Undefined);
    autoConfigItem->setValue(std::make_pair(type,item));
    this->addItem(autoConfigItem);
}

AutoConfigItem *AutoConfigItemArray::removeItem(AutoConfigItem *item) {
    if (!item){
        return nullptr;
    }
    for(auto it : this->items){
        if(it == item){
            if (observers.find(item) != observers.end()){
                item->RemoveObserver(this->observers[item]);
                this->observers[item]=-1;
                this->items.erase(std::find(items.begin(), items.end(), item));
                this->Notify(
                        this,
                        item,
                        AutoConfigItemArrayEvent::RemoveItem,
                        type);
                return it;
            }
        }
    }
    return nullptr;
}

AutoConfigItem *AutoConfigItemArray::removeItem(int index) {
   return this->removeItem(this->getItem(index));
}

AutoConfigItem *AutoConfigItemArray::getItem(int index) {
    if(index < 0 || index >= items.size()){
        return nullptr;
    }
    return items[index];
}

int AutoConfigItemArray::size() {
    return items.size();
}

ConfigValueType AutoConfigItemArray::getType() {
    return this->type;
}

AutoConfigItem *AutoConfigItemArray::getItem(const ConfigValue &item) {
    for(auto it : this->items){
        if(it->getValue() == item){
            return it;
        }
    }
}

nlohmann::json AutoConfigItemArray::toJson() {
    nlohmann::json j,arr = nlohmann::json::array();
    for(auto it : this->items){
        nlohmann::json item;
        it->toJson(item,"value");
        arr.push_back(item["value"]);
    }
    j["items"]=arr;
    j["type"]=type;
    return j;
}

void AutoConfigItemArray::fromJson(nlohmann::json j) {
    for(auto it : this->items){
        this->removeItem(it);
    }
    for(auto it : j){
        nlohmann::json item;
        item["value"] = j;
        AutoConfigItem * autoConfigItem = new AutoConfigItem();
        autoConfigItem->fromJson(item,"value");
        this->addItem(autoConfigItem);
    }
    return;
}
