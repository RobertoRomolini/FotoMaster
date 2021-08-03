#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QCoreApplication>
#include <QFile>

class Logger : public QObject
{
    Q_OBJECT
public:
    Logger(QObject *parent = 0);
    static void addLog(QString logMessage);

    static void setShouldLog(bool newShouldLog);

private:
    static bool shouldLog;

    static void checkDateLogs();
    static QString getLogFilename();
};

#endif // LOGGER_H
