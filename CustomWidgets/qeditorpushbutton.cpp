#include "qeditorpushbutton.h"

QEditorPushButton::QEditorPushButton(QWidget *parent) : QPushButton(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    setStyleSheet(neutralButton);
    setCheckable(true);
    setChecked(false);
}

void QEditorPushButton::hoverEnter(QHoverEvent *)
{

    signalEnterMouse ();
    if (  isChecked())
    {
        setStyleSheet(pressedButtonHovered);
    }
    else
    {
        setStyleSheet(buttonHovered);
    }

}

void QEditorPushButton::hoverLeave(QHoverEvent *)
{
    signalLeaveMouse ();
    if (  isChecked())
    {
        setStyleSheet(pressedButton);
    }
    else
    {
        setStyleSheet(neutralButton);
    }
}

void QEditorPushButton::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {  
        if ( isChecked())
        {
            setStyleSheet(neutralButton);
            setChecked(false);
        }
        else
        {
            buttonActiveSignal();
            setStyleSheet(pressedButton);
            setChecked(true);
        }
        buttonStateChangedSignal ();
    }
}

bool QEditorPushButton::event(QEvent *event)
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
    case QEvent::MouseButtonPress:
        mousePressEvent(static_cast<QMouseEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}
