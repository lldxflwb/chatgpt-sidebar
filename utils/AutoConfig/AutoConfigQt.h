// AutoConfigQt.h

#ifndef CHATGPT_AUTOCONFIGQT_H
#define CHATGPT_AUTOCONFIGQT_H

#include <QString>
#include "AutoConfig.h"
#include "AutoConfigItemQt.h"

class AutoConfigQt : public AutoConfig {
public:
    using AutoConfig::AutoConfig;

    void addItem(const std::string& key, const QString& value);
    QString getItemAsQString(const QString & key) const;
    const AutoConfigItemQt * getItemQt(const QString & key) const;
};

#endif // CHATGPT_AUTOCONFIGQT_H
