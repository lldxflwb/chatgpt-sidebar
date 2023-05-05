#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Windows.h>
#include <QMimeData>
#include "clickablelabel.h"
#include <QSettings>
#include "linebar.h"
#include "DealChatGpt.h"
#include "utils/settingsdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow , DealChatGpt
{
    Q_OBJECT

public:
    bool clicked_button ;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* getInstance();
    ClickableLabel * iconLabel;
    LineBar * bar;
    QString cache_text;
    SettingsDialog * setting_ui;

public slots:
    void iconLabelClicked();

    void TalkWithChatgpt(QString text,QString prompt);
private slots:

    void on_close_button_2_clicked();

    void fetchAnswerFromGPT3(const QString &text) override;
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void showSetting() override;

public slots:
    void handleApiResponse();
    void ShowBar(const QString& newText);
private:
    static MainWindow* instance;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    QPoint m_dragPos;
    bool m_dragging;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
