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

class AutoConfigItem {
private:
    ConfigValue value;
    std::vector<std::function<void(const ConfigValue&)>> observers;

public:
    void setValue(const ConfigValue &value);
    ConfigValue getValue() const;
    void addObserver(const std::function<void(const ConfigValue&)>& observer);

private:
    void notify(const ConfigValue &value) const;
};



#endif //CHATGPT_SIDEBAR_AUTOCONFIGITEM_H
