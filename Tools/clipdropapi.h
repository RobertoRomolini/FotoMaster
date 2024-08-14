#ifndef CLIPDROPAPI_H
#define CLIPDROPAPI_H

#include <QtNetwork>

class ClipDropApi : public QObject
{
public:
    explicit ClipDropApi();
    void sendRequestToRemoveBackground();
    void getResponseBackgroundRemoved();

private:
    QNetworkAccessManager *manager;
};

#endif // CLIPDROPAPI_H
