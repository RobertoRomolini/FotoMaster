#ifndef SETTINGSCONST_H
#define SETTINGSCONST_H

#include <QObject>

class SettingsConst
{
public:
    SettingsConst();

    static const QString directoryBackup;
    static const QString directoryMemory;
    static const QString percAumento;
    static const QString qualitaSalvataggio;
    static const QString trasformaQualita;
    static const QString latoMin;
    static const QString latoMax;
    static const QString ridimensionaMin;
    static const QString ridimensionaMax;
    static const QString ratioWidth;
    static const QString ratioHeight;
    static const QString apiKeyRemoveBG;
    static const QString urlRemoveBG;
    static const QString tolleranza;
    static const QString confrontoBianco;
    static const QString latoMinMD;
    static const QString dimMinFileSpinBox;
    static const QString imageOutputFormat;
    static const QString radioButtonJpg;
    static const QString radioButtonPng;
};

#endif // SETTINGSCONST_H
