#ifndef RESIZEWINDOW_H
#define RESIZEWINDOW_H

#include <QSettings>
#include <QCoreApplication>
#include <QResizeEvent>
#include <QWidget>

class ResizeWindow
{
public:
    ResizeWindow(QString fileName);

    void setObjectGeometry(QWidget *widget);

    //Move
    void moveWidgetX(QWidget *widget);
    void moveWidgetY(QWidget *widget);
    void moveWidgetXY(QWidget *widget);

    //Resize
    void resizeWidgetX(QWidget *widget);
    void resizeWidgetY(QWidget *widget);
    void resizeWidgetXY(QWidget *widget);

    //Getters and Setters
    void setWidthHeightIncrement(QResizeEvent *event, QObject *object);

private:
    QSettings *settingsResize;
    int widthIncrement;
    int heightIncrement;

};

#endif // RESIZEWINDOW_H
