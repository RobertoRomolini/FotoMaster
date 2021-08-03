#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);

    static int getSettingsInt(QString value);
    static bool getSettingsBool(QString value);
    static QString getSettingsString(QString value);


private:
    static QString getSettingsFilename();

};

#endif // SETTINGS_H
