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
class ButtonNode{
public:
    QPushButton * button;
    QString prompt;
    QString name;
public:
    ButtonNode(const QString &prompt, const QString &name , QWidget *parent);
    ButtonNode(const QString &prompt, const QString &name );
};
class ButtonList{
public:
    std::vector<ButtonNode> list_buttons;
    void SaveToSettings(QSettings * settings);
    void ReadFromSettings(QSettings * settings);
};
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
    std::map<QString,QLineEdit*> * edit_info;
    ButtonList * button_list;
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
