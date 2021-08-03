#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QCoreApplication>
#include <QFile>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QString logFilename, QObject *parent = 0);
    void addLog(QString logMessage);

    bool getShouldLog();
    void setShouldLog(bool newShouldLog);

private:
    bool shouldLog = true;
    QString logFilename;


};

#endif // LOGGER_H
