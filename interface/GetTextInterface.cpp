//
// Created by 48449 on 2023/4/21.
//

#include "GetTextInterface.h"
#include <QDebug>
#include <QApplication>
#include <QDebug>
#include <QClipboard>
#include <QTimer>
GetTextInterface::GetTextInterface() :GetTextInterface(ChatgptBase::UseMode::DefaultMode,""){
}

GetTextInterface::GetTextInterface(ChatgptBase::UseMode mode, const QString &text)  {
    this->chat = ChatgptBase::getInstance();
    this->chat->mode = mode;
    this->chat->text = text;
    if (ChatgptBase::UseMode::DefaultMode == chat->mode){
        installMouseHook();
    }
}

GetTextInterface::~GetTextInterface() {
    if (ChatgptBase::UseMode::DefaultMode == chat->mode ){
        uninstallMouseHook();
    }
}

void GetTextInterface::ChangeMode(ChatgptBase::UseMode mode_) {
    if (ChatgptBase::UseMode::DefaultMode == chat->mode ){
        uninstallMouseHook();
    }
    else if(ChatgptBase::UseMode::CCMode == chat->mode){
        uninstallKeyboardHook();
    }
    if (ChatgptBase::UseMode::DefaultMode == mode_){
        installMouseHook();
    }else if (ChatgptBase::UseMode::CCMode == mode_){
        installKeyboardHook();
    }
    chat->mode = mode_;
}

LRESULT CALLBACK GetTextInterface::mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    ChatgptBase * chat = ChatgptBase::getInstance();
    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
            case WM_LBUTTONUP:
            {

                if(ChatgptBase::UseMode::DefaultMode != chat->mode){
                    return CallNextHookEx(chat->mouseHook, nCode, wParam, lParam);;
                }
                qDebug() << "鼠标左键释放";
                // 备份剪贴板内容
                QClipboard* clipboard = QApplication::clipboard();
                const QMimeData* oldMimeData = clipboard->mimeData();
                std::unique_ptr<QMimeData> mimeDataBackup(oldMimeData ? cloneMimeData(oldMimeData) : nullptr);

                // 发送 Ctrl+C（复制）按键事件
                keybd_event(VK_CONTROL, 0, 0, 0);
                keybd_event('C', 0, 0, 0);
                keybd_event('C', 0, KEYEVENTF_KEYUP, 0);
                keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

                // 延迟检查剪贴板以确保选中的文本已被复制
                QTimer::singleShot(100, [mimeDataBackup=std::move(mimeDataBackup),clipboard]() mutable
                {
                    ChatgptBase * chat = ChatgptBase::getInstance();
                    // 比较剪贴板的当前内容与备份内容
                    const QMimeData* newMimeData = clipboard->mimeData();
                    if (newMimeData && (!mimeDataBackup || !newMimeData->data(QStringLiteral("text/plain")).isEmpty()) && newMimeData->text() != mimeDataBackup->text())
                    {
                        auto text =  newMimeData->text();
                        qDebug() << "选中的文本:" << text;
                        chat->text = text;
                        emit chat->textChanged(text);
                    }
                });
            }
                break;
        }
    }

    return CallNextHookEx(chat->mouseHook, nCode, wParam, lParam);
}

QMimeData* GetTextInterface::cloneMimeData(const QMimeData* original)
{
    QMimeData* cloned = new QMimeData();
    for (const QString& format : original->formats())
    {
        cloned->setData(format, original->data(format));
    }
    return cloned;
}

void GetTextInterface::installMouseHook()
{
    if (!chat->mouseHook)
    {
        chat->mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, GetModuleHandle(nullptr), 0);
        if (!chat->mouseHook)
        {
            qWarning() << "无法安装鼠标钩子";
        }
    }
}

void GetTextInterface::uninstallMouseHook()
{
    if (chat->mouseHook)
    {
        UnhookWindowsHookEx(chat->mouseHook);
        chat->mouseHook = nullptr;
    }
}

// 消息处理函数
LRESULT CALLBACK GetTextInterface::HookProc(int code, WPARAM wParam, LPARAM lParam) {
    // 判断是否按下 Ctrl+C
    if (code == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        if (p->vkCode == 'C' && GetAsyncKeyState(VK_CONTROL)) {
            // 延迟检查剪贴板以确保选中的文本已被复制
            QTimer::singleShot(100, []() mutable
            {
                auto * chat = ChatgptBase::getInstance();
                // 获取剪贴板实例
                QClipboard* clipboard = QApplication::clipboard();

                // 判断剪贴板中是否有文本数据
                if (!clipboard->mimeData()->hasText()) {
//                    qDebug() << "No text data in clipboard!";
                    return ;
                }

                // 获取剪贴板中的文本数据
                QString text = clipboard->mimeData()->text();

                // 输出剪切板文本内容
//                qDebug() << "Clipboard text: " << text;
                chat->text = text;
                emit chat->textChanged(text);
            });
        }
    }

    // 将消息传递给下一个钩子
    return CallNextHookEx(ChatgptBase::getInstance()->keyboardHook, code, wParam, lParam);
}

void GetTextInterface::installKeyboardHook() {
    if (chat->keyboardHook != nullptr) {
        return ;
    }

    chat->keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, nullptr, 0);
    if (chat->keyboardHook == nullptr) {
        return ;
    }
    return ;
}

void GetTextInterface::uninstallKeyboardHook() {
    if (chat->keyboardHook != nullptr) {
        UnhookWindowsHookEx(chat->keyboardHook);
        chat->keyboardHook = nullptr;
    }
}
