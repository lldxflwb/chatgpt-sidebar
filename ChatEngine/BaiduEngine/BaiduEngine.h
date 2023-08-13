//
// Created by 陈嘉乐 on 2023/8/13.
//

#ifndef CHATGPT_SIDEBAR_BAIDUENGINE_H
#define CHATGPT_SIDEBAR_BAIDUENGINE_H

#include "ChatEngine/ChatInterface.h"
#include <QNetworkAccessManager>

class BaiduEngine : public ChatInterface {
public:
    void OnInput(const QString &input) override;
    void OnStop() override;

private:
    QString access_token;

    void getAccessToken(const QString &api_key, const QString &secret_key);
};


#endif //CHATGPT_SIDEBAR_BAIDUENGINE_H
