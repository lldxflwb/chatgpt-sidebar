#include <QMessageBox>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#define MAX_PROMPT 13

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), edit_info(new std::map<QString, QLineEdit *>()),
      ui(new Ui::SettingsDialog) {
    // 宏 判断是否是win系统
#if defined(Q_OS_WIN)
    m_settings = new QSettings("sidebar.ini", QSettings::IniFormat);
    // 如果是mac
#elif defined(Q_OS_MACOS)
    // mac 申请配置文件写入权限 读取配置
    m_settings = new QSettings("/Users/Shared/sidebar.ini", QSettings::IniFormat);
    // 输出配置文件路径
#endif
    ui->setupUi(this);
    ui->verticalLayout->addSpacing(10);

    // ip set
    (*edit_info)["ip"] = ui->edit_ip;
    if (m_settings->value("ip", "") != "") {
        ui->edit_ip->setText(m_settings->value("ip", "").toString());
    }
    ui->edit_ip->setToolTip("请填入代理软件对本地开放的ip,代理应为socks5，如代理软件在本机则为127.0.0.1，非节点ip，具体详情见readme");

    // port set
    (*edit_info)[QString("port")] = ui->edit_port;
    if (m_settings->value("port", "") != "") {
        ui->edit_port->setText(m_settings->value("port", "").toString());
    }
    ui->edit_port->setToolTip("请填入代理软件对本地开放的port，代理应为socks5,如是clash默认为7890，如v2rayN则默认为10808，非节点port，具体详情见readme");
    // key set
    (*edit_info)[QString("key")] = ui->edit_key;
    if (m_settings->value("key", "") != "") {
        ui->edit_key->setText(m_settings->value("key", "").toString());
    }
    ui->edit_key->setToolTip("请填入您的openai的key，且请检查，您的赠送费用是否过期，直达连接见readme");
    this->engine_panel=new EnginePanel();
    ui->verticalLayout->addWidget(this->engine_panel);

    ui->formLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
    ui->verticalLayout->setSizeConstraint(
                QLayout::SizeConstraint::SetMinimumSize);

    // add prompt setting
    button_list = new ButtonList();
    button_list->ReadFromSettings(m_settings);

    ui->button_setting_broad->ReloadSetting(button_list);

    ui->save_button->setToolTip("保存配置");
    ui->close_button->setToolTip("隐藏配置界面");

    connect(ui->button_setting_broad, &ButtonSettingBorad::DeletePrompt, this,
            [this](QString name, QString prompt) {
        std::vector<ButtonNode> new_list;
        for (auto &item : button_list->list_buttons) {
            if (item.prompt == prompt && item.name == name) {
                continue;
            }
            new_list.push_back(item);
        }
        button_list->list_buttons = new_list;
        if (new_list.size() == 0) {
            button_list->list_buttons.push_back(ButtonNode("提示语", "名称"));
        }
        ui->button_setting_broad->ReloadSetting(button_list);
    });
    connect(ui->button_setting_broad->add_button, &QPushButton::clicked, this,
            [this](bool clicked = false) {
        if (button_list->list_buttons.size() > MAX_PROMPT) {
            qDebug() << "prompt size must less than" << MAX_PROMPT;
            static std::string tips = "功能按钮应该小于";
            tips = tips + std::to_string(MAX_PROMPT);
            QMessageBox::critical(this,tr("错误"), tr(tips.c_str()),QMessageBox::Close);
            return;
        };
        button_list->list_buttons.push_back(ButtonNode("提示语", "名称"));
        ui->button_setting_broad->ReloadSetting(button_list);
    });
}

SettingsDialog::~SettingsDialog() { delete ui; }

void SettingsDialog::on_close_button_clicked() { this->hide(); }

void SettingsDialog::on_save_button_clicked() {
    for (auto &item : (*this->edit_info)) {
        m_settings->setValue(item.first, item.second->text());
    }
    this->button_list->SaveToSettings(this->m_settings);
    m_settings->sync();
    emit SettingChangedSend(m_settings);
    this->hide();
}
