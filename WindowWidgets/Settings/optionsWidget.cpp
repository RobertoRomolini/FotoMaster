#include "optionsWidget.h"
#include "ui_optionsWidget.h"

#include <Tools/simplecrypt.h>

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);


    //-------------------------------------------------------------------------------//
    //                        Imposto le impostazioni da file
    //-------------------------------------------------------------------------------//
    // Generale
    QString directoryBackup = Settings::getSettingsString(SettingsConst::directoryBackup);
    if ( QDir(directoryBackup).exists()) //se la directory non esiste il programma crasha
    {
        ui->directoryBackup->setText(directoryBackup);
    }

    // Trasforma Immagini
    ui->percAumento->setValue(Settings::getSettingsInt(SettingsConst::percAumento));
    ui->latoMin->setValue(Settings::getSettingsInt(SettingsConst::latoMin));
    ui->latoMax->setValue(Settings::getSettingsInt(SettingsConst::latoMax));
    ui->ridimensionaMin->setChecked(Settings::getSettingsBool(SettingsConst::ridimensionaMin));
    ui->ridimensionaMax->setChecked(Settings::getSettingsBool(SettingsConst::ridimensionaMax));
    ui->ratioWidthJpg->setValue(Settings::getSettingsInt(SettingsConst::ratioWidthJpg));
    ui->ratioHeightJpg->setValue(Settings::getSettingsInt(SettingsConst::ratioHeightJpg));
    ui->ratioWidthPng->setValue(Settings::getSettingsInt(SettingsConst::ratioWidthPng));
    ui->ratioHeightPng->setValue(Settings::getSettingsInt(SettingsConst::ratioHeightPng));
    ui->ratioWidthWebp->setValue(Settings::getSettingsInt(SettingsConst::ratioWidthWebp));
    ui->ratioHeightWebp->setValue(Settings::getSettingsInt(SettingsConst::ratioHeightWebp));
    ui->outputJpg->setChecked(Settings::getSettingsBool(SettingsConst::outputJpg));
    ui->outputPng->setChecked(Settings::getSettingsBool(SettingsConst::outputPng));
    ui->outputWebp->setChecked(Settings::getSettingsBool(SettingsConst::outputWebp));
    ui->qualitaSalvataggioJpg->setValue(Settings::getSettingsInt(SettingsConst::qualitaSalvataggioJpg));
    ui->qualitaSalvataggioPng->setValue(Settings::getSettingsInt(SettingsConst::qualitaSalvataggioPng));
    ui->qualitaSalvataggioWebp->setValue(Settings::getSettingsInt(SettingsConst::qualitaSalvataggioWebp));
    ui->backgroundJpg->setText(Settings::getSettingsString(SettingsConst::backgroundJpg));
    ui->cbPercBassoJpg->setChecked(Settings::getSettingsBool(SettingsConst::cbPercBassoJpg));
    ui->percentualeBassoJpg->setValue(Settings::getSettingsInt(SettingsConst::percentualeBassoJpg));
    ui->cbPercBassoPng->setChecked(Settings::getSettingsBool(SettingsConst::cbPercBassoPng));
    ui->percentualeBassoPng->setValue(Settings::getSettingsInt(SettingsConst::percentualeBassoPng));
    ui->cbPercBassoWebp->setChecked(Settings::getSettingsBool(SettingsConst::cbPercBassoWebp));
    ui->percentualeBassoWebp->setValue(Settings::getSettingsInt(SettingsConst::percentualeBassoWebp));

    // Remove BG
    ui->apiKeyRemoveBG->setText(Settings::getSettingsString(SettingsConst::apiKeyRemoveBG));
    ui->urlRemoveBG->setText(Settings::getSettingsString(SettingsConst::urlRemoveBG));
    ui->radioButtonSizePreview->setChecked(Settings::getSettingsBool(SettingsConst::radioButtonSizePreview));
    ui->radioButtonSizeFull->setChecked(Settings::getSettingsBool(SettingsConst::radioButtonSizeFull));



    // FIXME
    SimpleCrypt crypt(3456345634645234);
    QString pippo("ciao");
    QString ciccio = crypt.encryptToString(pippo);
    qDebug () << ciccio;
    qDebug () << crypt.decryptToString(ciccio);
}

Options::~Options()
{
    delete ui;
}

//--------------------------------------------------------------------------//
//                             Private slots
//--------------------------------------------------------------------------//

void Options::on_chooseDirectory_clicked()
{
    QString filename = QFileDialog::getExistingDirectory(this, "Scegli Cartella" );
    if (filename != "")
    {
        ui->directoryBackup->setText(filename);
    }
}

void Options::on_deleteDirectory_clicked()
{
    ui->directoryBackup->setText("");
}

void Options::on_saveSettings_clicked()
{
    // Generale
    Settings::setSettings(SettingsConst::directoryBackup, ui->directoryBackup->text());

    // Trasforma Immagini
    Settings::setSettings(SettingsConst::percAumento, ui->percAumento->value());
    Settings::setSettings(SettingsConst::latoMin, ui->latoMin->value());
    Settings::setSettings(SettingsConst::latoMax, ui->latoMax->value());
    Settings::setSettings(SettingsConst::ridimensionaMin, ui->ridimensionaMin->isChecked());
    Settings::setSettings(SettingsConst::ridimensionaMax, ui->ridimensionaMax->isChecked());
    Settings::setSettings(SettingsConst::outputJpg, ui->outputJpg->isChecked());
    Settings::setSettings(SettingsConst::ratioWidthJpg, ui->ratioWidthJpg->value());
    Settings::setSettings(SettingsConst::ratioHeightJpg, ui->ratioHeightJpg->value());
    Settings::setSettings(SettingsConst::qualitaSalvataggioJpg, ui->qualitaSalvataggioJpg->value());
    Settings::setSettings(SettingsConst::outputPng, ui->outputPng->isChecked());
    Settings::setSettings(SettingsConst::ratioWidthPng, ui->ratioWidthPng->value());
    Settings::setSettings(SettingsConst::ratioHeightPng, ui->ratioHeightPng->value());
    Settings::setSettings(SettingsConst::qualitaSalvataggioPng, ui->qualitaSalvataggioPng->value());
    Settings::setSettings(SettingsConst::ratioWidthWebp, ui->ratioWidthWebp->value());
    Settings::setSettings(SettingsConst::ratioHeightWebp, ui->ratioHeightWebp->value());
    Settings::setSettings(SettingsConst::outputWebp, ui->outputWebp->isChecked());
    Settings::setSettings(SettingsConst::qualitaSalvataggioWebp, ui->qualitaSalvataggioWebp->value());
    Settings::setSettings(SettingsConst::backgroundJpg, ui->backgroundJpg->text());
    Settings::setSettings(SettingsConst::cbPercBassoJpg, ui->cbPercBassoJpg->isChecked());
    Settings::setSettings(SettingsConst::percentualeBassoJpg, ui->percentualeBassoJpg->value());
    Settings::setSettings(SettingsConst::cbPercBassoPng, ui->cbPercBassoPng->isChecked());
    Settings::setSettings(SettingsConst::percentualeBassoPng, ui->percentualeBassoPng->value());
    Settings::setSettings(SettingsConst::cbPercBassoWebp, ui->cbPercBassoWebp->isChecked());
    Settings::setSettings(SettingsConst::percentualeBassoWebp, ui->percentualeBassoWebp->value());

    // Remove BG
    Settings::setSettings(SettingsConst::apiKeyRemoveBG, ui->apiKeyRemoveBG->text());
    Settings::setSettings(SettingsConst::urlRemoveBG, ui->urlRemoveBG->text());
    Settings::setSettings(SettingsConst::removeBgImageSize, ui->removeBgImageSize->checkedButton()->text());
    Settings::setSettings(SettingsConst::radioButtonSizePreview, ui->radioButtonSizePreview->isChecked());
    Settings::setSettings(SettingsConst::radioButtonSizeFull, ui->radioButtonSizeFull->isChecked());

    this->close();
}

void Options::on_reset_settings_clicked()
{
    ui->percAumento->setValue(8);
    ui->latoMin->setValue(600);
    ui->latoMax->setValue(4500);
    ui->ridimensionaMin->setChecked(true);
    ui->ridimensionaMax->setChecked(true);
    ui->radioButtonSizeFull->setChecked(true);
}



