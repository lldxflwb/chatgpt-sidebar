#include "buttonsettingborad.h"
#include <QSpacerItem>

ButtonSettingPair::ButtonSettingPair(
        QWidget *parent, const QString &labelText, const QString &prompt)
    : QHBoxLayout(parent), label_text(labelText), prompt(prompt) {
    delete_button = new QPushButton("-");
    delete_button->setMaximumSize(25, 25);
    delete_button->setToolTip("删除改行配置");
    this->addWidget(delete_button);
    name = new QLineEdit(parent);
    name->setText(labelText);
    name->setMaximumWidth(50);
    name->setToolTip("请设置功能按钮名称");
    this->addWidget(name);
    content = new QLineEdit(parent);
    content->setText(prompt);
    content->setToolTip("请设置提问语，即prompt");
    this->addWidget(content);
    this->addSpacing(10);

}

ButtonSettingPair::~ButtonSettingPair() {
    if (content != nullptr) {
        delete content;
        content = nullptr;
    }
    if (name != nullptr) {
        delete name;
        name = nullptr;
    }
    if (delete_button != nullptr) {
        delete delete_button;
        delete_button = nullptr;
    }
}

ButtonSettingBorad::ButtonSettingBorad(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* v_layout = new QVBoxLayout;
    box = new QVBoxLayout;

    add_button = new QPushButton("添加prompt", parent);
    add_button->setToolTip("将会添加一行默认设置，名称和设置都需要更改，如果为默认值则无法被保存");
    this->setLayout(v_layout);
    v_layout->addLayout(box);
    QSpacerItem * sparcer_item = new QSpacerItem(0,160,QSizePolicy::Fixed,QSizePolicy::Expanding);
    v_layout->addSpacerItem(sparcer_item);
    v_layout->addWidget(add_button);
}

ButtonSettingBorad::~ButtonSettingBorad() {
}

void ButtonSettingBorad::ReloadSetting(ButtonList *list) {
    if (list == nullptr) {
        return;
    }
    QLayoutItem *child;
    while ((child = box->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    for (auto &item : list->list_buttons) {
        auto *line = new ButtonSettingPair(nullptr, item.name, item.prompt);
        connect(line->delete_button, &QPushButton::clicked,
                [name = item.name, prompt = item.prompt,
                this](bool clicked = false) { emit DeletePrompt(name, prompt); });
        connect(line->name, &QLineEdit::textChanged,
                [&item](const QString text) { item.name = text; });
        connect(line->content, &QLineEdit::textChanged,
                [&item](const QString text) { item.prompt = text; });
        box->addLayout(line);
    }
}

ButtonNode::ButtonNode(const QString &prompt, const QString &name,
                       QWidget *parent)
    : prompt(prompt), name(name) {
    button = new QPushButton(name, parent);
}

ButtonNode::ButtonNode(const QString &prompt, const QString &name)
    : prompt(prompt), name(name) {
    button = nullptr;
}

void ButtonList::SaveToSettings(QSettings *settings) {
    int cnt = 0;
    int last_cnt = settings->value("btns").toInt();
    for (int i = 0; i < list_buttons.size(); ++i) {
        auto &btn = list_buttons[i];
        if (btn.name == "名称" || btn.prompt == "提示语") {
            qDebug() << "存在无效按钮";
            cnt++;
            continue;
        }
        {
            QString key_name = QString("btn.prompt.%1").arg(i - cnt);
            settings->setValue(key_name, btn.prompt);
        }
        {
            QString key_name = QString("btn.name.%1").arg(i - cnt);
            settings->setValue(key_name, btn.name);
        }
    }
    settings->setValue("btns", list_buttons.size() - cnt);
    qDebug() << "cnts:" << cnt << ",last : " << last_cnt
             << " , all : " << list_buttons.size();
    for (int i = list_buttons.size() - cnt;
         i < list_buttons.size() || i < last_cnt; ++i) {
        {
            QString key_name = QString("btn.prompt.%1").arg(i);
            settings->remove(key_name);
        }
        {
            QString key_name = QString("btn.name.%1").arg(i);
            settings->remove(key_name);
        }
    }
}

void ButtonList::ReadFromSettings(QSettings *settings) {
    auto cnts = settings->value("btns", "-1").toInt();
    if (cnts == -1) {
        list_buttons.push_back(ButtonNode("请你用中文帮我解释该代码:", "解释"));
        list_buttons.push_back(ButtonNode(
                                   "请你将以下内容翻译为中文，其中术语可能偏向于计算机行业:", "翻译"));
        list_buttons.push_back(
                    ButtonNode("请你用中文，就以下内容进行创作:", "创作"));
        list_buttons.push_back(ButtonNode("请你用中文，总结以下内容:", "归纳"));
        SaveToSettings(settings);
    } else {
        list_buttons.clear();
        for (int i = 0; i < cnts; i++) {
            QString prompt_key = QString("btn.prompt.%1").arg(i);
            QString name_key = QString("btn.name.%1").arg(i);
            QString prompt = settings->value(prompt_key, "").toString();
            QString name = settings->value(name_key, "").toString();
            if (!prompt.isEmpty() && !name.isEmpty()) {
                list_buttons.push_back(ButtonNode(prompt, name));
            }
        }
    }
}
