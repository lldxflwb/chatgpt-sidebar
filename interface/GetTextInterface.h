//
// Created by 48449 on 2023/4/21.
//

#ifndef CHATGPT_SIDEBAR_GETTEXTINTERFACE_H
#define CHATGPT_SIDEBAR_GETTEXTINTERFACE_H

#include "../Base/ChatgptBase.h"
#include <Windows.h>
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
    static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
    static QMimeData* cloneMimeData(const QMimeData* original);
    static LRESULT CALLBACK HookProc(int code, WPARAM wParam, LPARAM lParam);

    void installMouseHook();
    void uninstallMouseHook();

    void installKeyboardHook();

    void uninstallKeyboardHook();
};


#endif //CHATGPT_SIDEBAR_GETTEXTINTERFACE_H
