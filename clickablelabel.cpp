#include "clickablelabel.h"
#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    if ( Qt::LeftButton == event->button())
    {
        emit clicked();
    }
    QLabel::mousePressEvent(event);
}
