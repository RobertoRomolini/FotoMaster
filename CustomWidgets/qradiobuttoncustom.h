#ifndef QRADIOBUTTONCUSTOM_H
#define QRADIOBUTTONCUSTOM_H

#include <QRadioButton>
#include <QObject>
#include <QWidget>

class QRadioButtonCustom : public QRadioButton
{
    Q_OBJECT
public:
    QRadioButtonCustom(QWidget *parent);
};

#endif // QRADIOBUTTONCUSTOM_H
