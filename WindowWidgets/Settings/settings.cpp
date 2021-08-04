#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{

}

QSettings *settings = new QSettings(qApp->applicationDirPath() + "/temp/settings.desktop", QSettings::IniFormat);

bool Settings::getSettingsBool(QString name)
{
    return settings->value(name).toBool();
}

QString Settings::getSettingsString(QString name)
{
    return settings->value(name).toString();
}

int Settings::getSettingsInt(QString name)
{
    return settings->value(name).toInt();
}

void Settings::setSettings(QString name, int value)
{
    settings->setValue(name, value);
}

void Settings::setSettings(QString name, QString value)
{
    settings->setValue(name, value);
}

void Settings::setSettings(QString name, bool value)
{
    settings->setValue(name, value);
}
