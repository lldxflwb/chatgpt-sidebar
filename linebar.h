#ifndef LINEBAR_H
#define LINEBAR_H

#include <QDialog>
#include "DealChatGpt.h"
#include <list>
#include "utils/settingsdialog.h"

namespace Ui {
class LineBar;
}

class LineBar : public QDialog
{
    Q_OBJECT

public:
    QString aim_text;
    explicit LineBar(QWidget *parent = nullptr);
    SettingsDialog * settings_dialog;
    DealChatGpt * talk;
    ~LineBar();
    void AddButton(ButtonNode * node);
    void RemoveButton(ButtonNode * node);
    void InitButton();

private slots:
    void on_close_button_clicked();
    void on_hide_button_clicked();
    void on_setting_button_clicked();
    void SettingChanged(QSettings * setting);
private:
    Ui::LineBar *ui;
};

#endif // LINEBAR_H
