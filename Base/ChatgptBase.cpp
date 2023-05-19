//
// Created by 48449 on 2023/5/5.
//

#include "ChatgptBase.h"

// 初始化静态变量 instance_
ChatgptBase* ChatgptBase::instance_ = nullptr;

// 获取 ChatgptBase 实例的静态成员函数实现
ChatgptBase* ChatgptBase::getInstance() {
    if (instance_ == nullptr) {
        instance_ = new ChatgptBase();
    }
    return instance_;
}

// 私有化构造函数和析构函数的实现
ChatgptBase::ChatgptBase() {
    mode = DefaultMode;
    text = "";
#if defined(Q_OS_WIN)
    keyboardHook = nullptr;
    mouseHook = nullptr;
#endif
}

ChatgptBase::~ChatgptBase() {
#if defined(Q_OS_WIN)
    // 在析构函数中清理资源
    if (keyboardHook != nullptr) {
        UnhookWindowsHookEx(keyboardHook);
    }
    if (mouseHook != nullptr) {
        UnhookWindowsHookEx(mouseHook);
    }
    keyboardHook = nullptr;
    mouseHook = nullptr;
#endif
}
