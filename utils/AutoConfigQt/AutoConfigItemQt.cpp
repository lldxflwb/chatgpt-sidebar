// AutoConfigItemQt.cpp

#include "AutoConfigItemQt.h"

void AutoConfigItemQt::setValue(const QString& value) {
    auto v = value.toStdString();
    // deep copy
    std::string n_v(v.c_str(),v.length());
    AutoConfigItem::setString(n_v);
}

QString AutoConfigItemQt::getValueAsQString() const {
    auto v = AutoConfigItem::getValue();
    auto s = std::get<std::string>(v);
    return QString::fromStdString(s);
}
