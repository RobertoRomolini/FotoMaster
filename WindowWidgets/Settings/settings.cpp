#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{

}

bool Settings::getSettingsBool(QString value)
{

}

QString Settings::getSettingsString(QString value)
{

}

int Settings::getSettingsInt(QString value)
{
    QSettings settings(getSettingsFilename() , QSettings::IniFormat);
    return settings.value(value).toInt();
}

//-----------------------------------------------------------------------------//
//                          Internal Private methods
//-----------------------------------------------------------------------------//
QString Settings::getSettingsFilename()
{
    return qApp->applicationDirPath() + "/temp/optionSettings.desktop";
}
