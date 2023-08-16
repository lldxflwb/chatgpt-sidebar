//
// Created by 陈嘉乐 on 2023/8/16.
//

#ifndef CHATGPT_SIDEBAR_AUTOCONFIGITEMARRAY_H
#define CHATGPT_SIDEBAR_AUTOCONFIGITEMARRAY_H

#include "AutoConfigItem.h"
#include "utils/PubSub.h"

class AutoConfigItemArray;
enum AutoConfigItemArrayEvent{
    AddItem,
    RemoveItem,
    ItemValueChange
};
typedef Publisher<AutoConfigItemArray*,AutoConfigItem *, AutoConfigItemArrayEvent,ConfigValueType> AutoConfigItemArrayPublisher;
class AutoConfigItemArray : public AutoConfigItemArrayPublisher{
    // 数组需要包含的元素
    // 1.数组的长度 items.size()
    // 2.数组的元素类型 ConfigValueType
    // 3.数组的元素 AutoConfigItem
    ConfigValueType type;
    std::vector<AutoConfigItem*> items;
    // 4.数组的观察者id
    std::map<AutoConfigItem *, SubscriberId> observers;
public:
    AutoConfigItemArray(ConfigValueType type);
    // 操作
    // 1.添加元素
    AutoConfigItem * addItem(AutoConfigItem * item);
    AutoConfigItem * addItem(ConfigValue item, ConfigValueType type = ConfigValueType::Undefined);
    // 2.删除元素
    AutoConfigItem * removeItem(AutoConfigItem * item);
    AutoConfigItem * removeItem(int index);
    // 3.获取元素
    AutoConfigItem * getItem(int index);
    AutoConfigItem * getItem(const ConfigValue &);
    // 4.获取数组长度
    int size();
    // 5.获取数组元素类型
    ConfigValueType getType();
    // 序列化 json , 反序列化 json
    nlohmann::json toJson();
    void fromJson(nlohmann::json);

};


#endif //CHATGPT_SIDEBAR_AUTOCONFIGITEMARRAY_H
