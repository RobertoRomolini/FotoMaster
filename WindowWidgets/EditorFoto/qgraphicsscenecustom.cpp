#include "qgraphicsscenecustom.h"

QGraphicsSceneCustom::QGraphicsSceneCustom (QWidget *parent) : QGraphicsScene(parent)
{
    temporaryImage = 0;

}

void QGraphicsSceneCustom::loadImage(QString fileName , int heightGraphicsView , QDoubleSpinBox *zoomPercentage)
{
    QFile copyFile (fileName);
    copyFile.copy(  qApp->applicationDirPath() + "/temp/temporaryImage/"  + QString (QString::number(temporaryImage)) + ".jpg");
    image.load (fileName);
    pixmapItem = new QGraphicsPixmapItem (addPixmap(QPixmap::fromImage(image)));
    double hGraph (heightGraphicsView);
    double hPixmap (image.height());
    zoomPercentage->setValue(100* hGraph /  hPixmap);
    setSceneRect(0,0,image.width(),image.height());
}

void QGraphicsSceneCustom::saveClose(QString fileName)
{
    if ( temporaryImage > 0 )
    {
        QMessageBox deleteConfirm;
        deleteConfirm.setText("Sei sicuro di voler uscire senza salvare?          ");
        deleteConfirm.addButton("Salva" , QMessageBox::YesRole);
        deleteConfirm.addButton("Esci" , QMessageBox::NoRole);
        int ret = deleteConfirm.exec();
        if ( ret == 0)
        {
            image.save(fileName, 0 , 90 );
        }
    }
}

void QGraphicsSceneCustom::save(QString fileName)
{
    image.save(fileName, 0 , 90 );
}

void QGraphicsSceneCustom::undo()
{
    if ( temporaryImage > 0 )
    {
        temporaryImage--;
        image.load(qApp->applicationDirPath() + "/temp/temporaryImage/" + QString (QString::number(temporaryImage)) + ".jpg");
        pixmapItem = (addPixmap(QPixmap::fromImage(image)));
        QFile deleteFile (qApp->applicationDirPath() + "/temp/temporaryImage/" + QString (QString::number(temporaryImage + 1)) + ".jpg");
        deleteFile.remove();
    }
}

void QGraphicsSceneCustom::saveImageUndo()
{
    if ( mousePosPress.x() >= 0 && mousePosPress.x() <= width() && mousePosPress.y() >= 0 && mousePosPress.y() <= height())
    {
        temporaryImage++;
        image.save( qApp->applicationDirPath() + "/temp/temporaryImage/" + QString (QString::number(temporaryImage)) + ".jpg", 0 , 90 );
    }
}

void QGraphicsSceneCustom::selectedPixelColor(QLabel *label)
{
    label->setStyleSheet("background-color:" + image.pixelColor(mousePosPress.toPoint()).name(QColor::HexRgb) + ";border-radius:2px; border:1px solid #000000;");
}

void QGraphicsSceneCustom::changePixelColor(QColor colorFound , QColor colorRepleace , int tolerance)
{
    for ( int i=0 ; i<image.width() ; i++ )
    {
        for ( int j=0 ; j<image.height(); j++ )
        {
            QColor pixel = image.pixelColor( i , j );

            if ( pixel.red() <= colorFound.red() + tolerance  &&   pixel.red() >= colorFound.red() - tolerance  &&
                 pixel.blue() <= colorFound.blue() + tolerance  &&   pixel.blue() >= colorFound.blue() - tolerance  &&
                 pixel.green() <= colorFound.green() + tolerance  &&   pixel.green() >= colorFound.green() - tolerance)
            {
                image.setPixelColor(  i , j , colorRepleace );
            }
        }
    }
    temporaryImage++;
    image.save( qApp->applicationDirPath() + "/temp/temporaryImage/" + QString (QString::number(temporaryImage)) + ".jpg", 0 , 90 );
    clear();
    pixmapItem = (addPixmap(QPixmap::fromImage(image)));
}

void QGraphicsSceneCustom::restoreImageClick(double dimension)
{
    QPixmap pix = QPixmap ("D:/Desktop/4 - Copy/scontornata.jpg").copy(mousePosPress.x()- dimension/2, mousePosPress.y()- dimension/2 , dimension , dimension);
    QPainterPath path;
    painter.begin(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    path.addEllipse(mousePosPress.x()- dimension/2, mousePosPress.y()- dimension/2, dimension, dimension);
    painter.setClipPath(path);
    painter.drawPixmap(mousePosPress.x()- dimension/2, mousePosPress.y()- dimension/2, dimension, dimension, pix);
    painter.end();
    clear();
    pixmapItem = (addPixmap(QPixmap::fromImage(image)));
}

void QGraphicsSceneCustom::restoreImageMove(double dimension)
{
    QPixmap pix = QPixmap ("D:/Desktop/4 - Copy/scontornata.jpg").copy(mousePosMove.x()- dimension/2, mousePosMove.y()- dimension/2 , dimension , dimension);
    QPainterPath path;
    painter.begin(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    path.addEllipse(mousePosMove.x()- dimension/2, mousePosMove.y()- dimension/2, dimension, dimension);
    painter.setClipPath(path);
    painter.drawPixmap(mousePosMove.x()- dimension/2, mousePosMove.y()- dimension/2, dimension, dimension, pix);
    painter.end();
    clear();
    pixmapItem = (addPixmap(QPixmap::fromImage(image)));
}

void QGraphicsSceneCustom::eraserLine( double dimension)
{
    QPen pen(Qt::white , dimension , Qt::SolidLine , Qt::RoundCap , Qt::RoundJoin);
    painter.begin(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen(pen);
    painter.drawLine(mousePosMoveLastScene  , mousePosMove);
    painter.end();
    clear();
    pixmapItem = (addPixmap(QPixmap::fromImage(image)));
}

void QGraphicsSceneCustom::eraserPoint(double dimension)
{
    QPen pen(Qt::white , dimension , Qt::SolidLine , Qt::RoundCap , Qt::RoundJoin);
    painter.begin(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen(pen);
    painter.drawPoint(mousePosPress);
    painter.end();
    clear();
    pixmapItem = (addPixmap(QPixmap::fromImage(image)));
}

void QGraphicsSceneCustom::eraserLinePointToPoint( double dimension)
{
    QPen pen(Qt::white , dimension , Qt::SolidLine , Qt::RoundCap , Qt::RoundJoin);
    painter.begin(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen(pen);
    painter.drawLine(mousePosPress  , mousePosPressShift);
    mousePosPress = mousePosPressShift;
    painter.end();
    clear();
    pixmapItem = (addPixmap(QPixmap::fromImage(image)));
}

void QGraphicsSceneCustom::eraserLineGradient(double dimension , double gradient)
{
    QRadialGradient radial ( mousePosMove , dimension/2);
    radial.setColorAt( 0 ,Qt::white);
    radial.setColorAt( gradient ,Qt::white);
    radial.setColorAt( 1 ,Qt::transparent);
    QBrush brush ( radial );
    QPen pen(Qt::white , dimension , Qt::SolidLine , Qt::RoundCap , Qt::RoundJoin);
    pen.setBrush(brush);
    painter.begin(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen(pen);
    painter.drawPoint(mousePosMove);
    painter.end();
    clear();
    pixmapItem = (addPixmap(QPixmap::fromImage(image)));
}

void QGraphicsSceneCustom::eraserPointGradient(double dimension, double gradient)
{
    QRadialGradient radial ( mousePosPress , dimension/2);
    radial.setColorAt( 0 ,Qt::white);
    radial.setColorAt( gradient ,Qt::white);
    radial.setColorAt( 1 ,Qt::transparent);
    QBrush brush ( radial );
    QPen pen(Qt::white , dimension , Qt::SolidLine , Qt::RoundCap , Qt::RoundJoin);
    pen.setBrush(brush);
    painter.begin(&image);
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen(pen);
    painter.drawPoint(mousePosPress);
    painter.end();
    clear();
    pixmapItem = (addPixmap(QPixmap::fromImage(image)));
}

void QGraphicsSceneCustom::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mouseScreenPosPress = event->screenPos();
    if ((QGuiApplication::queryKeyboardModifiers() == Qt::ShiftModifier)  && event->buttons() == Qt::LeftButton)
    {
        mousePosPressShift = event->scenePos();
        emit shiftLeftButtonClick ();
    }
    else if ((QGuiApplication::queryKeyboardModifiers() == Qt::AltModifier)  && event->buttons() == Qt::LeftButton)
    {
        mousePosPress = event->scenePos();
        emit altLeftButtonClick ();
    }
    else if (event->button() == Qt::LeftButton)
    {
        mousePosPress = event->scenePos();
        emit leftButtonClick ();
    }
    if (event->button() == Qt::RightButton)
    {
        emit rightButtonClick ();
    }

}

void QGraphicsSceneCustom::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit leftButtonRelease ();
    }
}

void QGraphicsSceneCustom::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    mouseScreenPosMove = event->screenPos();
    mousePosMove = event->scenePos();
    mousePosMoveLastScene = event->lastScenePos();
    if ((QGuiApplication::queryKeyboardModifiers() == Qt::AltModifier)  && event->buttons() == Qt::LeftButton)
    {
        emit altLeftButtonMoveSignal ();
    }
    else if (event->buttons() == Qt::LeftButton )
    {
        emit mouseLeftMoveSignal();
    }
    if ( (QGuiApplication::queryKeyboardModifiers() == Qt::AltModifier)  && event->buttons() == Qt::RightButton)
    {
        emit altRightButtonMoveSignal ();
    }

}

bool QGraphicsSceneCustom::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::Enter:
        emit signalEnterMouse();
        return true;
        break;
    case QEvent::GraphicsSceneLeave:
        emit signalLeaveMouse();
        return true;
        break;
    default:
        break;
    }
    return QGraphicsScene::event(event);
}

