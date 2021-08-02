#include "qgraphicsviewcustom.h"

QGraphicsViewCustom::QGraphicsViewCustom(QWidget *parent) : QGraphicsView(parent)
{
    setInteractive(true);
}


void QGraphicsViewCustom::wheelEvent(QWheelEvent * event)
{

    if(event->modifiers() & Qt::AltModifier)
    {

        if (event->angleDelta().x() > 0)
        {
            emit altScrollUpSignal();
        }
        else
        {
            emit altScrollDownSignal();
        }
    }
    else
    {
        if (event->angleDelta().y() > 0)
        {
            verticalScrollBar()->setSliderPosition( verticalScrollBar()->sliderPosition() - verticalScrollBar()->singleStep()  );
        }
        else
        {
            verticalScrollBar()->setSliderPosition( verticalScrollBar()->sliderPosition() + verticalScrollBar()->singleStep()  );
        }
    }
}
