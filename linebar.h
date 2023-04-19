#ifndef LINEBAR_H
#define LINEBAR_H

#include <QDialog>
#include "DealChatGpt.h"
namespace Ui {
class LineBar;
}

class LineBar : public QDialog
{
    Q_OBJECT

public:
    QString aim_text;
    explicit LineBar(QWidget *parent = nullptr);
    DealChatGpt * talk;
    ~LineBar();
private slots:
    void on_close_button_clicked();
    void on_talk_code_clicked();
    void on_translate_button_clicked();
    void on_setting_button_clicked();
private:
    Ui::LineBar *ui;
};

#endif // LINEBAR_H
