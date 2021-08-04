#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QDialog>
#include <QSettings>
#include <QCoreApplication>
#include <WindowWidgets/Settings/settings.h>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();

    // Getters and Setters
    QString getDirectoryBackup ();

    int getPercAumento();
    int getQualitaSalvataggio();
    bool getTrasformaQualita();
    int getLatoMin();
    int getLatoMax();
    bool getRidimensionaMin();
    bool getRidimensionaMax();
    int getRatioWidth();
    int getRatioHeight();

    QString getUrlRemoveBG();
    QString getApiKeyRemoveBG();

private slots:
    void on_chooseDirectory_clicked();
    void on_deleteDirectory_clicked();
    void on_saveSettings_clicked();
    void on_reset_settings_clicked();

private:
    Ui::Options *ui;


    //File di salvataggio impostazioni
    QSettings *optionSettings = new QSettings(qApp->applicationDirPath() + "/temp/optionSettings.desktop", QSettings::IniFormat);

};

#endif // OPTIONSWIDGET_H
