#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QTextEdit>

#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),edit_info(new std::map<QString,QLineEdit*>())
{
    m_settings = new QSettings("sidebar.ini", QSettings::IniFormat);
    ui->setupUi(this);

    // ip set
    auto * edit_ip = new QLineEdit("",this);
    (*edit_info)["ip"]=edit_ip;
    if (m_settings->value("ip","")!=""){
        edit_ip->setText( m_settings->value("ip","").toString() );
    }
    ui->formLayout->addRow("ip",edit_ip);

    // port set
    auto * edit_port = new QLineEdit("",this);
    (*edit_info)[QString("port")]=edit_port;
    if (m_settings->value("port","")!=""){
        edit_port->setText( m_settings->value("port","").toString() );
    }
    ui->formLayout->addRow("port",edit_port);

    // key set
    auto * edit_key = new QLineEdit("",this);
    (*edit_info)[QString("key")]=edit_key;
    if (m_settings->value("key","")!=""){
        edit_key->setText( m_settings->value("key","").toString() );
    }
    ui->formLayout->addRow("key",edit_key);

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_close_button_clicked() {
    this->hide();
}

void SettingsDialog::on_save_button_clicked() {
    for (auto & item : (*this->edit_info)) {
        m_settings->setValue(item.first,item.second->text());
    }
    m_settings->sync();
    this->hide();
}
