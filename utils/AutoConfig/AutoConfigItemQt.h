// AutoConfigItemQt.h

#ifndef CHATGPT_AUTOCONFIGITEMQT_H
#define CHATGPT_AUTOCONFIGITEMQT_H

#include <QString>
#include "AutoConfigItem.h"

class AutoConfigItemQt : public AutoConfigItem {
public:
    using AutoConfigItem::AutoConfigItem;

    void setValue(const QString& value);
    QString getValueAsQString() const;
};

#endif // CHATGPT_AUTOCONFIGITEMQT_H
