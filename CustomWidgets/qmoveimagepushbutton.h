#ifndef QMOVEIMAGEPUSHBUTTON_H
#define QMOVEIMAGEPUSHBUTTON_H

#include <QtWidgets>

class QMoveImagePushButton  : public QPushButton
{
    Q_OBJECT
public:
    explicit QMoveImagePushButton(QWidget *parent = 0);
    bool checked = true;
    QString greenButton = "background-color:#5AD409; border-radius:2px; border:1px solid #000000;";
    QString greenHoveredButton = "background-color:#32FF00; border-radius:2px; border:1px solid #000000;";
    QString redButton = "background-color:#FB362D; border-radius:2px; border:1px solid #000000;";
    QString redHoveredButton = "background-color:#FF0000; border-radius:2px; border:1px solid #000000;";


protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    bool event(QEvent *event);

private:

};

#endif // QMOVEIMAGEPUSHBUTTON_H
