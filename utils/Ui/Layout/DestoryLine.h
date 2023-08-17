//
// Created by 陈嘉乐 on 2023/8/17.
//

#ifndef CHATGPT_SIDEBAR_DESTORYLINE_H
#define CHATGPT_SIDEBAR_DESTORYLINE_H

#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QWidget>
#include <vector>
#include <QPushButton>
#include "utils/AutoConfig/AutoConfigItem.h"

class DestroyLine : QHBoxLayout{
public:
    QPushButton * destroyButton;
    std::vector<AutoConfigItem*> values;
    DestroyLine(QWidget *parent = nullptr);
    void AddValues(AutoConfigItem * value);
};


#endif //CHATGPT_SIDEBAR_DESTORYLINE_H
