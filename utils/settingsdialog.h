#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <map>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
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
class ButtonList : QHBoxLayout{
public:
    std::vector<ButtonNode> list_buttons;
    void SaveToSettings(QSettings * settings);
    void ReadFromSettings(QSettings * settings);
};
class ButtonSettingBorad : public QVBoxLayout{
Q_OBJECT
public:
    class ButtonSettingPair : public QHBoxLayout{
    public:
        QString label_text;
        QString prompt;

        ButtonSettingPair(QWidget *parent, const QString &labelText, const QString &prompt);

        ~ButtonSettingPair() override;

        QLineEdit * name;
        QLineEdit * content;
        QPushButton * delete_button;
    };
    explicit ButtonSettingBorad(QWidget *parent);
    QVBoxLayout * box;
    QPushButton * add_button;
    void ReloadSetting(ButtonList * list);

    ~ButtonSettingBorad() override;
public:
signals:
    void DeletePrompt(QString name,QString prompt);
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
    ButtonSettingBorad * button_setting_broad;
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
