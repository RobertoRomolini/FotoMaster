#include "qpushbuttonblue.h"


QPushButtonBlue::QPushButtonBlue(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet(normal);

}

void QPushButtonBlue::hoverEnter(QHoverEvent *)
{
    signalEnterMouse ();
    setStyleSheet(hovered);
}

void QPushButtonBlue::hoverLeave(QHoverEvent *)
{
    signalLeaveMouse ();
    setStyleSheet(normal);
}

void QPushButtonBlue::hoverMove(QHoverEvent *)
{
    //signalMoveMouse ();
}

bool QPushButtonBlue::event(QEvent *event)
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
