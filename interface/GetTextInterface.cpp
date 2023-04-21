//
// Created by 48449 on 2023/4/21.
//

#include "GetTextInterface.h"
#include <QDebug>


GetTextInterface::GetTextInterface() :GetTextInterface(UseMode::DefaultMode,""){
    if (UseMode::DefaultMode == mode){
        installMouseHook();
    }
}

GetTextInterface::GetTextInterface(GetTextInterface::UseMode mode, const QString &text) : mode(mode), text(text) {

}

GetTextInterface::~GetTextInterface() {
    if (UseMode::DefaultMode == mode ){
        uninstallMouseHook();
    }
}

void GetTextInterface::ChangeMode(GetTextInterface::UseMode mode_) {
    if (UseMode::DefaultMode == mode ){
        uninstallMouseHook();
    }
    if (UseMode::DefaultMode == mode_){
        installMouseHook();
    }
}

void GetTextInterface::installMouseHook()
{
    if (!mouseHook)
    {
        mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, GetModuleHandle(nullptr), 0);
        if (!mouseHook)
        {
            qWarning() << "无法安装鼠标钩子";
        }
    }
}

void GetTextInterface::uninstallMouseHook()
{
    if (mouseHook)
    {
        UnhookWindowsHookEx(mouseHook);
        mouseHook = nullptr;
    }
}