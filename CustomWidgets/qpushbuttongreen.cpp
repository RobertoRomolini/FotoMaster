#include "qpushbuttongreen.h"

QPushButtonGreen::QPushButtonGreen(QWidget *parent) : QPushButton(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    setStyleSheet(normal);
}

void QPushButtonGreen::hoverEnter(QHoverEvent *)
{
    signalEnterMouse ();
    setStyleSheet(hovered);
}

void QPushButtonGreen::hoverLeave(QHoverEvent *)
{
    signalLeaveMouse ();
    setStyleSheet(normal);
}

void QPushButtonGreen::hoverMove(QHoverEvent *)
{
    //signalMoveMouse ();
}

bool QPushButtonGreen::event(QEvent *event)
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
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}
