#ifndef QEDITORPUSHBUTTON_H
#define QEDITORPUSHBUTTON_H

#include <QtWidgets>

class QEditorPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QEditorPushButton(QWidget *parent = 0);
    QString neutralButton = QString ("background-color:#C3C3C3; border-radius:2px; border:1px solid #000000;");
    QString pressedButton = QString ("background-color:#F5F5F5; border-radius:2px; border:1px solid #000000;");
    QString pressedButtonHovered = QString ("background-color:#F5F5F5; border-radius:2px; border:2px solid #000000;");
    QString buttonHovered = QString ("background-color:#d4d4d4; border-radius:2px; border:2px solid #000000;");

private slots:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool event(QEvent *event);



signals:
    void signalEnterMouse ();
    void signalLeaveMouse ();
    void signalLeftClick();
    void buttonStateChangedSignal ();
    void buttonActiveSignal();

public slots:



private:


};

#endif // QEDITORPUSHBUTTON_H
