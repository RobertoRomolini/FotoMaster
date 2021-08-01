#include "options.h"
#include "ui_options.h"

#include <QFileDialog>

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);


    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //                                                       Imposto le impostazioni da file
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    QString directoryBackup = optionSettings->value("directoryBackup").toString();
    if ( QDir(directoryBackup).exists()) //se la directory non esiste il programma crasha
    {
        ui->directoryBackup->setText(directoryBackup);
    }
    ui->apiKeyRemoveBG->setText(optionSettings->value("apiKeyRemoveBG").toString());
    ui->urlRemoveBG->setText(optionSettings->value("urlRemoveBG").toString());

}

Options::~Options()
{
    delete ui;
}

QString Options::getDirectoryBackup()
{
    return optionSettings->value("directoryBackup").toString();
}

QString Options::getApiKeyRemoveBG()
{
    return optionSettings->value("apiKeyRemoveBG").toString();
}

QString Options::getUrlRemoveBG()
{
    return optionSettings->value("urlRemoveBG").toString();
}

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
    optionSettings->setValue("directoryBackup" , ui->directoryBackup->text() );
    optionSettings->setValue("apiKeyRemoveBG" , ui->apiKeyRemoveBG->text() );
    optionSettings->setValue("urlRemoveBG" , ui->urlRemoveBG->text() );

    this->close();
}
