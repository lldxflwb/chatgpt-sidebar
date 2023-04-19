#include "linebar.h"
#include "ui_linebar.h"

LineBar::LineBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineBar)
{
    ui->setupUi(this);
    // 设置窗口标志，使其成为顶层窗口
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    aim_text = "";
}

LineBar::~LineBar()
{
    delete ui;
}

void LineBar::on_close_button_clicked() {
    qDebug() << "退出软件";
    exit(0);
}

void LineBar::on_talk_code_clicked() {
    this->talk->TalkWithGpt("请你用中文帮我解释该代码:"+this->aim_text,this->talk->out);
}

void LineBar::on_translate_button_clicked() {
    this->talk->TalkWithGpt("请你将以下内容翻译为中文，其中术语可能偏向于计算机行业:"+this->aim_text,this->talk->out);
}

void LineBar::on_setting_button_clicked() {
    this->talk->showSetting();
}
