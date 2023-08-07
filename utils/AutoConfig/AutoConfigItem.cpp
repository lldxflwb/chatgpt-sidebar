//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "AutoConfigItem.h"

void AutoConfigItem::setValue(const ConfigValue& newValue) {
    if (value != newValue) {
        value = newValue;
        notify(newValue);
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
