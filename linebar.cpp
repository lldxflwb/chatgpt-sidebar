#include "linebar.h"
#include "ui_linebar.h"

LineBar::LineBar(QWidget *parent) : QDialog(parent), ui(new Ui::LineBar) {
    ui->setupUi(this);
    // 设置窗口标志，使其成为顶层窗口
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    ui->close_button->setToolTip("退出软件");
    ui->hide_button->setToolTip("隐藏bar,10s后自动隐藏");
    ui->setting_button->setToolTip("调出设置界面");
    aim_text = "";
}

LineBar::~LineBar() { delete ui; }

void LineBar::on_close_button_clicked() {
    qDebug() << "退出";
    exit(0);
}

void LineBar::on_setting_button_clicked() { this->talk->showSetting(); }

void LineBar::on_hide_button_clicked() { this->hide(); }

void LineBar::AddButton(ButtonNode *node) {

    node->button = new QPushButton(node->name, this);
    node->button->setMaximumWidth(40);
    node->button->setFlat(true);
    node->button->setToolTip(node->prompt);
    // 将按钮添加到布局中
    ui->horizontalLayout->addWidget(node->button);
    connect(node->button, &QPushButton::clicked, [this, node]() {
        this->talk->TalkWithGpt(node->prompt + "\n" + this->aim_text,
                                this->talk->out);
        this->hide();
    });
}

void LineBar::InitButton() {
    for (auto &item : settings_dialog->button_list->list_buttons) {
        AddButton(&item);
    }
    QObject::connect(settings_dialog, &SettingsDialog::SettingChangedSend, this,
                     &LineBar::SettingChanged);
}

void LineBar::RemoveButton(ButtonNode *node) {
    QHBoxLayout *layout = ui->horizontalLayout;
    if (node->button == nullptr) {
        return;
    }
    layout->removeWidget(node->button);
    QObject::disconnect(node->button, &QPushButton::clicked, this, nullptr);
    delete node->button;
    node->button = nullptr;
}

void LineBar::SettingChanged(QSettings *setting) {
    for (auto &item : settings_dialog->button_list->list_buttons) {
        RemoveButton(&item);
    }
    settings_dialog->button_list->list_buttons.clear();
    settings_dialog->button_list->ReadFromSettings(setting);
    for (auto &item : settings_dialog->button_list->list_buttons) {
        AddButton(&item);
    }
}
