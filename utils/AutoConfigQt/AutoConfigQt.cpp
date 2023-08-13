// AutoConfigQt.cpp

#include "AutoConfigQt.h"

AutoConfigItemQt * AutoConfigQt::addQString(const std::string& key, const QString& value) {
    AutoConfigItemQt * item = new AutoConfigItemQt();
    item->setValue(value);
    return static_cast<AutoConfigItemQt*>(addItems(key, item));
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

AutoConfigQt::AutoConfigQt(const std::string &fileName, StoragePolicy _stroagePolicy, AutoConfigQt *_parent)
: AutoConfig(fileName, _stroagePolicy, _parent) {}
