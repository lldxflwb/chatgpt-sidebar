//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "AutoConfigItem.h"

void AutoConfigItem::setValue(std::pair<ConfigValueType, ConfigValue> newValue) {
    if (value != newValue.second) {
        value = newValue.second;
        type = newValue.first;
        notify(newValue.second);
    }
}

ConfigValue AutoConfigItem::getValue() const {
    return value;
}

void AutoConfigItem::addObserver(const std::function<void(const ConfigValue&)>& observer) {
    observers.push_back(observer);
}

void AutoConfigItem::notify(const ConfigValue& newValue) const {
    for (const auto& observer : observers) {
        observer(newValue);
    }
}

void AutoConfigItem::setString(const std::string &newValue) {
    std::pair<ConfigValueType, ConfigValue> v_n ;
    v_n.first = ConfigValueType::String;
    v_n.second = newValue;
    setValue(v_n);
}

void AutoConfigItem::setInt(int newValue) {
    setValue(std::make_pair(ConfigValueType::Int, newValue));
}

void AutoConfigItem::setDouble(double newValue) {
    setValue(std::make_pair(ConfigValueType::Double, newValue));
}

std::pair<ConfigValueType, const ConfigValue> AutoConfigItem::getValueAsPair() const {
    return std::make_pair(type, value);
}

void AutoConfigItem::setValue(const ConfigValue &newValue) {
    int index = newValue.index();
    ConfigValueType currType = static_cast<ConfigValueType>(index);
    switch(currType){
        case ConfigValueType::Int:
            setInt(std::get<int>(newValue));
            break;
        case ConfigValueType::Double:
            setDouble(std::get<double>(newValue));
            break;
        case ConfigValueType::String:
            setString(std::get<std::string>(newValue));
            break;
        default:
            assert("Change Index to enum Type ConfigValueType error");
    }
}
