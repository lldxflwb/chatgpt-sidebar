#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#define MAX_PROMPT 13

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), edit_info(new std::map<QString, QLineEdit *>()),
      ui(new Ui::SettingsDialog) {
    m_settings = new QSettings("sidebar.ini", QSettings::IniFormat);
    ui->setupUi(this);
    ui->verticalLayout->addSpacing(10);

    // ip set
    (*edit_info)["ip"] = ui->edit_ip;
    if (m_settings->value("ip", "") != "") {
        ui->edit_ip->setText(m_settings->value("ip", "").toString());
    }

    // port set
    (*edit_info)[QString("port")] = ui->edit_port;
    if (m_settings->value("port", "") != "") {
        ui->edit_port->setText(m_settings->value("port", "").toString());
    }

    // key set
    (*edit_info)[QString("key")] = ui->edit_key;
    if (m_settings->value("key", "") != "") {
        ui->edit_key->setText(m_settings->value("key", "").toString());
    }

    ui->formLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
    ui->verticalLayout->setSizeConstraint(
                QLayout::SizeConstraint::SetMinimumSize);

    // add prompt setting
    button_list = new ButtonList();
    button_list->ReadFromSettings(m_settings);

    ui->button_setting_broad->ReloadSetting(button_list);

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
