#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <map>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "buttonsettingborad.h"
#include "utils/MySetting/Panel/EnginePanel.h"



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
signals:
    void SettingChangedSend(QSettings * settings);
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    QSettings *m_settings;
    std::map<QString,QLineEdit*>* edit_info;
    ButtonList * button_list;
    ButtonSettingBorad * button_setting_broad;
    EnginePanel * engine_panel;

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
