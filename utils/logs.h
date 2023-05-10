//
// Created by 48449 on 2023/5/10.
//

#ifndef CHATGPT_SIDEBAR_LOGS_H
#define CHATGPT_SIDEBAR_LOGS_H


#include <QFile>
#include <QMessageLogger>
#include <qlogging.h>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#pragma execution_character_set("utf-8")
void logSysInit(QString filePath);
void logSysInit();


#endif //CHATGPT_SIDEBAR_LOGS_H
