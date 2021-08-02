#ifndef QGRAPHICSVIEWCUSTOM_H
#define QGRAPHICSVIEWCUSTOM_H

#include <QtWidgets>

class QGraphicsViewCustom : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QGraphicsViewCustom(QWidget *parent=0);



protected:
    virtual void wheelEvent(QWheelEvent * event) override;


signals:
    void altScrollUpSignal();
    void altScrollDownSignal();

};

#endif // QGRAPHICSVIEWCUSTOM_H
