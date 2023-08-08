// AutoConfigItemQt.cpp

#include "AutoConfigItemQt.h"

void AutoConfigItemQt::setValue(const QString& value) {
    AutoConfigItem::setValue(std::make_pair(ConfigValueType::String,value.toStdString()));
}

QString AutoConfigItemQt::getValueAsQString() const {
    auto v = AutoConfigItem::getValue();
    auto s = std::get<std::string>(v);
    return QString::fromStdString(s);
}
