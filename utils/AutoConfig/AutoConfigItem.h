//
// Created by 陈嘉乐 on 2023/8/7.
//

#ifndef CHATGPT_SIDEBAR_AUTOCONFIGITEM_H
#define CHATGPT_SIDEBAR_AUTOCONFIGITEM_H

#include <variant>
#include <string>
#include <unordered_map>
#include <functional>
#include "utils/PubSub.h"
#include <vector>
#include "nlohmann/json.hpp"

using ConfigValue = std::variant<int, double, std::string,nlohmann::json>;

enum ConfigValueType {
    Undefined,
    Int,
    Double,
    String,
    Json
};

enum class AutoConfigItemEvent{
    ValueChanged,
    NodeBeDeleted
};

typedef Publisher<const ConfigValue &, ConfigValueType,AutoConfigItemEvent> AutoConfigItemPublisher;


class AutoConfigItem : public AutoConfigItemPublisher{
private:
    ConfigValue value;
    ConfigValueType type;
    std::vector<std::function<void(const ConfigValue&)>> observers;

public:
    virtual void setValue(const ConfigValue& newValue);
    virtual void setValue(std::pair<ConfigValueType, ConfigValue> newValue);
    virtual void setString(const std::string& newValue);
    virtual void setInt(int newValue);
    virtual void setDouble(double newValue);
    virtual void setJson(nlohmann::json j);
    virtual std::pair<ConfigValueType, const ConfigValue> getValueAsPair() const;
    virtual ConfigValue getValue() const;
    // 序列化 反序列化
    void toJson(nlohmann::json & item,std::string key);
    void fromJson(nlohmann::json & item,std::string key);
};


#endif //CHATGPT_SIDEBAR_AUTOCONFIGITEM_H
