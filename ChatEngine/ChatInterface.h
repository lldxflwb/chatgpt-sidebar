//
// Created by 陈嘉乐 on 2023/8/12.
//

#ifndef CHATGPT_SIDEBAR_CHATINTERFACE_H
#define CHATGPT_SIDEBAR_CHATINTERFACE_H

#include <QString>
#include <map>
#include "utils/PubSub.h"
#include <QWidget>

enum class ApiStatus{
    start,
    sending,
    finish,
    error
};

typedef Publisher<QString, ApiStatus> ChatPublisher;

class ChatInterface : public ChatPublisher{
public:
    enum class OutPutEnum{
        single,
        stream
    };
    OutPutEnum outPutEnum;

    virtual ~ChatInterface();

    explicit ChatInterface(OutPutEnum outPutEnum);

    ChatInterface();

    virtual void OnInput(const QString& input) = 0;
    virtual void OnStop() = 0;
};


#endif //CHATGPT_SIDEBAR_CHATINTERFACE_H
