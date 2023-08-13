//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "TestFunc.h"

#include "utils/MySetting/Proxy/ProxyConfigWidgetPublic.h"
#include "utils/MySetting/Proxy/ProxyActionHttp.h"
#include "utils/MySetting/KeyInfo/ChatGptKey.h"
#include "ChatEngine/ChatGptEngine/OpenAiEngine.h"
#include "ChatEngine/ChatInterface.h"
#include <variant>

void TestFunc::TestProxyConfigWidgetPublic() {
    auto pconfig = std::make_shared<ProxyActionHttp::ProxyConfigHttp>("","6863","","");
    ProxyConfigWidgetPublic * p = new ProxyConfigWidgetPublic(pconfig);
    p->show();
}

void TestFunc::TestChatGptConfig() {
    ChatInterface * chat = new OpenAiEngine();
    auto w = new ChatGptKey("111");
    w->autoConfigQt->readFile();
    w->show();
    QWidget * t = new QWidget();
    QLineEdit * text_edit = new QLineEdit(t);
    QHBoxLayout * layout = new QHBoxLayout(t);
    layout->addWidget(text_edit);
    t->setLayout(layout);
    t->show();

    chat->RegisterObserver([text_edit](QString text, ApiStatus status){
        qDebug() << text ;
        text_edit->setText(text_edit->text()+text);
    });

    chat->OnInput("hello");
}
