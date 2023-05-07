#include "linebar.h"
#include "ui_linebar.h"

LineBar::LineBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineBar)
{
    ui->setupUi(this);
    // 设置窗口标志，使其成为顶层窗口
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    aim_text = "";
}

LineBar::~LineBar()
{
    delete ui;
}

void LineBar::on_close_button_clicked() {
    qDebug() << "退出";
    exit(0);
}

void LineBar::on_talk_code_clicked() {
    this->talk->TalkWithGpt("请你用中文帮我解释该代码:"+this->aim_text,this->talk->out);
}

void LineBar::on_translate_button_clicked() {
    this->talk->TalkWithGpt("请你将以下内容翻译为中文，其中术语可能偏向于计算机行业:"+this->aim_text,this->talk->out);
}

void LineBar::on_setting_button_clicked() {
    this->talk->showSetting();
}

void LineBar::on_hide_button_clicked() {
    this->hide();
}

void LineBar::AddButton(ButtonNode *node) {
// 创建水平布局
    QHBoxLayout *layout = ui->horizontalLayout;
    node->button = new QPushButton(node->name,this);
// 将按钮添加到布局中
    layout->addWidget(node->button);
    connect(node->button, &QPushButton::clicked, [this,node]() {
        this->talk->TalkWithGpt(node->prompt+"\n"+this->aim_text,this->talk->out);
        this->hide();
    });
}

void LineBar::InitButton() {
    for (auto & item : settings_dialog->button_list->list_buttons) {
        AddButton(&item);
    }
    QObject::connect( settings_dialog, &SettingsDialog::SettingChangedSend, this, &LineBar::SettingChanged);
}

void LineBar::RemoveButton(ButtonNode *node) {
    QHBoxLayout *layout = ui->horizontalLayout;
    layout->removeWidget(node->button);
    delete node->button;
    node->button = nullptr;
    QObject::disconnect(node->button, &QPushButton::clicked, this, nullptr);
}

void LineBar::SettingChanged(QSettings *setting) {
    for (auto & item : settings_dialog->button_list->list_buttons) {
        RemoveButton(&item);
    }
    settings_dialog->button_list->list_buttons.clear();
    settings_dialog->button_list->ReadFromSettings(setting);
    for (auto & item : settings_dialog->button_list->list_buttons) {
        AddButton(&item);
    }
}


