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
    QSettings settings;
    // Generale
    QString directoryBackup = settings.value(SettingsConst::directoryBackup).toString();
    if ( QDir(directoryBackup).exists()) //se la directory non esiste il programma crasha
    {
        ui->directoryBackup->setText(directoryBackup);
    }
    ui->isLogEnabled->setChecked(settings.value(SettingsConst::isLogEnabled).toBool());

    // Trasforma Immagini
    ui->percAumento->setValue(settings.value(SettingsConst::percAumento).toInt());
    ui->latoMin->setValue(settings.value(SettingsConst::latoMin).toInt());
    ui->latoMax->setValue(settings.value(SettingsConst::latoMax).toInt());
    ui->ridimensionaMin->setChecked(settings.value(SettingsConst::ridimensionaMin).toBool());
    ui->ridimensionaMax->setChecked(settings.value(SettingsConst::ridimensionaMax).toBool());
    ui->ratioWidthJpg->setValue(settings.value(SettingsConst::ratioWidthJpg).toInt());
    ui->ratioHeightJpg->setValue(settings.value(SettingsConst::ratioHeightJpg).toInt());
    ui->ratioWidthPng->setValue(settings.value(SettingsConst::ratioWidthPng).toInt());
    ui->ratioHeightPng->setValue(settings.value(SettingsConst::ratioHeightPng).toInt());
    ui->ratioWidthWebp->setValue(settings.value(SettingsConst::ratioWidthWebp).toInt());
    ui->ratioHeightWebp->setValue(settings.value(SettingsConst::ratioHeightWebp).toInt());
    ui->outputJpg->setChecked(settings.value(SettingsConst::outputJpg).toBool());
    ui->outputPng->setChecked(settings.value(SettingsConst::outputPng).toBool());
    ui->outputWebp->setChecked(settings.value(SettingsConst::outputWebp).toBool());
    ui->qualitaSalvataggioJpg->setValue(settings.value(SettingsConst::qualitaSalvataggioJpg).toInt());
    ui->qualitaSalvataggioPng->setValue(settings.value(SettingsConst::qualitaSalvataggioPng).toInt());
    ui->qualitaSalvataggioWebp->setValue(settings.value(SettingsConst::qualitaSalvataggioWebp).toInt());
    ui->backgroundJpg->setText(settings.value(SettingsConst::backgroundJpg).toString());
    ui->cbPercBassoJpg->setChecked(settings.value(SettingsConst::cbPercBassoJpg).toBool());
    ui->percentualeBassoJpg->setValue(settings.value(SettingsConst::percentualeBassoJpg).toInt());
    ui->cbPercBassoPng->setChecked(settings.value(SettingsConst::cbPercBassoPng).toBool());
    ui->percentualeBassoPng->setValue(settings.value(SettingsConst::percentualeBassoPng).toInt());
    ui->cbPercBassoWebp->setChecked(settings.value(SettingsConst::cbPercBassoWebp).toBool());
    ui->percentualeBassoWebp->setValue(settings.value(SettingsConst::percentualeBassoWebp).toInt());
    ui->saveImageFolders->setChecked(settings.value(SettingsConst::saveImageFolders).toBool());

    // Remove BG
    SimpleCrypt crypt(SettingsConst::simpleCryptKey);
    ui->apiKeyRemoveBG->setText(crypt.decryptToString(settings.value(SettingsConst::apiKeyRemoveBG).toString()));
    ui->urlRemoveBG->setText(settings.value(SettingsConst::urlRemoveBG).toString());
    ui->radioButtonSizePreview->setChecked(settings.value(SettingsConst::radioButtonSizePreview).toBool());
    ui->radioButtonSizeFull->setChecked(settings.value(SettingsConst::radioButtonSizeFull).toBool());
    ui->removeBgFormatJpg->setChecked(settings.value(SettingsConst::removeBgFormatJpg).toBool());
    ui->removeBgFormatPng->setChecked(settings.value(SettingsConst::removeBgFormatPng).toBool());
    ui->removeBgFormatZip->setChecked(settings.value(SettingsConst::removeBgFormatZip).toBool());

    // ClipDrop
    ui->apiKeyClipDrop->setText(crypt.decryptToString(settings.value(SettingsConst::clipDropApiKey).toString()));
    ui->clipDropFormatJpg->setChecked(settings.value(SettingsConst::clipDropFormatJpg).toBool());
    ui->clipDropFormatPng->setChecked(settings.value(SettingsConst::clipDropFormatPng).toBool());
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
    QSettings settings;
    // Generale
    settings.setValue(SettingsConst::directoryBackup, ui->directoryBackup->text());
    settings.setValue(SettingsConst::isLogEnabled, ui->isLogEnabled->isChecked());

    // Trasforma Immagini
    settings.setValue(SettingsConst::percAumento, ui->percAumento->value());
    settings.setValue(SettingsConst::latoMin, ui->latoMin->value());
    settings.setValue(SettingsConst::latoMax, ui->latoMax->value());
    settings.setValue(SettingsConst::ridimensionaMin, ui->ridimensionaMin->isChecked());
    settings.setValue(SettingsConst::ridimensionaMax, ui->ridimensionaMax->isChecked());
    settings.setValue(SettingsConst::outputJpg, ui->outputJpg->isChecked());
    settings.setValue(SettingsConst::ratioWidthJpg, ui->ratioWidthJpg->value());
    settings.setValue(SettingsConst::ratioHeightJpg, ui->ratioHeightJpg->value());
    settings.setValue(SettingsConst::qualitaSalvataggioJpg, ui->qualitaSalvataggioJpg->value());
    settings.setValue(SettingsConst::outputPng, ui->outputPng->isChecked());
    settings.setValue(SettingsConst::ratioWidthPng, ui->ratioWidthPng->value());
    settings.setValue(SettingsConst::ratioHeightPng, ui->ratioHeightPng->value());
    settings.setValue(SettingsConst::qualitaSalvataggioPng, ui->qualitaSalvataggioPng->value());
    settings.setValue(SettingsConst::ratioWidthWebp, ui->ratioWidthWebp->value());
    settings.setValue(SettingsConst::ratioHeightWebp, ui->ratioHeightWebp->value());
    settings.setValue(SettingsConst::outputWebp, ui->outputWebp->isChecked());
    settings.setValue(SettingsConst::qualitaSalvataggioWebp, ui->qualitaSalvataggioWebp->value());
    settings.setValue(SettingsConst::backgroundJpg, ui->backgroundJpg->text());
    settings.setValue(SettingsConst::cbPercBassoJpg, ui->cbPercBassoJpg->isChecked());
    settings.setValue(SettingsConst::percentualeBassoJpg, ui->percentualeBassoJpg->value());
    settings.setValue(SettingsConst::cbPercBassoPng, ui->cbPercBassoPng->isChecked());
    settings.setValue(SettingsConst::percentualeBassoPng, ui->percentualeBassoPng->value());
    settings.setValue(SettingsConst::cbPercBassoWebp, ui->cbPercBassoWebp->isChecked());
    settings.setValue(SettingsConst::percentualeBassoWebp, ui->percentualeBassoWebp->value());
    settings.setValue(SettingsConst::saveImageFolders, ui->saveImageFolders->isChecked());

    // RemoveBG
    SimpleCrypt crypt(SettingsConst::simpleCryptKey);
    settings.setValue(SettingsConst::apiKeyRemoveBG, crypt.encryptToString(ui->apiKeyRemoveBG->text()));
    settings.setValue(SettingsConst::urlRemoveBG, ui->urlRemoveBG->text());
    settings.setValue(SettingsConst::removeBgImageSize, ui->removeBgImageSize->checkedButton()->text());
    settings.setValue(SettingsConst::radioButtonSizePreview, ui->radioButtonSizePreview->isChecked());
    settings.setValue(SettingsConst::radioButtonSizeFull, ui->radioButtonSizeFull->isChecked());
    settings.setValue(SettingsConst::removeBgFormatJpg, ui->removeBgFormatJpg->isChecked());
    settings.setValue(SettingsConst::removeBgFormatPng, ui->removeBgFormatPng->isChecked());
    settings.setValue(SettingsConst::removeBgFormatZip, ui->removeBgFormatZip->isChecked());
    settings.setValue(SettingsConst::removeBgImageFormat, ui->removeBgImageFormat->checkedButton()->text());

    // ClipDrop
    settings.setValue(SettingsConst::clipDropApiKey, crypt.encryptToString(ui->apiKeyClipDrop->text()));
    settings.setValue(SettingsConst::clipDropFormatJpg, ui->clipDropFormatJpg->isChecked());
    settings.setValue(SettingsConst::clipDropFormatPng, ui->clipDropFormatPng->isChecked());
    settings.setValue(SettingsConst::clipDropImageFormat, ui->clipDropImageFormat->checkedButton()->text());

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
    ui->saveImageFolders->setChecked(true);
    ui->outputJpg->setChecked(true);
    ui->outputPng->setChecked(true);
    ui->ratioWidthJpg->setValue(1);
    ui->ratioHeightJpg->setValue(1);
    ui->ratioWidthPng->setValue(2);
    ui->ratioHeightPng->setValue(3);
    ui->ratioWidthWebp->setValue(2);
    ui->ratioHeightWebp->setValue(3);
    ui->qualitaSalvataggioJpg->setValue(85);
    ui->qualitaSalvataggioPng->setValue(85);
    ui->qualitaSalvataggioWebp->setValue(85);
    ui->backgroundJpg->setText("ffffff");
    ui->percentualeBassoJpg->setValue(16);
    ui->percentualeBassoPng->setValue(16);
    ui->percentualeBassoWebp->setValue(16);
    ui->urlRemoveBG->setText("https://api.remove.bg/v1.0/removebg");
    ui->radioButtonSizeFull->setChecked(true);
    ui->removeBgFormatPng->setChecked(true);
    ui->clipDropFormatPng->setChecked(true);
}



