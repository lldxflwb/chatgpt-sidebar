//
// Created by 48449 on 2023/4/21.
//

#ifndef CHATGPT_SIDEBAR_GETTEXTINTERFACE_H
#define CHATGPT_SIDEBAR_GETTEXTINTERFACE_H

//#include "../Base/ChatgptBase.h"
#include "Base/ChatgptBase.h"
#include <QString>
#include <QMimeData>

class GetTextInterface {
public:
    ChatgptBase * chat;

    GetTextInterface(ChatgptBase::UseMode mode, const QString &text);

    virtual ~GetTextInterface();

    GetTextInterface();

    void ChangeMode(ChatgptBase::UseMode mode_);
//    virtual void ShowBar() = 0;
#if defined(Q_OS_WIN)
    static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK HookProc(int code, WPARAM wParam, LPARAM lParam);
#elif defined(Q_OS_MACOS)
    static CGEventRef keyEventHandler(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon);
#endif
    static QMimeData* cloneMimeData(const QMimeData* original);
    void installMouseHook();
    void uninstallMouseHook();

    void installKeyboardHook();

    void uninstallKeyboardHook();
};


#endif //CHATGPT_SIDEBAR_GETTEXTINTERFACE_H
