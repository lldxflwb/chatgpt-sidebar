//
// Created by lldx on 2024/2/2.
//

#ifndef CHATGPT_SIDEBAR_ZHIPUENGINE_H
#define CHATGPT_SIDEBAR_ZHIPUENGINE_H

#include "ChatEngine/ChatInterface.h"
#include <QNetworkAccessManager>
class ZhiPuEngine : public ChatInterface{
public:
    void OnInput(const QString &input) override;
    void OnStop() override;
};

#endif //CHATGPT_SIDEBAR_ZHIPUENGINE_H
