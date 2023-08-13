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
#include <QSettings>
#include <QMouseEvent>
#include "utils/MySetting/Proxy/ProxyManager.h"

extern QNetworkAccessManager * networkManager;
extern ProxyManager * proxyManager;

MainWindow *MainWindow::instance = nullptr;
QObject * globalWindow;
QWidget * aiNetwork;
QTextEdit * outPutTextArea;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), clicked_button(false), ui(new Ui::MainWindow) {
    proxyManager=new ProxyManager();
    setting_ui = new SettingsDialog();
    setting_ui->show();
    this->hide();
    aiNetwork = new QWidget();
    qDebug() << "开始初始化窗口";
    ui->setupUi(this);
    this->setWindowTitle("主窗口");
    m_setting = setting_ui->m_settings;
//    setting = new QSettings("sidebar.ini", QSettings::IniFormat);
    setWindowTitle("全局鼠标事件监听示例");
    outPutTextArea = this->ui->out_put_text_2;
    instance = this;
    globalWindow = this;
    this->bar = new LineBar();
    this->bar->settings_dialog = setting_ui;
    this->bar->InitButton();
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
    // 在其他地方连接自定义信号 mySignal() 和槽函数 mySlot()
    QObject::connect(chat, &ChatgptBase::textChanged, this, &MainWindow::ShowBar);
    setupNetworkManager();
    ChangeMode(ChatgptBase::UseMode::CCMode);
    connect(setting_ui, &SettingsDialog::SettingChangedSend, [this](QSettings *settings) {
        this->OnSettingChanged(settings);
    });
    connect(ui->action_button_2,&QPushButton::clicked,[this](bool checked = false){
        this->TalkWithGpt(this->ui->i_2->toPlainText(),this->ui->out_put_text_2);
    });
}

// 槽函数：当 iconLabel 被点击时调用
void MainWindow::iconLabelClicked() {
    // 显示一个文本窗口
    MainWindow::getInstance()->clicked_button = true;
//    fetchAnswerFromGPT3(MainWindow::getInstance()->iconLabel->select_text);
    MainWindow::getInstance()->iconLabel->hide();
    MainWindow::getInstance()->hide();
//    QMessageBox::information(this, tr("选中的文本"), tr("这里是选中的文本的详细信息。"));
}

MainWindow *MainWindow::getInstance() {
    return instance;
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_close_button_2_clicked() {
    exit(0);
}

void MainWindow::TalkWithChatgpt(QString text, QString prompt) {

}

void MainWindow::fetchAnswerFromGPT3(const QString &text) {
    this->setting_ui->engine_panel->cacheText ="";
    this->setting_ui->engine_panel->GetEngine()->OnInput(text);
    MainWindow::getInstance()->ui->out_put_text_2->moveCursor(QTextCursor::End);
    this->show();
    this->ui->i_2->setText(text);
//    QUrl url("https://api.openai.com/v1/chat/completions");
//    cache_text = "";
//    this->show();
//    QNetworkRequest request(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
////    request.setRawHeader("OpenAI-Organization", "org-czN24sxhQjpKxcATiidkrSzG");
////    request.setRawHeader("Authorization", "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");
//    auto key = "Bearer " + m_setting->value("key").toString();
//    request.setRawHeader("Authorization", key.toUtf8());
//    QJsonObject jsonBody;
//    jsonBody["model"] = "gpt-3.5-turbo";
//    QJsonArray messages;
//    QJsonObject message;
//    message["role"] = "user";
//    message["content"] = text;
//    messages.append(message);
//    jsonBody["messages"] = messages;
//    jsonBody["stream"] = true;
//    QByteArray jsonString = QJsonDocument(jsonBody).toJson();
//    // 转换为 QObject* 类型
//    const QObject *receiver = static_cast<const QObject *>(qobject_cast<QObject *>(this));;
//    QNetworkReply *reply = networkManager->post(request, jsonString);
//    connect(reply, &QNetworkReply::readyRead, this, &MainWindow::handleApiResponse);
}

void MainWindow::handleApiResponse() {
//    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
//
//    // 检查网络错误
//    if (reply->error() != QNetworkReply::NoError) {
//        QMessageBox::critical(this, tr("发生错误"), tr("网络错误"), QMessageBox::Discard);
//        qDebug() << "Error:" << reply->errorString();
//        return;
//    }
//
//    // 读取响应数据
//    QByteArray data = reply->readAll();
//    {
//        // 将 JSON 字符串转换为 QJsonDocument
//        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
//
//        // 如果 JSON 文档不为空且不是空对象，则进行解析
//        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
//            QJsonObject jsonObject = jsonDoc.object();
//
//            // 检查是否存在 error 对象
//            if (jsonObject.contains("error")) {
//                QJsonObject errorObject = jsonObject["error"].toObject();
//                QString errorMessage = errorObject["message"].toString();
//                QString errorType = errorObject["type"].toString();
//
//                // 在此处处理错误消息和错误类型，例如显示在消息框中
//                QMessageBox::critical(this, tr("发生错误"), errorMessage, QMessageBox::Close);
//            } else {
////                qDebug() <<"未包含error";
////                QMessageBox::critical(this, tr("发生错误"), tr("未处理"), QMessageBox::Close);
//            }
//        } else {
////            qDebug() << "序列化失败";
////            QMessageBox::critical(this, tr("发生错误"), tr("消息序列化失败"), QMessageBox::Close);
//        }
//    }
//    qDebug() << "111";
//    QTextStream stream(data);
//// 解析数据字段
//    while (!stream.atEnd()) {
//        QString line = stream.readLine();
//        qDebug() << "line:" << line;
//        if (line.startsWith("data:")) {
//            QString jsonStr = line.mid(5);
////            qDebug() << "one line:" << jsonStr;
//
//            // 将 JSON 字符串转换为 QJsonDocument
//            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());
//
//            // 如果 JSON 文档不为空且不是空对象，则进行解析
//            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
//                QJsonObject jsonObject = jsonDoc.object();
//
//                QString id = jsonObject["id"].toString();
//                QString object = jsonObject["object"].toString();
//                qint64 created = jsonObject["created"].toDouble();
//                QString model = jsonObject["model"].toString();
//
//                QJsonArray choicesArray = jsonObject["choices"].toArray();
//
//                // 遍历 choices 数组
//                for (int i = 0; i < choicesArray.size(); ++i) {
//                    QJsonObject choiceObject = choicesArray[i].toObject();
//
//                    QJsonObject deltaObject = choiceObject["delta"].toObject();
//                    QString role = deltaObject["role"].toString();
//                    QString content = deltaObject["content"].toString();
//
//                    int index = choiceObject["index"].toInt();
//                    QString finishReason = choiceObject["finish_reason"].toString();
//                    MainWindow::getInstance()->cache_text += content;
//                    MainWindow::getInstance()->ui->out_put_text_2->setText(MainWindow::getInstance()->cache_text);
////                    MainWindow::getInstance()->ui->out_put_text_2->insertPlainText(content);
//                    MainWindow::getInstance()->ui->out_put_text_2->moveCursor(QTextCursor::End);
//                    qDebug() << content;
//                }
//            }
//        } else if (line == "") {
//            continue;
//        } else {
//
//        }
//    }
}

void MainWindow::on_pushButton_clicked() {
    this->hide();
}


void MainWindow::on_pushButton_4_clicked() {
    setting_ui->show();
}

void MainWindow::showSetting() {
    this->setting_ui->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
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

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (m_dragging) {
        // 移动窗口
        move(event->globalPos() - m_dragPos);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && m_dragging) {
        // 标记为不可拖动
        m_dragging = false;
        // 恢复鼠标指针状态
        unsetCursor();
        event->accept();
    }
}

void MainWindow::ShowBar(const QString &newText) {
    qDebug() << "选中的文本:" << newText;
    // 创建图标
    // 显示图标
    MainWindow::getInstance()->bar->aim_text = newText;
    // 显示 MainWindow
    MainWindow::getInstance()->bar->show();
    // 移动 MainWindow 到响应位置
    QPoint cursorPos = QCursor::pos();
    MainWindow::getInstance()->bar->move(cursorPos + QPoint(10, 10));
    // 延迟检查剪贴板以确保选中的文本已被复制
    QTimer::singleShot(1000 * 10, [this]() {
        this->bar->hide();
    });
}
