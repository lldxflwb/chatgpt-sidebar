//
// Created by 48449 on 2023/4/21.
//

#ifndef CHATGPT_SIDEBAR_GETTEXTINTERFACE_H
#define CHATGPT_SIDEBAR_GETTEXTINTERFACE_H

#include <Windows.h>
#include <QString>

class GetTextInterface {
public:
    enum UseMode{
        DefaultMode,//默认选项，划词，直接托管剪贴板，查询是否有选中文本，有则浮现linebar
        CCMode ,//按下ctrl c，即进行复制操作后，获取剪贴板第一条，并在鼠标旁复习linebar
        DefinedKeyMode , //按下自定义按键后，直接托管剪切版，查询是否有选中文本，有则浮现linebar
    };
    UseMode mode ;
    QString text;

    GetTextInterface(UseMode mode, const QString &text);

    GetTextInterface();

private:
    static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
    static HHOOK mouseHook;
private:
    void installMouseHook();
    void uninstallMouseHook();
};


#endif //CHATGPT_SIDEBAR_GETTEXTINTERFACE_H
