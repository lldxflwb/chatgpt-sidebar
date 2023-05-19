//
// Created by 48449 on 2023/5/5.
//

#ifndef CHATGPT_SIDEBAR_CHATGPTBASE_H
#define CHATGPT_SIDEBAR_CHATGPTBASE_H

#include <QString>
#if defined(Q_OS_WIN)
#include <Windows.h>
#elif defined(Q_OS_MACOS)
//#include "Carbon/Carbon.h"
#include <ApplicationServices/ApplicationServices.h>
#endif

#include <QObject>

class ChatgptBase : public QObject {
    Q_OBJECT
public:
    enum UseMode {
        DefaultMode,
        CCMode,
        DefinedKeyMode,
    };
    UseMode mode;
    QString text;
#if defined(Q_OS_WIN)
    HHOOK keyboardHook;
    HHOOK mouseHook;
#elif defined(Q_OS_MACOS)
    CFMachPortRef  eventTap;
#endif
    // 获取 ChatgptBase 实例的静态成员函数
    static ChatgptBase* getInstance();

signals:
    // 文本变更信号
    void textChanged(const QString& newText);

private:
    // 私有化构造函数和析构函数，以防止创建多个实例和直接删除实例
    ChatgptBase();
    ~ChatgptBase();

    // 静态变量，用于保存唯一的 ChatgptBase 实例
    static ChatgptBase* instance_;
};

#endif //CHATGPT_SIDEBAR_CHATGPTBASE_H
