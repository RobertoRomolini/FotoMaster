#include "logger.h"

#include <QDateTime>

Logger::Logger(QString logFilename, QObject *parent) : QObject(parent)
{
    this->logFilename = logFilename;
}

void Logger::addLog(QString logMessage)
{
    QFile file(this->logFilename);
    if(file.open(QFile::Append | QFile::Text))
    {
        QTextStream out(&file);
        out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "]: " << logMessage << Qt::endl;
        file.close();
    }
}

//-------------------------------------------//
//               Getter and Setter
//-------------------------------------------//

bool Logger::getShouldLog()
{
    return shouldLog;
}

void Logger::setShouldLog(bool newShouldLog)
{
    shouldLog = newShouldLog;
}


