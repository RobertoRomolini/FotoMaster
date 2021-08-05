#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{

}

bool Settings::getSettingsBool(QString name)
{
    QSettings settings(getSettingsPath(), QSettings::IniFormat);
    return settings.value(name).toBool();
}

QString Settings::getSettingsString(QString name)
{
    QSettings settings(getSettingsPath(), QSettings::IniFormat);
    return settings.value(name).toString();
}

int Settings::getSettingsInt(QString name)
{
    QSettings settings(getSettingsPath(), QSettings::IniFormat);
    return settings.value(name).toInt();
}

void Settings::setSettings(QString name, int value)
{
    QSettings settings(getSettingsPath(), QSettings::IniFormat);
    settings.setValue(name, value);
}

void Settings::setSettings(QString name, QString value)
{
    QSettings settings(getSettingsPath(), QSettings::IniFormat);
    settings.setValue(name, value);
}

void Settings::setSettings(QString name, bool value)
{
    QSettings settings(getSettingsPath(), QSettings::IniFormat);
    settings.setValue(name, value);
}

QString Settings::getSettingsPath()
{
    return qApp->applicationDirPath() + "/temp/settings.desktop";
}




