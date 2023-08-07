// AutoConfigQt.cpp

#include "AutoConfigQt.h"

void AutoConfigQt::addItem(const std::string& key, const QString& value) {
    ConfigValue v = value.toStdString();
    addItems(key, v);
}

QString AutoConfigQt::getItemAsQString(const QString & key) const {
    auto item = getItemQt(key);
    if(item != nullptr) {
        return item->getValueAsQString();
    }
    return "";
}

const AutoConfigItemQt *AutoConfigQt::getItemQt(const QString &key) const {
    auto k = key.toStdString();
    auto item = getItem(k);
    return static_cast<const AutoConfigItemQt *>(item);
}
