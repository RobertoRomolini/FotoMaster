#ifndef QPUSHBUTTONBLUE_H
#define QPUSHBUTTONBLUE_H

#include <QtWidgets>

class QPushButtonBlue : public QPushButton
{
    Q_OBJECT
public:
    QPushButtonBlue(QWidget *parent);


protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);

signals:
    void signalEnterMouse ();
    void signalLeaveMouse ();
    //void signalMoveMouse ();

private:
    QString normal = "font: 10pt 'Helvetica'; font-weight:bold; background-color:#0A63A9; border-radius:4px; border:1px solid #000000;";
    QString hovered = "font: 10pt 'Helvetica'; font-weight:bold; background-color:#008FFF; border-radius:4px; border:2px solid #000000;";

};

#endif // QPUSHBUTTONBLUE_H
