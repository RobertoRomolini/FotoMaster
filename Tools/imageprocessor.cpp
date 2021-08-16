#include "imageprocessor.h"
#include "logger.h"

#include <QFileInfo>

ImageProcessor::ImageProcessor(QString filename, QString outputformat)
{
    this->image.load(filename);
    this->setNewImage(outputformat);
}

void ImageProcessor::fixOrientationImage()
{
    QImgOrient imageOrientation;
    QTransform imageRotate;
    if ( imageOrientation.orientation(filename) == 8)
    {
         imageRotate.rotate(270);
         this->image = image.transformed(imageRotate);
    }
    if ( imageOrientation.orientation(filename) == 6)
    {
         imageRotate.rotate(90);
         this->image = image.transformed(imageRotate);
    }
    if ( imageOrientation.orientation(filename) == 3 )
    {
         imageRotate.rotate(180);
         this->image = image.transformed(imageRotate);
    }
}

void ImageProcessor::saveNewImage(QString absoluteFilePath, int quality)
{
    this->newImage.save(absoluteFilePath , nullptr , quality);
}

void ImageProcessor::saveImage(QString absoluteFilePath, int quality)
{
    this->image.save(absoluteFilePath , nullptr , quality);
}

void ImageProcessor::modifyImageFormat()
{
    QPainter painter;
    newImage = newImage.scaled(image.width() , image.height() , Qt::IgnoreAspectRatio);
    painter.begin(&newImage);
    painter.drawImage( 0 , 0  , image );
    painter.end();
}

int ImageProcessor::pixelImageTop(int tolleranza)
{
    QColor pixel;
    for ( int i=0 ; i<image.height() ; i++ )
    {
        for ( int j=0 ; j<image.width(); j++ )
        {
            pixel =  image.pixelColor( j , i );

            if (pixel.red() <= 255 - tolleranza &&
                 pixel.green() <= 255 - tolleranza &&
                 pixel.blue() <= 255 - tolleranza &&
                 pixel.alphaF() > 0.02)
            {
                qDebug () << "Top pixel RGBA: " << pixel.red() << "," << pixel.green() << "," << pixel.blue() << "," << pixel.alphaF();
                return i;
            }
        }
    }

    return 0;
}

int ImageProcessor::pixelImageRight(int tolleranza)
{
    QColor pixel;
    for ( int i=image.width()-1 ; i>0 ; i-- )
    {
        for ( int j=0 ; j<image.height(); j++ )
        {
            pixel =  image.pixelColor( i , j );
            if (pixel.red() <= 255 - tolleranza &&
                 pixel.green() <= 255 - tolleranza &&
                 pixel.blue() <= 255 - tolleranza &&
                 pixel.alphaF() > 0.02)
            {
                qDebug () << "Right pixel RGBA: " << pixel.red() << "," << pixel.green() << "," << pixel.blue() << "," << pixel.alphaF();
                return image.width()- i -1;
            }
        }
    }

    return image.width() - 1;
}

int ImageProcessor::pixelImageBottom(int tolleranza)
{
    QColor pixel;
    for ( int i=image.height()-1 ; i>0 ; i-- )
    {
        for ( int j=0 ; j<image.width(); j++ )
        {
            pixel =  image.pixelColor( j , i );
            if (pixel.red() <= 255 - tolleranza &&
                 pixel.green() <= 255 - tolleranza &&
                 pixel.blue() <= 255 - tolleranza &&
                 pixel.alphaF() > 0.02)
            {

                qDebug () << "Bottom pixel RGBA: " << pixel.red() << "," << pixel.green() << "," << pixel.blue() << "," << pixel.alphaF();
                return image.height() - i -1;
            }
        }
    }

    return image.height() - 1;
}

int ImageProcessor::pixelImageLeft(int tolleranza)
{
    QColor pixel;
    for ( int i=0 ; i<image.width() ; i++ )
    {
        for ( int j=0 ; j<image.height(); j++ )
        {
            pixel =  image.pixelColor( i , j );
            if (pixel.red() <= 255 - tolleranza &&
                 pixel.green() <= 255 - tolleranza &&
                 pixel.blue() <= 255 - tolleranza &&
                 pixel.alphaF() > 0.02)
            {
                qDebug () << "Left pixel RGBA: " << pixel.red() << "," << pixel.green() << "," << pixel.blue() << "," << pixel.alphaF();
                return i;
            }
        }
    }

    return 0;
}

void ImageProcessor::scaledNewImageToMin(int latoMin)
{
    if (newImage.width() < latoMin)
    {
        newImage = newImage.scaledToWidth(latoMin , Qt::SmoothTransformation );
    }
    else if (newImage.height() < latoMin)
    {
        newImage = newImage.scaledToHeight(latoMin , Qt::SmoothTransformation );
    }
}

void ImageProcessor::scaledNewImageToMax(int latoMax)
{
    if (newImage.width() > latoMax)
    {
        newImage = newImage.scaledToWidth(latoMax , Qt::SmoothTransformation );
    }
    else if (newImage.height() > latoMax)
    {
        newImage = newImage.scaledToHeight(latoMax , Qt::SmoothTransformation );
    }
}

void ImageProcessor::centerImage(int tolleranza, double ratioHeight, double ratioWidth, int percAumento, double percentualeBasso)
{
    QPainter painter;

    int top = this->pixelImageTop(tolleranza);
    int bottom = this->pixelImageBottom(tolleranza);
    int left = this->pixelImageLeft(tolleranza);
    int right = this->pixelImageRight(tolleranza);

    // Calculate aspect ratio
    double ratio = ratioHeight/ratioWidth;

    if ( top == 0 && bottom == 0 && left == 0 && right == 0 )
    {
        qDebug () << "L'oggetto tocca la foto da tutti i lati, la riquadro solamente";
        if (image.width() * ratio > image.height() || image.width() > image.height() / ratio)
        {
            newImage = newImage.scaled(image.width(), image.width() * ratio, Qt::IgnoreAspectRatio);
            painter.begin(&newImage);
            painter.drawImage(0, ((image.width() * ratio) - image.height())/2 , image );
        }
        else
        {
            newImage = newImage.scaled(image.height() / ratio, image.height(), Qt::IgnoreAspectRatio);
            painter.begin(&newImage);
            painter.drawImage(((image.height() / ratio) - image.width())/2 , 0, image );
        }
    }
    else
    {

        int newWidth = image.width() - left - right;
        int newHeight = image.height() - top - bottom;
        QRect rect (left , top , newWidth , newHeight);
        image = image.copy(rect);

        int newWidthIncreased = newWidth + ((newWidth * percAumento)/100);
        int newHeightIncreased = newHeight + ((newHeight * percAumento)/100);
        int newWidthIncreasedHalf = newWidth + ((newWidth * percAumento/2)/100);
        int newHeightIncreasedHalf = newHeight + ((newHeight * percAumento/2)/100);

        if ( top != 0 && bottom != 0 && left != 0 && right != 0 )
        {
            qDebug () << "L'oggetto non tocca i bordi, procedo rimuovendo la parte eccedente";
            if (percentualeBasso == -1)
            {
                if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
                {
                    newImage = newImage.scaled(newWidthIncreased, newWidthIncreased * ratio, Qt::IgnoreAspectRatio);
                    painter.begin(&newImage);
                    painter.drawImage((newWidthIncreased - newWidth)/2, ((newWidthIncreased * ratio) - newHeight)/2 , image );
                }
                else
                {
                    newImage = newImage.scaled(newHeightIncreased / ratio, newHeightIncreased, Qt::IgnoreAspectRatio);
                    painter.begin(&newImage);
                    painter.drawImage(((newHeightIncreased / ratio) - newWidth)/2 , (newHeightIncreased - newHeight)/2, image );
                }
            }
            else
            {
                double bottomValue = percentualeBasso/100;
                double newHeightWithBottom = newHeightIncreasedHalf + newHeightIncreasedHalf * bottomValue;
                double newWidthWithBottom = newHeightWithBottom / ratio;

                if (newWidthWithBottom < newWidthIncreased)
                {
                    newImage = newImage.scaled(newWidthIncreased, newWidthIncreased * ratio, Qt::IgnoreAspectRatio);
                    painter.begin(&newImage);
                    painter.drawImage((newWidthIncreased - newWidth)/2, newWidthIncreased * ratio - newHeight - newWidthIncreased * ratio * bottomValue , image);
                }
                else
                {
                    if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
                    {
                        newImage = newImage.scaled(newWidthIncreased, newWidthIncreased * ratio, Qt::IgnoreAspectRatio);
                        painter.begin(&newImage);
                        painter.drawImage((newWidthIncreased - newWidth)/2, ((newWidthIncreased * ratio) - newHeight)/2 , image );
                    }
                    else
                    {
                        newImage = newImage.scaled(newHeightIncreased / ratio, newHeightIncreased, Qt::IgnoreAspectRatio);
                        painter.begin(&newImage);
                        painter.drawImage(((newHeightIncreased / ratio) - newWidth)/2 , (newHeightIncreased - newHeight)/2, image );
                    }
                }
            }
        }
        else if ( top != 0 && bottom == 0 && left != 0 && right != 0 )
        {
            qDebug () << "L'oggetto tocca il bordo solo sotto";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage((newWidthIncreasedHalf - newWidth)/2, (newWidthIncreasedHalf * ratio) - newHeight , image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(((newHeightIncreasedHalf / ratio) - newWidth)/2 , newHeightIncreasedHalf - newHeight, image);
            }
        }
        else if ( top == 0 && bottom != 0 && left != 0 && right != 0 )
        {
            qDebug () << "L'oggetto tocca il bordo solo sopra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage((newWidthIncreasedHalf - newWidth)/2, 0 , image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(((newHeightIncreasedHalf / ratio) - newWidth)/2 , 0, image);
            }
        }
        else if ( top != 0 && bottom != 0 && left != 0 && right == 0 )
        {
            qDebug () << "L'oggetto tocca il bordo solo a destra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(newWidthIncreasedHalf - newWidth, ((newWidthIncreasedHalf * ratio) - newHeight)/2 , image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage((newHeightIncreasedHalf / ratio) - newWidth , (newHeightIncreasedHalf - newHeight)/2, image);
            }
        }
        else if ( top != 0 && bottom != 0 && left == 0 && right != 0 )
        {
            qDebug () << "L'oggetto tocca il bordo solo a sinistra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, ((newWidthIncreasedHalf * ratio) - newHeight)/2 , image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, (newHeightIncreasedHalf - newHeight)/2, image);
            }
        }
        else if ( top != 0 && bottom == 0 && left == 0 && right != 0 )
        {
            qDebug () << "L'oggetto tocca il bordo sotto e a sinistra";

            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, (newWidthIncreasedHalf * ratio) - newHeight, image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, newHeightIncreasedHalf - newHeight, image);
            }
        }
        else if ( top != 0 && bottom == 0 && left != 0 && right == 0 )
        {
            qDebug () << "L'oggetto tocca il bordo sotto e a destra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(newWidthIncreasedHalf - newWidth, (newWidthIncreasedHalf * ratio) - newHeight , image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage((newHeightIncreasedHalf / ratio) - newWidth , newHeightIncreasedHalf - newHeight, image);
            }
        }
        else if ( top == 0 && bottom != 0 && left != 0 && right == 0 )
        {
            qDebug () << "L'oggetto tocca il bordo sopra e a destra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(newWidthIncreasedHalf - newWidth, 0, image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage((newHeightIncreasedHalf / ratio) - newWidth , 0, image);
            }
        }
        else if ( top == 0 && bottom != 0 && left == 0 && right != 0 )
        {
            qDebug () << "L'oggetto tocca il bordo sopra e a sinistra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, 0, image);
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, 0, image);
            }
        }
        else if ( top != 0 && bottom != 0 && left == 0 && right == 0 )
        {
            qDebug () << "L'oggetto tocca il bordo a destra e a sinistra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidth, newWidth * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, ((newWidth * ratio) - newHeight)/2 , image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreased / ratio, newHeightIncreased, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(((newHeightIncreased / ratio) - newWidth)/2 , (newHeightIncreased - newHeight)/2, image);
            }
        }
        else if ( top == 0 && bottom == 0 && left != 0 && right != 0 )
        {
            qDebug () << "L'oggetto tocca il bordo sopra e sotto";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreased, newWidthIncreased * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage((newWidthIncreased - newWidth)/2, ((newWidthIncreased * ratio) - newHeight)/2, image );
            }
            else
            {
                newImage = newImage.scaled(newHeight / ratio, newHeight, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(((newHeightIncreased / ratio) - newWidth)/2 ,0 , image);
            }
        }
        else if ( top != 0 && bottom == 0 && left == 0 && right == 0 )
        {
            qDebug () << "L'oggetto tocca tutti i lati tranne sopra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidth, newWidth * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, (newWidth * ratio) - newHeight, image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(((newHeightIncreasedHalf / ratio) - newWidth)/2, newHeightIncreasedHalf - newHeight , image);
            }
        }

        else if ( top == 0 && bottom == 0 && left != 0 && right == 0 )
        {
            qDebug () << "L'oggetto tocca tutti i lati tranne a sinistra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(newWidthIncreasedHalf - newWidth, ((newWidthIncreasedHalf * ratio) - newHeight)/2, image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeight, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage((newHeightIncreasedHalf / ratio) - newWidth, 0, image);
            }
        }
        else if ( top == 0 && bottom == 0 && left == 0 && right != 0 )
        {
            qDebug () << "L'oggetto tocca tutti i lati tranne a destra";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, ((newWidthIncreasedHalf * ratio) - newHeight)/2, image);
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeight, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, 0, image);
            }
        }
        else if (top == 0 && bottom != 0 && left == 0 && right == 0)
        {
            qDebug () << "L'oggetto tocca tutti i lati tranne sotto";
            if (newWidth * ratio > newHeight || newWidth > newHeight / ratio)
            {
                newImage = newImage.scaled(newWidthIncreasedHalf, newWidthIncreasedHalf * ratio, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(0, (newWidthIncreasedHalf * ratio) - newHeight, image );
            }
            else
            {
                newImage = newImage.scaled(newHeightIncreasedHalf / ratio, newHeightIncreasedHalf, Qt::IgnoreAspectRatio);
                painter.begin(&newImage);
                painter.drawImage(((newHeightIncreasedHalf / ratio) - newWidth)/2, 0 , image);
            }
        }
    }
    painter.end();
}

QImage ImageProcessor::getNewImage()
{
    return this->newImage;
}

//-----------------------------------------------------------------------------------------//
//                                     Private Methods
//-----------------------------------------------------------------------------------------//
void ImageProcessor::setNewImage(QString outputFormat)
{
    if (outputFormat == "jpg")
    {
        newImage.load(":/Files/Files/whiteImage.jpg");
    }
    else
    {
        newImage.load(":/Files/Files/pngTransparent.png");
    }
}




