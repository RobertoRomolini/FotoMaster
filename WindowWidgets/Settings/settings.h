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

    static int getSettingsInt(QString name);
    static bool getSettingsBool(QString name);
    static QString getSettingsString(QString name);

    static void setSettings(QString name, int value);
    static void setSettings(QString name, QString value);
    static void setSettings(QString name, bool value);

private:


};

#endif // SETTINGS_H
