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
    explicit ImageProcessor(QString filename);

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

    void centerImage(double ratioHeight, double ratioWidth, int percAumento, double percentualeBasso, int tolleranza);

    QImage getNewImage();

    const QString &getOutputFormat() const;

    void setNewImage(QString filename, QString hexColorBg = nullptr);

private:
    QImage image;
    QImage newImage;
    QString filename;
    QString outputFormat;
};

#endif // IMAGEPROCESSOR_H
