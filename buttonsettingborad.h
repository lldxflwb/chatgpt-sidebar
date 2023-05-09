#ifndef BUTTONSETTINGBORAD_H
#define BUTTONSETTINGBORAD_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QWidget>

class ButtonNode {
public:
    QPushButton *button;
    QString prompt;
    QString name;

public:
    ButtonNode(const QString &prompt, const QString &name, QWidget *parent);
    ButtonNode(const QString &prompt, const QString &name);
};

class ButtonList : QHBoxLayout {
public:
    std::vector<ButtonNode> list_buttons;
    void SaveToSettings(QSettings *settings);
    void ReadFromSettings(QSettings *settings);
};

class ButtonSettingBorad : public QWidget {
    Q_OBJECT
public:
    explicit ButtonSettingBorad(QWidget *parent);
    QVBoxLayout *box;
    QPushButton *add_button;
    void ReloadSetting(ButtonList *list);

    ~ButtonSettingBorad() override;

public:
signals:
    void DeletePrompt(QString name, QString prompt);
};

class ButtonSettingPair : public QHBoxLayout {
public:
    QString label_text;
    QString prompt;
    ButtonSettingPair(QWidget *parent, const QString &labelText,
                      const QString &prompt);
    ~ButtonSettingPair() override;
    QLineEdit *name;
    QLineEdit *content;
    QPushButton *delete_button;
};

#endif // BUTTONSETTINGBORAD_H
