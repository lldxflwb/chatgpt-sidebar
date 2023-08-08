//
// Created by 陈嘉乐 on 2023/8/7.
//

#ifndef CHATGPT_SIDEBAR_AUTOCONFIGITEM_H
#define CHATGPT_SIDEBAR_AUTOCONFIGITEM_H

#include <variant>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

using ConfigValue = std::variant<int, double, std::string>;
enum class ConfigValueType {
    Int,
    Double,
    String
};

class AutoConfigItem {
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
    virtual std::pair<ConfigValueType, const ConfigValue> getValueAsPair() const;
    virtual ConfigValue getValue() const;
    void addObserver(const std::function<void(const ConfigValue&)>& observer);
private:
    void notify(const ConfigValue &value) const;
};



#endif //CHATGPT_SIDEBAR_AUTOCONFIGITEM_H
