#ifndef QPUSHBUTTONGREEN_H
#define QPUSHBUTTONGREEN_H

#include <QtWidgets>

class QPushButtonGreen : public QPushButton
{
    Q_OBJECT
public:
    explicit QPushButtonGreen(QWidget *parent = 0 );

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
    QString normal = "font: 10pt 'Helvetica'; font-weight:bold; background-color:#5AD409; border-radius:4px; border:1px solid #000000;";
    QString hovered = "font: 10pt 'Helvetica'; font-weight:bold; background-color:#32FF00; border-radius:4px; border:2px solid #000000;";

};

#endif // QPUSHBUTTONGREEN_H
