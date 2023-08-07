#include "mainwindow.h"

#include <QApplication>
#include "TestFunc.h"
#include <QDebug>
#include "utils/logs.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyleSheet("file:///:/style.qss");
    // 让用户数据可以输出到日志
//    logSysInit("log.txt");
    MainWindow w;
    w.hide();
//    TestFunc t;
//    t.TestProxyConfigWidgetPublic();
    return a.exec();
}
