#include "qmoveimagepushbutton.h"

QMoveImagePushButton::QMoveImagePushButton(QWidget *parent) : QPushButton(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    setStyleSheet(greenButton);
}

void QMoveImagePushButton::hoverEnter(QHoverEvent *)
{

    if ( checked)
    {
        setStyleSheet(greenHoveredButton);
    }
    else
    {
        setStyleSheet(redHoveredButton);
    }

}

void QMoveImagePushButton::hoverLeave(QHoverEvent *)
{

    if ( checked)
    {
        setStyleSheet(greenButton);
    }
    else
    {
        setStyleSheet(redButton);
    }
}


bool QMoveImagePushButton::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}
