//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "TestFunc.h"


#include "utils/MySetting/KeyInfo/ChatGptKey.h"
#include "ChatEngine/ChatGptEngine/OpenAiEngine.h"

#include "ChatEngine/BaiduEngine/BaiduEngine.h"
#include <variant>
#include <QTextEdit>
#include "utils/MySetting/Panel/EnginePanel.h"

void TestFunc::TestProxyConfigWidgetPublic() {
//    auto pconfig = std::make_shared<ProxyActionHttp::ProxyConfigHttp>("","6863","","");
//    ProxyConfigWidgetPublic * p = new ProxyConfigWidgetPublic(pconfig);
//    p->show();
}

void TestFunc::TestChatGptConfig() {
    ChatInterface *chat = new BaiduEngine();
    auto w = new ChatGptKey("111");
    w->autoConfigQt->readFile();
    w->show();
    TestChat(chat);
}

void TestFunc::TestChat(ChatInterface *chat) {

    static QWidget * t ;
    static QTextEdit * text_edit;
    static QHBoxLayout * layout;
    static QString * cache;
    if(t== nullptr){
        t=new QWidget();
        text_edit = new QTextEdit(t);
        layout = new QHBoxLayout(t);
        layout->addWidget(text_edit);
        t->setLayout(layout);
        t->show();
        cache= new QString();
    }
    *cache = "";
    QString * tmp_cache = cache;
    QTextEdit * edit = text_edit;

    chat->RegisterObserver([edit,tmp_cache](QString text, ApiStatus status){
        *tmp_cache = *tmp_cache + text;
        edit->setText(*tmp_cache);
    });

    chat->OnInput("你是谁？请自我介绍一下，以及我该如何使用你？");
}

void TestFunc::TestBaidu() {
    BaiduEngine *chat = new BaiduEngine();
    TestChat(chat);
}

void TestFunc::TestPanel() {
    EnginePanel * panel = new EnginePanel(EngineType::Baidu);
    panel->show();
}
