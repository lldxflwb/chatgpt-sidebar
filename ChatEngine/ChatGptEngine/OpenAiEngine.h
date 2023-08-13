//
// Created by 陈嘉乐 on 2023/8/12.
//

#ifndef CHATGPT_SIDEBAR_OPENAIENGINE_H
#define CHATGPT_SIDEBAR_OPENAIENGINE_H

#include "ChatEngine/ChatInterface.h"


class OpenAiEngine : public ChatInterface {
public:
    void OnInput(const QString &input) override;

    void OnStop() override;
};


#endif //CHATGPT_SIDEBAR_OPENAIENGINE_H
