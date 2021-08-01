#ifndef QIMGORIENT_H
#define QIMGORIENT_H

#include <QObject>

#include "windows.h"
#include "minmax.h"
#include "gdiplus.h"

#include <QImage>

using namespace Gdiplus;

class QImgOrient : public QObject
{
    Q_OBJECT
public:
    explicit QImgOrient(QObject *parent = 0);

    SHORT orientation(QString fname);

signals:

public slots:
};

#endif // QIMGORIENT_H
