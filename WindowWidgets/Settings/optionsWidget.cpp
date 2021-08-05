#include "optionsWidget.h"
#include "ui_optionsWidget.h"

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
    ui->qualitaSalvataggio->setValue(Settings::getSettingsInt(SettingsConst::qualitaSalvataggio));
    ui->trasformaQualita->setChecked(Settings::getSettingsBool(SettingsConst::trasformaQualita));
    ui->latoMin->setValue(Settings::getSettingsInt(SettingsConst::latoMin));
    ui->latoMax->setValue(Settings::getSettingsInt(SettingsConst::latoMax));
    ui->ridimensionaMin->setChecked(Settings::getSettingsBool(SettingsConst::ridimensionaMin));
    ui->ridimensionaMax->setChecked(Settings::getSettingsBool(SettingsConst::ridimensionaMax));
    ui->ratioWidth->setValue(Settings::getSettingsInt(SettingsConst::ratioWidth));
    ui->ratioHeight->setValue(Settings::getSettingsInt(SettingsConst::ratioHeight));
    ui->radioButtonJpg->setChecked(Settings::getSettingsBool(SettingsConst::radioButtonJpg));
    ui->radioButtonPng->setChecked(Settings::getSettingsBool(SettingsConst::radioButtonPng));

    // Remove BG
    ui->apiKeyRemoveBG->setText(Settings::getSettingsString(SettingsConst::apiKeyRemoveBG));
    ui->urlRemoveBG->setText(Settings::getSettingsString(SettingsConst::urlRemoveBG));
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
    Settings::setSettings(SettingsConst::qualitaSalvataggio, ui->qualitaSalvataggio->value());
    Settings::setSettings(SettingsConst::trasformaQualita, ui->trasformaQualita->isChecked());
    Settings::setSettings(SettingsConst::latoMin, ui->latoMin->value());
    Settings::setSettings(SettingsConst::latoMax, ui->latoMax->value());
    Settings::setSettings(SettingsConst::ridimensionaMin, ui->ridimensionaMin->isChecked());
    Settings::setSettings(SettingsConst::ridimensionaMax, ui->ridimensionaMax->isChecked());
    Settings::setSettings(SettingsConst::ratioWidth, ui->ratioWidth->value());
    Settings::setSettings(SettingsConst::ratioHeight, ui->ratioHeight->value());
    Settings::setSettings(SettingsConst::imageOutputFormat, ui->imageOutputFormat->checkedButton()->text());
    Settings::setSettings(SettingsConst::radioButtonJpg, ui->radioButtonJpg->isChecked());
    Settings::setSettings(SettingsConst::radioButtonPng, ui->radioButtonPng->isChecked());

    // Remove BG
    Settings::setSettings(SettingsConst::apiKeyRemoveBG, ui->apiKeyRemoveBG->text());
    Settings::setSettings(SettingsConst::urlRemoveBG, ui->urlRemoveBG->text());

    this->close();
}

void Options::on_reset_settings_clicked()
{
    ui->percAumento->setValue(8);
    ui->qualitaSalvataggio->setValue(85);
    ui->trasformaQualita->setChecked(true);
    ui->latoMin->setValue(600);
    ui->latoMax->setValue(4500);
    ui->ridimensionaMin->setChecked(true);
    ui->ridimensionaMax->setChecked(true);
}



