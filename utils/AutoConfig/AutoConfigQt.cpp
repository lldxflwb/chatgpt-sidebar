// AutoConfigQt.cpp

#include "AutoConfigQt.h"

void AutoConfigQt::addQString(const std::string& key, const QString& value) {
    ConfigValue v = value.toStdString();
    addItems(key, v);
}

QString AutoConfigQt::getItemAsQString(const QString & key) {
    auto item = getItemQt(key);
    if(item != nullptr) {
        return item->getValueAsQString();
    }
    return "";
}

 AutoConfigItemQt *AutoConfigQt::getItemQt(const QString &key) {
    auto k = key.toStdString();
    auto item = getItem(k);
    return static_cast< AutoConfigItemQt *>(item);
}

AutoConfigQt::AutoConfigQt(const std::string &fileName) : AutoConfig(fileName) {}
