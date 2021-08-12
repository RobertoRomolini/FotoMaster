#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QObject>
#include <QCoreApplication>
#include "qimgorient.h"

class ImageProcessor
{
public:
    explicit ImageProcessor(QString filename, QString outputformat);

    void fixOrientationImage();
    void saveNewImage(QString filePath, int quality = 100);
    void saveImage(QString filePath, int quality = 100);
    void modifyImageFormat();

    int pixelImageTop(int tolleranza);
    int pixelImageRight(int tolleranza);
    int pixelImageBottom(int tolleranza);
    int pixelImageLeft(int tolleranza);

    void scaledNewImageToMin(int latoMin);
    void scaledNewImageToMax(int latoMax);

    void centerImage(int tolleranza, double ratioHeight, double ratioWidth, int percAumento, double percentualeBasso = -1);

    QImage getNewImage();

private:
    QImage image;
    QImage newImage;
    QString filename;

    void setNewImage(QString filename);
};

#endif // IMAGEPROCESSOR_H
