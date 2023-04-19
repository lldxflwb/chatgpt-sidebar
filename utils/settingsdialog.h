#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <map>
#include <QString>
#include <QLineEdit>
namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
private slots:

    void on_close_button_clicked();
    void on_save_button_clicked();
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    QSettings *m_settings;
    std::map<QString,QLineEdit*> * edit_info;
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
