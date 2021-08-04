#include "optionsWidget.h"
#include "ui_options.h"

#include <QFileDialog>

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);


    //-------------------------------------------------------------------------------//
    //                        Imposto le impostazioni da file
    //-------------------------------------------------------------------------------//
    // Generale
    QString directoryBackup = optionSettings->value("directoryBackup").toString();
    if ( QDir(directoryBackup).exists()) //se la directory non esiste il programma crasha
    {
        ui->directoryBackup->setText(directoryBackup);
    }

    // Trasforma Immagini
    ui->percAumento->setValue(optionSettings->value("percAumento").toInt());
    ui->qualitaSalvataggio->setValue(optionSettings->value("qualitaSalvataggio").toInt());
    ui->trasformaQualita->setChecked(optionSettings->value("trasformaQualita").toBool());
    ui->latoMin->setValue(optionSettings->value("latoMin").toInt());
    ui->latoMax->setValue(optionSettings->value("latoMax").toInt());
    ui->ridimensionaMin->setChecked(optionSettings->value("ridimensionaMin").toBool());
    ui->ridimensionaMax->setChecked(optionSettings->value("ridimensionaMax").toBool());
    ui->ratioWidth->setValue(optionSettings->value("ratioWidth").toInt());
    ui->ratioHeight->setValue(optionSettings->value("ratioHeight").toInt());

    // Remove BG
    ui->apiKeyRemoveBG->setText(optionSettings->value("apiKeyRemoveBG").toString());
    ui->urlRemoveBG->setText(optionSettings->value("urlRemoveBG").toString());

    qDebug() << Settings::getSetting("percAumento");

}

Options::~Options()
{
    delete ui;
}

//--------------------------------------------------------------------------//
//                             Getters and Setters
//--------------------------------------------------------------------------//

QString Options::getDirectoryBackup()
{
    return optionSettings->value("directoryBackup").toString();
}

int Options::getPercAumento()
{
    return ui->percAumento->value();
}

int Options::getQualitaSalvataggio()
{
    return ui->qualitaSalvataggio->value();
}

bool Options::getTrasformaQualita()
{
    return ui->trasformaQualita->isChecked();
}

int Options::getLatoMin()
{
    return ui->latoMin->value();
}

int Options::getLatoMax()
{
    return ui->latoMax->value();
}

bool Options::getRidimensionaMin()
{
    return ui->ridimensionaMin->isChecked();
}

bool Options::getRidimensionaMax()
{
    return ui->ridimensionaMax->isChecked();
}

int Options::getRatioWidth()
{
    return ui->ratioWidth->value();
}

int Options::getRatioHeight()
{
    return ui->ratioHeight->value();
}

QString Options::getApiKeyRemoveBG()
{
    return optionSettings->value("apiKeyRemoveBG").toString();
}

QString Options::getUrlRemoveBG()
{
    return optionSettings->value("urlRemoveBG").toString();
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
    optionSettings->setValue("directoryBackup" , ui->directoryBackup->text());

    // Trasforma Immagini
    optionSettings->setValue("percAumento" , ui->percAumento->value());
    optionSettings->setValue("qualitaSalvataggio" , ui->qualitaSalvataggio->value());
    optionSettings->setValue("trasformaQualita" , ui->trasformaQualita->isChecked());
    optionSettings->setValue("latoMin" , ui->latoMin->value());
    optionSettings->setValue("latoMax" , ui->latoMax->value());
    optionSettings->setValue("ridimensionaMin" , ui->ridimensionaMin->isChecked());
    optionSettings->setValue("ridimensionaMax" , ui->ridimensionaMax->isChecked());
    optionSettings->setValue("ratioWidth" , ui->ratioWidth->value());
    optionSettings->setValue("ratioHeight" , ui->ratioHeight->value());

    // Remove BG
    optionSettings->setValue("apiKeyRemoveBG" , ui->apiKeyRemoveBG->text());
    optionSettings->setValue("urlRemoveBG" , ui->urlRemoveBG->text());

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



