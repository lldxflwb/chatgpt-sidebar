//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "AutoConfigItem.h"

void AutoConfigItem::setValue(std::pair<ConfigValueType, ConfigValue> newValue) {
    if (value != newValue.second) {
        value = newValue.second;
        type = newValue.first;
        Notify(newValue.second, this->type,AutoConfigItemEvent::ValueChanged);
    }
}

ConfigValue AutoConfigItem::getValue() const {
    return value;
}

//SubscriberId AutoConfigItem::RegisterObserver(const std::function<void(const ConfigValue&)>& observer) {
//    observers.push_back(observer);
//}
//
//void AutoConfigItem::Notify(const ConfigValue &value, ConfigValueType valueType) const {
//    for (const auto& observer : observers) {
//        observer(value);
//    }
//}

void AutoConfigItem::setString(const std::string &newValue) {
    std::pair<ConfigValueType, ConfigValue> v_n ;
    v_n.first = ConfigValueType::String;
    v_n.second = newValue;
    setValue(v_n);
}

void AutoConfigItem::setInt(int newValue) {
    ConfigValue v ;
    v = newValue;
    setValue(std::make_pair(ConfigValueType::Int, v));
}

void AutoConfigItem::setDouble(double newValue) {
    ConfigValue v;
    v = newValue;
    setValue(std::make_pair(ConfigValueType::Double, v));
}

void AutoConfigItem::setJson(nlohmann::json j) {
    ConfigValue v;
    v = j;
    setValue(std::make_pair(ConfigValueType::Json, v));
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

void AutoConfigItem::toJson(nlohmann::json & item,std::string key) {
    std::visit([key,&item](auto& v){
        item[key] = v;
    },this->value);
}

void AutoConfigItem::fromJson(nlohmann::json & item,std::string key) {
    if (item.find(key) == item.end()){
        return;
    }
    auto value = item[key];
    if (value.is_number_integer()) {
        this->setInt(value.get<int>());
    } else if (value.is_number_float()) {
        this->setDouble(value.get<double>());
    } else if (value.is_string()) {
        this->setString(value.get<std::string>());
    }
    else{
        throw std::runtime_error(key + " is not a valid type");
    }
}
