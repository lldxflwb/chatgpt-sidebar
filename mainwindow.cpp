#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QClipboard>
#include <QTimer>
#include <QKeySequence>
#include <QLabel>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings >
#include <QMouseEvent>
HHOOK MainWindow::mouseHook = nullptr;
MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),clicked_button(false)
{
    setting_ui = new SettingsDialog();
    setting_ui->show();
    this->hide();
    qDebug() << "开始初始化窗口";
    ui->setupUi(this);
    this->setWindowTitle("主窗口");
    m_setting = setting_ui->m_settings;
//    setting = new QSettings("sidebar.ini", QSettings::IniFormat);
    setWindowTitle("全局鼠标事件监听示例");
    installMouseHook();
    instance = this;
    this->bar = new LineBar();
    this->bar->talk = this;
    this->out = ui->out_put_text_2;
    // 设置窗口标志，使其成为顶层窗口
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    iconLabel = new ClickableLabel(this);
    iconLabel->setFixedSize(24, 24);
    iconLabel->setStyleSheet("background-color: red;"); // 为了便于识别，将图标的背景颜色设置为红色
    iconLabel->hide(); // 在初始状态下隐藏图标
    // 连接 clicked 信号到槽函数
    connect(iconLabel, &ClickableLabel::clicked, this, &MainWindow::iconLabelClicked);
    setupNetworkManager();
}
// 槽函数：当 iconLabel 被点击时调用
void MainWindow::iconLabelClicked()
{
    // 显示一个文本窗口
    MainWindow::getInstance()->clicked_button = true;
//    fetchAnswerFromGPT3(MainWindow::getInstance()->iconLabel->select_text);
    MainWindow::getInstance()->iconLabel->hide();
    MainWindow::getInstance()->hide();
//    QMessageBox::information(this, tr("选中的文本"), tr("这里是选中的文本的详细信息。"));
}
MainWindow* MainWindow::getInstance()
{
    return instance;
}
MainWindow::~MainWindow()
{
    delete ui;
        uninstallMouseHook();
}


void MainWindow::installMouseHook()
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

void MainWindow::uninstallMouseHook()
{
    if (mouseHook)
    {
        UnhookWindowsHookEx(mouseHook);
        mouseHook = nullptr;
    }
}
QMimeData* MainWindow::cloneMimeData(const QMimeData* original)
{
    QMimeData* cloned = new QMimeData();
    for (const QString& format : original->formats())
    {
        cloned->setData(format, original->data(format));
    }
    return cloned;
}

LRESULT CALLBACK MainWindow::mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
            case WM_LBUTTONUP:
            {
            if(MainWindow::getInstance()->clicked_button){
                MainWindow::getInstance()->clicked_button = false;
                return CallNextHookEx(mouseHook, nCode, wParam, lParam);;
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
                    // 比较剪贴板的当前内容与备份内容
                    const QMimeData* newMimeData = clipboard->mimeData();
                    if (newMimeData && (!mimeDataBackup || !newMimeData->data(QStringLiteral("text/plain")).isEmpty()) && newMimeData->text() != mimeDataBackup->text())
                    {
                        auto text =  newMimeData->text();
                        qDebug() << "选中的文本:" << text;
                        // 创建图标
                        // 显示图标
                        MainWindow::getInstance()->bar->aim_text = text;

                        // 显示 MainWindow
                        MainWindow::getInstance()->bar->show();
                        // 移动 MainWindow 到响应位置
                        QPoint cursorPos = QCursor::pos();
                        MainWindow::getInstance()->bar->move(cursorPos + QPoint(10, 10));
                        // 使用备份数据恢复剪贴板
                        clipboard->setMimeData(mimeDataBackup.release());
                    }
                });
            }
            break;
        }
    }

    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}



void MainWindow::on_close_button_2_clicked()
{
    exit(0);
}

void MainWindow::TalkWithChatgpt(QString text, QString prompt) {

}

void MainWindow::fetchAnswerFromGPT3(const QString &text) {
    this->ui->i_2->setText(text);
    QUrl url("https://api.openai.com/v1/chat/completions");
    cache_text = "";
    this->show();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    request.setRawHeader("OpenAI-Organization", "org-czN24sxhQjpKxcATiidkrSzG");
//    request.setRawHeader("Authorization", "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");
    auto key = "Bearer "+m_setting->value("key").toString();
    request.setRawHeader("Authorization", key.toUtf8());
    QJsonObject jsonBody;
    jsonBody["model"] = "gpt-3.5-turbo";

    QJsonArray messages;
    QJsonObject message;
    message["role"] = "user";
    message["content"] = text;
    messages.append(message);
    jsonBody["messages"] = messages;
    jsonBody["stream"] = true;
    QByteArray jsonString = QJsonDocument(jsonBody).toJson();
    // 转换为 QObject* 类型
    const QObject* receiver = static_cast<const QObject*>(qobject_cast<QObject*>(this));;
    QNetworkReply *reply = networkManager->post(request, jsonString);
    connect(reply, &QNetworkReply::readyRead, this, &MainWindow::handleApiResponse);
}

void MainWindow::handleApiResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    // 检查网络错误
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        return;
    }

    // 读取响应数据
    QByteArray data = reply->readAll();
    QTextStream stream(data);
// 解析数据字段
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.startsWith("data:")) {
            QString jsonStr = line.mid(5);
            qDebug() << "one line:" << jsonStr;

            // 将 JSON 字符串转换为 QJsonDocument
            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

            // 如果 JSON 文档不为空且不是空对象，则进行解析
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();

                QString id = jsonObject["id"].toString();
                QString object = jsonObject["object"].toString();
                qint64 created = jsonObject["created"].toDouble();
                QString model = jsonObject["model"].toString();

                qDebug() << "id:" << id;
                qDebug() << "object:" << object;
                qDebug() << "created:" << created;
                qDebug() << "model:" << model;

                QJsonArray choicesArray = jsonObject["choices"].toArray();

                // 遍历 choices 数组
                for (int i = 0; i < choicesArray.size(); ++i) {
                    QJsonObject choiceObject = choicesArray[i].toObject();

                    QJsonObject deltaObject = choiceObject["delta"].toObject();
                    QString role = deltaObject["role"].toString();
                    QString content = deltaObject["content"].toString();

                    int index = choiceObject["index"].toInt();
                    QString finishReason = choiceObject["finish_reason"].toString();
                    MainWindow::getInstance()->cache_text += content;
                    MainWindow::getInstance()->ui->out_put_text_2->setText(MainWindow::getInstance()->cache_text);
//                    MainWindow::getInstance()->ui->out_put_text_2->insertPlainText(content);
                    MainWindow::getInstance()->ui->out_put_text_2->moveCursor(QTextCursor::End);
                    qDebug() << "role:" << role;
                    qDebug() << "content:" << content;
                    qDebug() << "index:" << index;
                    qDebug() << "finish_reason:" << finishReason;
                }
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
}


void MainWindow::on_pushButton_4_clicked()
{
setting_ui->show();
}

void MainWindow::showSetting() {
    this->setting_ui->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标按下时窗口的位置
        m_dragPos = event->globalPos() - frameGeometry().topLeft();
        // 标记为可拖动
        m_dragging = true;
        // 设置鼠标指针为拖动状态
        setCursor(QCursor(Qt::SizeAllCursor));
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging) {
        // 移动窗口
        move(event->globalPos() - m_dragPos);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_dragging) {
        // 标记为不可拖动
        m_dragging = false;
        // 恢复鼠标指针状态
        unsetCursor();
        event->accept();
    }
}
