#include "resizewindow.h"

ResizeWindow::ResizeWindow(QString fileName)
{
    settingsResize = new QSettings(qApp->applicationDirPath() + "/temp/" + fileName + "Resize.desktop", QSettings::IniFormat);
}

void ResizeWindow::setWidthHeightIncrement(QResizeEvent *event , QObject *object)
{
    this->widthIncrement = event->size().width() - settingsResize->value(object->objectName() + "Width").toInt();
    this->heightIncrement = event->size().height() - settingsResize->value(object->objectName() + "Height").toInt();
}

void ResizeWindow::setObjectGeometry(QWidget *widget)
{
    settingsResize->setValue(widget->objectName() + "Width" , widget->width());
    settingsResize->setValue(widget->objectName() + "Height" , widget->height());
    settingsResize->setValue(widget->objectName() + "X" , widget->x());
    settingsResize->setValue(widget->objectName() + "Y" , widget->y());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                                                                                       Move
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void ResizeWindow::moveWidgetX(QWidget *widget)
{
    widget->move( this->widthIncrement + settingsResize->value(widget->objectName()+  "X").toInt()  , widget->y() );
}

void ResizeWindow::moveWidgetY(QWidget *widget)
{
    widget->move( widget->x() ,  this->heightIncrement + settingsResize->value(  widget->objectName() +  "Y").toInt() );
}

void ResizeWindow::moveWidgetXY(QWidget *widget)
{
    widget->move( this->widthIncrement + settingsResize->value(widget->objectName()+  "X").toInt() ,  this->heightIncrement + settingsResize->value(  widget->objectName() +  "Y").toInt() );
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                                                                                       Resize
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void ResizeWindow::resizeWidgetX(QWidget *widget)
{
    widget->resize( this->widthIncrement + settingsResize->value(widget->objectName()+  "Width").toInt()  , widget->height() );
}

void ResizeWindow::resizeWidgetY(QWidget *widget)
{
    widget->resize( widget->width()  , this->heightIncrement + settingsResize->value(widget->objectName() + "Height").toInt()   );
}

void ResizeWindow::resizeWidgetXY(QWidget *widget)
{
    widget->resize( this->widthIncrement + settingsResize->value(widget->objectName()+  "Width").toInt() , this->heightIncrement + settingsResize->value(widget->objectName() + "Height").toInt()   );
}




