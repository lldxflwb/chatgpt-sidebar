// AutoConfigQt.h

#ifndef CHATGPT_AUTOCONFIGQT_H
#define CHATGPT_AUTOCONFIGQT_H

#include <QString>
#include "AutoConfig.h"
#include "AutoConfigItemQt.h"

class AutoConfigQt : public AutoConfig {
public:
    using AutoConfig::AutoConfig;

    explicit AutoConfigQt(const std::string &fileName);

    void addQString(const std::string& key, const QString& value);
    QString getItemAsQString(const QString & key) ;
    AutoConfigItemQt * getItemQt(const QString & key) ;
};

#endif // CHATGPT_AUTOCONFIGQT_H
