//
// Created by 48449 on 2023/4/21.
//

#include "GetTextInterface.h"
#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <QTimer>
#include <thread>
#include <QMessageBox>

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

#if defined(Q_OS_WIN)
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
#endif

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
#if defined(Q_OS_WIN)
    if (!chat->mouseHook)
    {
        chat->mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, GetModuleHandle(nullptr), 0);
        if (!chat->mouseHook)
        {
            qWarning() << "无法安装鼠标钩子";
        }
    }

#endif
}

void GetTextInterface::uninstallMouseHook()
{
#if defined(Q_OS_WIN)
    if (chat->mouseHook)
    {
        UnhookWindowsHookEx(chat->mouseHook);
        chat->mouseHook = nullptr;
    }
#endif
}

#if defined(Q_OS_WIN)
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
#elif defined(Q_OS_MACOS)
CGEventRef GetTextInterface::keyEventHandler(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon)
{
    // 获取按键的键码和修饰键
    CGKeyCode keyCode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    CGEventFlags flags = CGEventGetFlags(event);

    //    std::cout <<keyCode << std::endl;
    // 判断是否按下了a键
    if (keyCode == 8 && (flags & kCGEventFlagMaskCommand) != 0) {
        std::thread([](){
            // 延迟检查剪贴板以确保选中的文本已被复制
            std::this_thread::sleep_for(std::chrono::microseconds(100));
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
        }).detach();
    }

    // 返回事件给下一个处理器
    return event;
}

#endif

void GetTextInterface::installKeyboardHook() {
    if(chat == nullptr){
        return;
    }
#if defined(Q_OS_WIN)
    if (chat->keyboardHook != nullptr) {
        return ;
    }

    chat->keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, nullptr, 0);
    if (chat->keyboardHook == nullptr) {
        return ;
    }
    return ;
#elif defined(Q_OS_MACOS)
    // 定义一个事件类型列表，包含我们感兴趣的事件类型和类别
    qDebug() << "install mac key borad";
    // 判断是否拿到了权限
    if (!AXIsProcessTrustedWithOptions(NULL)) {
        // 弹窗 提示用户打开辅助功能
        QMessageBox::information(NULL, "提示", "请打开辅助功能", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        // 获取当前程序的路径
        QString path = QCoreApplication::applicationDirPath();
        // 转化为 CFStringRef
        CFStringRef pathRef = CFStringCreateWithCString(NULL, path.toStdString().c_str(), kCFStringEncodingUTF8);
        // 申请权限 AXMakeProcessTrusted 获取申请结果
        auto result = AXMakeProcessTrusted(pathRef);
        // 判断是否申请成功
        if (result) {
            qDebug() << "申请成功";
        } else {
            qDebug() << "申请失败";
        }
        return ;
    }
    std::thread my_thread([this](){
        chat->eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionListenOnly, kCGEventMaskForAllEvents, keyEventHandler, NULL);
        // 检查事件源是否创建成功
        if (!chat->eventTap) {
            qDebug() << "Failed to create event tap." ;
            return ;
        }
        // 创建一个事件循环源，用于将事件源添加到事件循环中
        CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, chat->eventTap, 0);

        // 将事件循环源添加到当前线程的事件循环中
        CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);

        // 启用事件源
        CGEventTapEnable(chat->eventTap, true);

        // 运行一个事件循环，等待用户输入
        CFRunLoopRun();
    });
    my_thread.detach();
#endif
}

void GetTextInterface::uninstallKeyboardHook() {
#if defined(Q_OS_WIN)
    if (chat->keyboardHook != nullptr) {
        UnhookWindowsHookEx(chat->keyboardHook);
        chat->keyboardHook = nullptr;
    }
#elif defined(Q_OS_MACOS)
//    qDebug() << "disable mac key borad";
    // 注销事件处理器，并将handlerRef置空
//    RemoveEventHandler(chat->handlerRef);
//    chat->handlerRef = NULL;
#endif
}
