#include "logger.h"

#include <QDateTime>
#include <QFileInfo>
#include <QTextStream>
#include "WindowWidgets/Settings/settingsconst.h"

Logger::Logger(QObject *parent) : QObject(parent)
{
    checkDateLogs();
}

bool Logger::shouldLog;

void Logger::logInfo(QString message)
{
    QSettings settings;

    if(settings.value(SettingsConst::isLogEnabled).toBool()){
        QFile file(getLogFilename());
        if(file.open(QFile::Append | QFile::Text))
        {
            QTextStream out(&file);
            out << "[" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "]: " << message << Qt::endl;
            file.close();
        }
    }
}

//-------------------------------------------//
//               Getter and Setter
//-------------------------------------------//

void Logger::setShouldLog(bool newShouldLog)
{
    shouldLog = newShouldLog;
}

//-------------------------------------------//
//             Internal methods
//-------------------------------------------//

void Logger::checkDateLogs()
{
    // Check if the log file has logs for more than 30 days
    QFile logFile(getLogFilename());
    QFile newLogFile(qApp->applicationDirPath() + "/temp/newLog.log");
    if (logFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&logFile);

        newLogFile.open(QFile::Append | QFile::Text);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QDate date = QDate::fromString(line.mid(1,10),"yyyy-MM-dd");
            QTextStream out(&newLogFile);
            if (date.addDays(30) > QDate::currentDate())
            {
                out << line << Qt::endl;
            }
        }
        newLogFile.close();
        logFile.close();
    }
    logFile.remove();
    newLogFile.rename(getLogFilename());
}

QString Logger::getLogFilename()
{
    return qApp->applicationDirPath() + "/temp/log.log";
}


