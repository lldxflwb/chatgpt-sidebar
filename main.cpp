#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyleSheet("file:///:/style.qss");
    MainWindow w;
    w.hide();
    return a.exec();
}
