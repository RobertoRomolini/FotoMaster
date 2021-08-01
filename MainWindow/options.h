#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QSettings>
#include <QCoreApplication>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();

    //Getters and Setters
    QString getDirectoryBackup ();
    QString getUrlRemoveBG();
    QString getApiKeyRemoveBG();


private slots:
    void on_chooseDirectory_clicked();
    void on_deleteDirectory_clicked();
    void on_saveSettings_clicked();

private:
    Ui::Options *ui;


    //File di salvataggio impostazioni
    QSettings *optionSettings = new QSettings(qApp->applicationDirPath() + "/temp/optionSettings.desktop", QSettings::IniFormat);

};

#endif // OPTIONS_H
