#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Tools/simplecrypt.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //---------------------------------------------------//
    //         Crea le icone nei pushbutton
    //---------------------------------------------------//
    QIcon ButtonIcon(":/Files/Files/editButton.png");
    ui->modifica1->setIcon(ButtonIcon);
    ui->modifica1->setIconSize(QSize(22, 22));
    ui->modifica2->setIcon(ButtonIcon);
    ui->modifica2->setIconSize(QSize(22, 22));
    ui->modifica3->setIcon(ButtonIcon);
    ui->modifica3->setIconSize(QSize(22, 22));
    ui->modifica4->setIcon(ButtonIcon);
    ui->modifica4->setIconSize(QSize(22, 22));
    ui->modifica5->setIcon(ButtonIcon);
    ui->modifica5->setIconSize(QSize(22, 22));
    QIcon indietro (":/Files/Files/indietro.png");
    ui->indietroDirectory->setIcon(indietro);
    ui->indietroDirectory->setIconSize(QSize(22, 22));
    QIcon backupIcon (":/Files/Files/settings.png");
    ui->settingsButton->setIcon(backupIcon);
    ui->settingsButton->setIconSize(QSize(22, 22));
    QIcon refreshRemoveBgIcon (":/Files/Files/refreshIcon.png");
    ui->refreshCrediti->setIcon(refreshRemoveBgIcon);
    ui->refreshCrediti->setIconSize(QSize(18, 18));
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //
    //                                           Crea le cartelle di sistema
    //
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    QDir dirTemp (qApp->applicationDirPath() + "/temp/");
    if (!dirTemp.exists())
        dirTemp.mkpath(qApp->applicationDirPath() + "/temp/");

    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //
    //                                                       Apre la directory di default o in alternativa l'ultima cercata
    //
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    QSettings settings;
    QString directoryBackup(settings.value(SettingsConst::directoryBackup).toString());
    if (directoryBackup != "" && QDir(directoryBackup).exists() )
    {
        ui->directory->setText(directoryBackup);
    }
    else
    {
        QString line = settings.value(SettingsConst::directoryMemory).toString();
        if ( QDir(line).exists()) //se la directory non esiste il programma crasha
        {
            ui->directory->setText(line);
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //
    //                                                        Mostra anterpima database quando il mouse entra nel pulsante
    //
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    connect( ui->sostituisci1 , &QPushButtonGreen::signalEnterMouse , this, [this] ()
    {
        ui->anteprimaFile->vediAnteprima(qApp->applicationDirPath() + "/temp/database1.csv" );
    });
    connect( ui->sostituisci2 , &QPushButtonGreen::signalEnterMouse , this, [this] ()
    {
        ui->anteprimaFile->vediAnteprima(qApp->applicationDirPath() + "/temp/database2.csv" );
    });
    connect( ui->sostituisci3 , &QPushButtonGreen::signalEnterMouse , this, [this] ()
    {
        ui->anteprimaFile->vediAnteprima(qApp->applicationDirPath() + "/temp/database3.csv" );
    });
    connect( ui->sostituisci4 , &QPushButtonGreen::signalEnterMouse , this, [this] ()
    {
        ui->anteprimaFile->vediAnteprima(qApp->applicationDirPath() + "/temp/database4.csv" );
    });
    connect( ui->sostituisci5 , &QPushButtonGreen::signalEnterMouse , this, [this] ()
    {
        ui->anteprimaFile->vediAnteprima(qApp->applicationDirPath() + "/temp/database5.csv" );
    });

    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //
    //                                                       Pulisci tabella quando il puntatore esce dal bottone sostituisci
    //
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    connect( ui->sostituisci1 , &QPushButtonGreen::signalLeaveMouse , ui->anteprimaFile , &QTableWidgetShowDatabase::clearTable );
    connect( ui->sostituisci2 , &QPushButtonGreen::signalLeaveMouse , ui->anteprimaFile , &QTableWidgetShowDatabase::clearTable );
    connect( ui->sostituisci3 , &QPushButtonGreen::signalLeaveMouse , ui->anteprimaFile , &QTableWidgetShowDatabase::clearTable );
    connect( ui->sostituisci4 , &QPushButtonGreen::signalLeaveMouse , ui->anteprimaFile , &QTableWidgetShowDatabase::clearTable );
    connect( ui->sostituisci5 , &QPushButtonGreen::signalLeaveMouse , ui->anteprimaFile , &QTableWidgetShowDatabase::clearTable );

    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //
    //                                                       Connessione del pulsante di modifica al database
    //
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    connect( ui->modifica1 , &QPushButtonBlue::clicked , this, [this] ()
    {
        database->changeLabel("Database 1" , qApp->applicationDirPath() + "/temp/database1.csv");
        database->exec();
    } );
    connect( ui->modifica2 , &QPushButtonBlue::clicked , this, [this] ()
    {
        database->changeLabel("Database 2" , qApp->applicationDirPath() + "/temp/database2.csv");
        database->exec();
    } );
    connect( ui->modifica3 , &QPushButtonBlue::clicked , this, [this] ()
    {
        database->changeLabel("Database 3" , qApp->applicationDirPath() + "/temp/database3.csv");
        database->exec();
    } );
    connect( ui->modifica4 , &QPushButtonBlue::clicked , this, [this] ()
    {
        database->changeLabel("Database 4" , qApp->applicationDirPath() + "/temp/database4.csv");
        database->exec();
    } );
    connect( ui->modifica5 , &QPushButtonBlue::clicked , this, [this] ()
    {
        database->changeLabel("Database 5" , qApp->applicationDirPath() + "/temp/database5.csv");
        database->exec();
    } );

    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //
    //                                                       Connessione del pulsante sostituisci al metodo "sostituisci"
    //
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    connect( ui->sostituisci1 , &QPushButtonGreen::clicked , this, [this] ()
    {
        sostituisci(qApp->applicationDirPath() + "/temp/database1.csv");
    } );
    connect( ui->sostituisci2 , &QPushButtonGreen::clicked , this, [this] ()
    {
        sostituisci(qApp->applicationDirPath() + "/temp/database2.csv");
    } );
    connect( ui->sostituisci3 , &QPushButtonGreen::clicked , this, [this] ()
    {
        sostituisci(qApp->applicationDirPath() + "/temp/database3.csv");
    } );
    connect( ui->sostituisci4 , &QPushButtonGreen::clicked , this, [this] ()
    {
        sostituisci(qApp->applicationDirPath() + "/temp/database4.csv");
    } );
    connect( ui->sostituisci5 , &QPushButtonGreen::clicked , this, [this] ()
    {
        sostituisci(qApp->applicationDirPath() + "/temp/database5.csv");
    } );

    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //                                             Setta le impostazioni dall'ultima chiusura
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    ui->tolleranza->setValue(settings.value(SettingsConst::tolleranza).toInt());
    ui->confrontoBianco->setValue(settings.value(SettingsConst::confrontoBianco).toInt());
    ui->latoMinMD->setValue(settings.value(SettingsConst::latoMinMD).toInt());
    ui->dimMinFileSpinBox->setValue(settings.value(SettingsConst::dimMinFileSpinBox).toInt());
    ui->centraRiquadra->setChecked(settings.value(SettingsConst::centraRiquadra).toBool());
    ui->changeImageFormat->setChecked(settings.value(SettingsConst::changeImageFormat).toBool());
    ui->changeImageFormatDropdown->setCurrentText(settings.value(SettingsConst::changeImageFormatDropdown).toString());
    ui->immaginiQuadrate->setChecked(settings.value(ui->immaginiQuadrate->objectName()).toBool());
    ui->sfondoBianco->setChecked(settings.value(ui->sfondoBianco->objectName()).toBool());
    ui->mostraImmagini->setChecked(settings.value(ui->mostraImmagini->objectName()).toBool());
    ui->percentualeBianco->setChecked(settings.value(ui->percentualeBianco->objectName()).toBool());
    ui->mostraDimensione->setChecked(settings.value(ui->mostraDimensione->objectName()).toBool());
    ui->dimensioneFile->setChecked(settings.value(ui->dimensioneFile->objectName()).toBool());

    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //                                            Comunica alla tabella i valori di Mainwindow
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    ui->contenutoCartella->setLatoMinMD(ui->latoMinMD->value());
    ui->contenutoCartella->setDimMinFileSpinBox(ui->dimMinFileSpinBox->value());
    ui->contenutoCartella->setConfrontoBianco(ui->confrontoBianco->value());

    //Collega le azioni del menu
    connect ( ui->actionEsci , &QAction::triggered , this, &MainWindow::close  );
    connect ( ui->actionRipristina_impostazioni , &QAction::triggered , this, &MainWindow::restoreSettings  );
    connect (ui->actionImpostazioni , &QAction::triggered , options ,  &Options::exec );
    connect (ui->actionAggiornaLista , &QAction::triggered , this, [this] ()
    {
        ui->contenutoCartella->aggiornaLista(ui->directory->text());
    });
    connect (ui->actionAggiornaListaConOpzioni , &QAction::triggered , this ,  [this] ()
    {
        ui->selezionaTutto->setChecked(Qt::Checked);
        ui->contenutoCartella->aggiornaLista(ui->directory->text());
    });


    //Salva le impostazioni per il resize della finestra
    setElementPosition();

    //Collega il tasto removeBg al metodo
    connect( ui->removeBg , &QPushButtonGreen::clicked , this , &MainWindow::chiamataRemoveBg);
    connect( ui->refreshCrediti , &QPushButtonGreen::clicked , this , &MainWindow::chiamataCreditiRemoveBg);

    //Collega il tasto clipDrop al metodo
    connect( ui->sendToClipDrop , &QPushButtonGreen::clicked , this , &MainWindow::sendImagesToClipDrop);
    ui->clipDropCredits->setText(settings.value(SettingsConst::clipDropCredits).toString());
    ui->clipDropCreditsUpdatedAt->setText(settings.value(SettingsConst::clipDropCreditsUpdatedAt).toString());

    //Aggiorno i crediti rimanenti quando apro l'applicazione
    chiamataCreditiRemoveBg();

    // Aggiorna la tabella
    ui->contenutoCartella->aggiornaLista(ui->directory->text());

}

//Distruttore
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createFolderIfNotExists(QString folderName)
{
    if (!QDir(ui->directory->text() + "/" + folderName).exists())
    {
        QDir().mkpath(ui->directory->text() + "/" + folderName);
    }
}

QList<QFileInfo> MainWindow::getImagesToSend(QString directory)
{
    QDir dir(directory);
    QList<QFileInfo> fileList = dir.entryInfoList();
    QList<QFileInfo> newFileList;
    for ( int i=0 ; i < fileList.size() ; i++ )
    {
        QImageReader imageReader (fileList.at(i).absoluteFilePath());
        if ((imageReader.format() == "jpeg" || imageReader.format() == "png") && ui->contenutoCartella->item( i , 0 )->checkState() == Qt::Checked){
          newFileList.append(fileList.at(i));
        }
    }
    return newFileList;
}

void MainWindow::sendImagesToClipDrop()
{
    //Controllo se la tabella è aggiornata
    ui->contenutoCartella->checkTableUpdate(ui->directory->text());

    QList<QFileInfo> fileList = this->getImagesToSend(ui->directory->text());

    QMessageBox sendConfirmation;

    if (fileList.count() != 0)
    {
        sendConfirmation.setText("Sei sicuro di voler inviare a ClipDrop.co " + QString::number(fileList.count()) + " immagine/i?          ");
        sendConfirmation.addButton("Si" , QMessageBox::YesRole);
        sendConfirmation.addButton("No" , QMessageBox::NoRole);

        int ret = sendConfirmation.exec();
        if ( ret == 0)
        {
            this->createFolderIfNotExists("originali_clip_drop");
            this->createFolderIfNotExists("temp");

            QProgressDialog progress("Invio foto a ClipDrop..." , "Annulla" , 0 , fileList.size() , this);
            progress.setWindowModality(Qt::WindowModal);
            progress.setWindowTitle("FotoMaster");
            progress.setMinimumDuration(200);

            QSettings settings;

            for ( int i=0 ; i < fileList.size() ; i++ )
            {
                progress.setValue(i);
                if (progress.wasCanceled())
                {
                    break;
                }

                //Creo la chiamata post al server
                QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

                QHttpPart imagePart;
                imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; filename=\""+ fileList.at(i).fileName() +"\"; name=\"image_file\";"));
                //Copio il file nella cartella temp
                QFile::copy(fileList.at(i).absoluteFilePath()  , ui->directory->text() + "/temp/" + fileList.at(i).fileName());
                QFile *file = new QFile( ui->directory->text() + "/temp/" + fileList.at(i).fileName());
                file->open(QIODevice::ReadOnly);
                imagePart.setBodyDevice(file);

                //Setto il parent in modo che venga eliminato quando elimino quest'ultimo
                file->setParent(multiPart);

                multiPart->append(imagePart);

                SimpleCrypt crypt(SettingsConst::simpleCryptKey);
                QNetworkRequest request;
                request.setUrl(QUrl(this->clipDropApiBaseUrl + "/remove-background/v1"));
                request.setRawHeader("x-api-key", crypt.decryptToString(settings.value(SettingsConst::clipDropApiKey).toString()).toUtf8());

                QNetworkReply *reply = clipDropManager->post(request , multiPart);

                //Setto il parent in modo che venga eliminato quando elimino quest'ultimo
                multiPart->setParent(reply);

                QString absoluthFilePath = fileList.at(i).absoluteFilePath();
                connect(clipDropManager, &QNetworkAccessManager::finished, this, [reply , absoluthFilePath , this ]
                {
                    responseFromClipDrop(reply , absoluthFilePath);
                });

                //Attende la risposta prima di proseguire con il loop
                QEventLoop loop;
                connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
                loop.exec();

                //Chiudo il file altirmenti non posso cancellare la cartella temporanea
                file->close();


            }
            //Elimino la cartella temp
            QDir tempDirectory(ui->directory->text() + "/temp");
            tempDirectory.removeRecursively();
            //Aggiorno la tabella una volta finito
            ui->contenutoCartella->aggiornaLista(ui->directory->text());
        }
    }

}

void MainWindow::responseFromClipDrop(QNetworkReply *reply , QString absoluthFilePath)
{
    QSettings settings;
    QFileInfo fileInfo(absoluthFilePath);

    QByteArray data (reply->readAll());

    //Sposto i file nella cartella "originali" se non ci sono errori
    if (reply->error() == 0)
    {
        QFile::rename(absoluthFilePath  , ui->directory->text() + "/originali_clip_drop/" +fileInfo.fileName());
    }

    QString fileExtension = settings.value(SettingsConst::clipDropImageFormat).toString().toUtf8();
    QPixmap img;
    img.loadFromData(data);
    img.save(ui->directory->text() + "/" + fileInfo.completeBaseName() +"." +  fileExtension);

    QString remainingCredits = QString::number(reply->rawHeader("x-remaining-credits").toInt());
    ui->clipDropCredits->setText(remainingCredits);
    QString now = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm");
    ui->clipDropCreditsUpdatedAt->setText(now);
    settings.setValue(SettingsConst::clipDropCredits, remainingCredits);
    settings.setValue(SettingsConst::clipDropCreditsUpdatedAt, now);

    clipDropManager->disconnect();
    reply->deleteLater();
}

//------------------------------------------------------------------------------------------------------------------------------------------------//
//
//                                                                                             Remove BG
//
//------------------------------------------------------------------------------------------------------------------------------------------------//


void MainWindow::chiamataRemoveBg()
{
    //Controllo se la tabella è aggiornata
    ui->contenutoCartella->checkTableUpdate(ui->directory->text());

    QList<QFileInfo> fileList = getImagesToSend(ui->directory->text());
    QMessageBox sendConfirmation;

    if (fileList.count() != 0)
    {
        sendConfirmation.setText("Sei sicuro di voler inviare a removebg " + QString::number(fileList.count()) + " immagine/i?          ");
        sendConfirmation.addButton("Si" , QMessageBox::YesRole);
        sendConfirmation.addButton("No" , QMessageBox::NoRole);

        int ret = sendConfirmation.exec();
        if ( ret == 0)
        {
            this->createFolderIfNotExists("originali_remove_bg");
            this->createFolderIfNotExists("temp");

            QProgressDialog progress("Invio foto a removebg..." , "Annulla" , 0 , fileList.size() , this);
            progress.setWindowModality(Qt::WindowModal);
            progress.setWindowTitle("FotoMaster");
            progress.setMinimumDuration(200);

            QSettings settings;

            for ( int i=0 ; i < fileList.size() ; i++ )
            {
                progress.setValue(i);
                if (progress.wasCanceled())
                {
                    break;
                }

                QImageReader imageReader (fileList.at(i).absoluteFilePath());

                if ((imageReader.format() == "jpeg" || imageReader.format() == "png") && ui->contenutoCartella->item( i , 0 )->checkState() == Qt::Checked)
                {
                    imageReader.setFileName("");

                    //Creo la chiamata post al server
                    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

                    QHttpPart format;
                    format.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"format\""));
                    format.setBody(settings.value(SettingsConst::removeBgImageFormat).toString().toUtf8());

                    QHttpPart size;
                    size.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"size\""));
                    size.setBody(settings.value(SettingsConst::removeBgImageSize).toString().toUtf8());

                    QHttpPart imagePart;
                    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; filename=\""+ fileList.at(i).fileName() +"\"; name=\"image_file\";"));
                    //Copio il file nella cartella temp
                    QFile::copy(fileList.at(i).absoluteFilePath()  , ui->directory->text() + "/temp/" + fileList.at(i).fileName());
                    QFile *file = new QFile( ui->directory->text() + "/temp/" + fileList.at(i).fileName());
                    file->open(QIODevice::ReadOnly);
                    imagePart.setBodyDevice(file);

                    //Setto il parent in modo che venga eliminato quando elimino quest'ultimo
                    file->setParent(multiPart);

                    multiPart->append(size);
                    multiPart->append(format);
                    multiPart->append(imagePart);

                    SimpleCrypt crypt(SettingsConst::simpleCryptKey);
                    QNetworkRequest request;
                    request.setUrl(QUrl(settings.value(SettingsConst::urlRemoveBG).toString()));
                    request.setRawHeader("X-Api-Key", crypt.decryptToString(settings.value(SettingsConst::apiKeyRemoveBG).toString()).toUtf8());

                    QNetworkReply *reply = manager->post(request , multiPart);

                    //Setto il parent in modo che venga eliminato quando elimino quest'ultimo
                    multiPart->setParent(reply);

                    QString absoluthFilePath = fileList.at(i).absoluteFilePath();
                    connect(manager, &QNetworkAccessManager::finished, this, [reply , absoluthFilePath , this ]
                    {
                        rispostaRemoveBg(reply , absoluthFilePath);
                    });

                    //Attende la risposta prima di proseguire con il loop
                    QEventLoop loop;
                    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
                    loop.exec();

                    //Chiudo il file altirmenti non posso cancellare la cartella temporanea
                    file->close();

                }
            }
            //Elimino la cartella temp
            QDir tempDirectory(ui->directory->text() + "/temp");
            tempDirectory.removeRecursively();
            //Aggiorno la tabella una volta finito
            ui->contenutoCartella->aggiornaLista(ui->directory->text());
        }
    }
}

void MainWindow::rispostaRemoveBg(QNetworkReply *reply , QString absoluthFilePath)
{
    QSettings settings;
    QFileInfo fileInfo(absoluthFilePath);

    QByteArray data (reply->readAll());

    //Sposto i file nella cartella "originali" se non ci sono errori
    if (reply->error() == 0)
    {
        QFile::rename(absoluthFilePath  , ui->directory->text() + "/originali_remove_bg/" +fileInfo.fileName());
    }

    if (settings.value(SettingsConst::removeBgImageFormat).toString().toUtf8() == "zip")
    {
        QFile file (ui->directory->text() + "/" + fileInfo.completeBaseName() +".zip");
        file.open(QIODevice::WriteOnly);
        file.write(data);
        file.flush();
        file.close();
    }
    else
    {
        QPixmap img;
        img.loadFromData(data);
        img.save(ui->directory->text() + "/" + fileInfo.completeBaseName() +"." + settings.value(SettingsConst::removeBgImageFormat).toString().toUtf8() );
    }
    manager->disconnect();
    reply->deleteLater();
}

void MainWindow::chiamataCreditiRemoveBg()
{
    QSettings settings;
    SimpleCrypt crypt(SettingsConst::simpleCryptKey);
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.remove.bg/v1.0/account"));
    request.setRawHeader("X-Api-Key", crypt.decryptToString(settings.value(SettingsConst::apiKeyRemoveBG).toString()).toUtf8());

    connect(managerCrediti, &QNetworkAccessManager::finished, this, &MainWindow::rispostaCreditiRemoveBg);
    managerCrediti->get(request);
}

void MainWindow::rispostaCreditiRemoveBg(QNetworkReply *reply)
{
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObject = jsonResponse.object();

    int crediti = jsonObject.value("data").toObject().value("attributes").toObject().value("credits").toObject().value("total").toInt();
    ui->creditiRimanenti->setText(QString::number(crediti));
    managerCrediti->disconnect();
    reply->deleteLater();
}

//------------------------------------------------------------------------------------------------------------------------------------------------//
//
//                                                              Sostituisci le parole dei nomi file come nel database
//
//------------------------------------------------------------------------------------------------------------------------------------------------//

void MainWindow::sostituisci(QString database)
{
    QFile fileDatabase1(database);
    fileDatabase1.open(QIODevice::ReadOnly | QFile::Text);
    QTextStream in(&fileDatabase1);
    QString filename = qApp->applicationDirPath() + "/temp/temp.csv";
    QFile fileMemory(filename);
    fileMemory.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&fileMemory);
    QDir dir(ui->directory->text());
    QList<QFileInfo> fileList = dir.entryInfoList();
    QFile file;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QString trovare = line.split(";").at(0);
        QString sostituire = line.split(";").at(1);
        for ( int i=0 ; i < fileList.size() ; i++ )
        {
            QString fileName1 = fileList.at(i).fileName().replace(trovare , sostituire , Qt::CaseSensitive);
            if (fileList.at(i).fileName() != fileName1)
            {
                stream << fileName1 << ";" << fileList.at(i).fileName() << Qt::endl;
            }
            file.rename( ui->directory->text() + "/" + fileList.at(i).fileName() , ui->directory->text() + "/" + fileName1  );
        }
    }
    fileMemory.close();
    fileDatabase1.close();
    ui->contenutoCartella->aggiornaLista(ui->directory->text());
}

void MainWindow::cancellaDatiFile (QString nomeFile)
{
    QFile fileMemory(qApp->applicationDirPath() + nomeFile);
    fileMemory.open(QIODevice::WriteOnly | QIODevice::Truncate);
    fileMemory.close();
}

//------------------------------------------------------------------------------------------------------------------------------------------------//
//
//                                                      Collega azioni del menu a tendina
//
//------------------------------------------------------------------------------------------------------------------------------------------------//

//Ripristina i valori predefiniti
void MainWindow::restoreSettings()
{
    ui->tolleranza->setValue(15);
    ui->confrontoBianco->setValue( 50);
    ui->latoMinMD->setValue(600);
    ui->dimMinFileSpinBox->setValue(500);
}

//------------------------------------------------------------------------------------------------------------------------------------------------//
//
//                                                      Modifica l'immagine riquadrandola
//
//------------------------------------------------------------------------------------------------------------------------------------------------//

void MainWindow::on_trasformaImmagini_clicked()
{
    Logger::addLog("Click on button 'Trasforma Immagini'");

    //Controllo se la cartella è stata aggiornata prima di lanciare la funzione
    ui->contenutoCartella->checkTableUpdate(ui->directory->text());

    QDir dir(ui->directory->text());
    QList<QFileInfo> fileList = dir.entryInfoList();
    QProgressDialog progress("Elaborazione foto..." , "Annulla" , 0 , fileList.size() , this);
    progress.setWindowTitle("FotoMaster");
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(200);

    QSettings settings;

    //Creo la cartella temporanea di appoggio dei file
    if (! QDir(ui->directory->text() + "/temp").exists())
    {
        QDir().mkpath(ui->directory->text() + "/temp" );
    }

    //Creo la cartella di backup
    if (! QDir(ui->directory->text() + "/originali_foto_master").exists())
    {
        QDir().mkpath(ui->directory->text() + "/originali_foto_master" );
    }

    for ( int i=0 ; i < fileList.size() ; i++ )
    {
        progress.setValue(i);
        if (progress.wasCanceled())
        {
            break;
        }

        QImageReader imageReader(fileList.at(i).absoluteFilePath());

        if ( imageReader.canRead() && ui->contenutoCartella->item( i , 0 )->checkState() == Qt::Checked)
        {
            Logger::addLog("File name: " + fileList.at(i).absoluteFilePath() );

            imageReader.setFileName("");

            QFile::rename(fileList.at(i).absoluteFilePath(), ui->directory->text() + "/temp/" + fileList.at(i).fileName());

            ImageProcessor image (ui->directory->text() + "/temp/" + fileList.at(i).fileName());

            image.fixOrientationImage();

            image.saveImage(ui->directory->text() + "/originali_foto_master/" + fileList.at(i).fileName(), 85);

            QString newBasename(ui->directory->text() + "/" + fileList.at(i).completeBaseName());

            if (ui->changeImageFormat->isChecked())
            {
                Logger::addLog("'Trasforma' is checked");

                QString imageFormat(ui->changeImageFormatDropdown->currentText());

                image.setNewImage(imageFormat);
                image.modifyImageFormat();

                image.saveNewImage(newBasename + "." + imageFormat, 85);
            }
            else if (ui->centraRiquadra->isChecked())
            {
                Logger::addLog("'Centra' is checked");

                if (settings.value(SettingsConst::saveImageFolders).toBool())
                {
                    if (!QDir(ui->directory->text() + "/jpg").exists() && settings.value(SettingsConst::outputJpg).toBool())
                    {
                        QDir().mkpath(ui->directory->text() + "/jpg" );
                    }

                    if (!QDir(ui->directory->text() + "/png").exists() && settings.value(SettingsConst::outputPng).toBool())
                    {
                        QDir().mkpath(ui->directory->text() + "/png" );
                    }

                    if (!QDir(ui->directory->text() + "/webp").exists() && settings.value(SettingsConst::outputWebp).toBool())
                    {
                        QDir().mkpath(ui->directory->text() + "/webp" );
                    }
                }

                double percBasso = -1;

                if (settings.value(SettingsConst::outputJpg).toBool())
                {
                    if (settings.value(SettingsConst::cbPercBassoJpg).toBool())
                    {
                        percBasso = settings.value(SettingsConst::percentualeBassoJpg).toInt();
                    }

                    image.setNewImage("jpg", settings.value(SettingsConst::backgroundJpg).toString());
                    image.centerImage(settings.value(SettingsConst::ratioHeightJpg).toInt(),
                                      settings.value(SettingsConst::ratioWidthJpg).toInt(),
                                      settings.value(SettingsConst::percAumento).toInt(),
                                      percBasso,
                                      ui->tolleranza->value());

                    image = this->checkSideSize(image);

                    if (settings.value(SettingsConst::saveImageFolders).toBool())
                    {
                        newBasename = ui->directory->text() + "/jpg/" + fileList.at(i).completeBaseName();
                    }

                    image.saveNewImage(newBasename + ".jpg", settings.value(SettingsConst::qualitaSalvataggioJpg).toInt());
                }

                if (settings.value(SettingsConst::outputPng).toBool())
                {
                    if (settings.value(SettingsConst::cbPercBassoPng).toBool())
                    {
                        percBasso = settings.value(SettingsConst::percentualeBassoPng).toInt();
                    }

                    image.setNewImage("png");
                    image.centerImage(settings.value(SettingsConst::ratioHeightPng).toInt(),
                                      settings.value(SettingsConst::ratioWidthPng).toInt(),
                                      settings.value(SettingsConst::percAumento).toInt(),
                                      percBasso,
                                      ui->tolleranza->value());

                    image = this->checkSideSize(image);

                    if (settings.value(SettingsConst::saveImageFolders).toBool())
                    {
                        newBasename = ui->directory->text() + "/png/" + fileList.at(i).completeBaseName();
                    }

                    image.saveNewImage(newBasename + ".png", settings.value(SettingsConst::qualitaSalvataggioPng).toInt());
                }

                if (settings.value(SettingsConst::outputWebp).toBool())
                {
                    if (settings.value(SettingsConst::cbPercBassoWebp).toBool())
                    {
                        percBasso = settings.value(SettingsConst::percentualeBassoWebp).toInt();
                    }

                    image.setNewImage("webp");
                    image.centerImage(settings.value(SettingsConst::ratioHeightWebp).toInt(),
                                      settings.value(SettingsConst::ratioWidthWebp).toInt(),
                                      settings.value(SettingsConst::percAumento).toInt(),
                                      percBasso,
                                      ui->tolleranza->value());

                    image = this->checkSideSize(image);

                    if (settings.value(SettingsConst::saveImageFolders).toBool())
                    {
                        newBasename = ui->directory->text() + "/webp/" + fileList.at(i).completeBaseName();
                    }

                    image.saveNewImage(newBasename + ".webp", settings.value(SettingsConst::qualitaSalvataggioWebp).toInt());
                }
            }
        }
    }

    //Elimino la cartella temp
    QDir tempDirectory(ui->directory->text() + "/temp");
    tempDirectory.removeRecursively();

    ui->contenutoCartella->aggiornaLista(ui->directory->text());
}

ImageProcessor MainWindow::checkSideSize(ImageProcessor image)
{
    QSettings settings;
    // Controlla se il lato è minore o maggiore del valore dello spinbox e ridimensiona la foto
    if (settings.value(SettingsConst::ridimensionaMin).toBool())
    {
        image.scaledNewImageToMin(settings.value(SettingsConst::latoMin).toInt());
    }
    if (settings.value(SettingsConst::ridimensionaMax).toBool())
    {
        image.scaledNewImageToMax(settings.value(SettingsConst::latoMax).toInt());
    }

    return image;
}

//-------------------------------------------------------------------------------------------------------------//
//                                         Overrided methods
//-------------------------------------------------------------------------------------------------------------//
void MainWindow::closeEvent(QCloseEvent *)
{
    QSettings settings;
    settings.setValue(SettingsConst::tolleranza, ui->tolleranza->value());
    settings.setValue(SettingsConst::confrontoBianco, ui->confrontoBianco->value());
    settings.setValue(SettingsConst::latoMinMD, ui->latoMinMD->value());
    settings.setValue(SettingsConst::dimMinFileSpinBox, ui->dimMinFileSpinBox->value());
    settings.setValue(SettingsConst::centraRiquadra, ui->centraRiquadra->isChecked());
    settings.setValue(SettingsConst::changeImageFormat, ui->changeImageFormat->isChecked());
    settings.setValue(SettingsConst::changeImageFormatDropdown, ui->changeImageFormatDropdown->currentText());
    settings.setValue(ui->immaginiQuadrate->objectName(), ui->immaginiQuadrate->isChecked());
    settings.setValue(ui->sfondoBianco->objectName(), ui->sfondoBianco->isChecked());
    settings.setValue(ui->mostraImmagini->objectName(), ui->mostraImmagini->isChecked());
    settings.setValue(ui->percentualeBianco->objectName(), ui->percentualeBianco->isChecked());
    settings.setValue(ui->mostraDimensione->objectName(), ui->mostraDimensione->isChecked());
    settings.setValue(ui->dimensioneFile->objectName(), ui->dimensioneFile->isChecked());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeWindow->setWidthHeightIncrement(event , this);

    //Move only Y
    resizeWindow->moveWidgetY(ui->centraRiquadra);
    resizeWindow->moveWidgetY(ui->tolleranza);
    resizeWindow->moveWidgetY(ui->label_4);
    resizeWindow->moveWidgetY(ui->trasformaImmagini);
    resizeWindow->moveWidgetY(ui->trasformaImmaginiBox);
    resizeWindow->moveWidgetY(ui->changeImageFormat);
    resizeWindow->moveWidgetY(ui->label_5);
    resizeWindow->moveWidgetY(ui->refreshCrediti);
    resizeWindow->moveWidgetY(ui->creditiRimanenti);
    resizeWindow->moveWidgetY(ui->removeBg);
    resizeWindow->moveWidgetY(ui->trasformaImmaginiBox_2);
    resizeWindow->moveWidgetY(ui->changeImageFormatDropdown);
    resizeWindow->moveWidgetY(ui->label_6);
    resizeWindow->moveWidgetY(ui->clipDropCredits);
    resizeWindow->moveWidgetY(ui->clipDropCreditsUpdatedAt);
    resizeWindow->moveWidgetY(ui->sendToClipDrop);
    resizeWindow->moveWidgetY(ui->trasformaImmaginiBox_3);

    //Muove solo X
    resizeWindow->moveWidgetY(ui->selezionaDeseleziona);
    resizeWindow->moveWidgetX(ui->indietroDirectory);
    resizeWindow->moveWidgetX(ui->scegliCartella);
    resizeWindow->moveWidgetX(ui->settingsButton);
    resizeWindow->moveWidgetX(ui->sostituisci1);
    resizeWindow->moveWidgetX(ui->sostituisci2);
    resizeWindow->moveWidgetX(ui->sostituisci3);
    resizeWindow->moveWidgetX(ui->sostituisci4);
    resizeWindow->moveWidgetX(ui->sostituisci5);
    resizeWindow->moveWidgetX(ui->modifica1);
    resizeWindow->moveWidgetX(ui->modifica2);
    resizeWindow->moveWidgetX(ui->modifica3);
    resizeWindow->moveWidgetX(ui->modifica4);
    resizeWindow->moveWidgetX(ui->modifica5);
    resizeWindow->moveWidgetX(ui->annullaModifiche);
    resizeWindow->moveWidgetX(ui->label);
    resizeWindow->moveWidgetX(ui->label_2);
    resizeWindow->moveWidgetX(ui->label_3);
    resizeWindow->moveWidgetX(ui->trovareRapido);
    resizeWindow->moveWidgetX(ui->sostituireRapido);
    resizeWindow->moveWidgetX(ui->sostituisciRapido);
    resizeWindow->moveWidgetX(ui->sostituisciBox);
    resizeWindow->moveWidgetX(ui->sostituisciRapidoBox);
    resizeWindow->moveWidgetX(ui->anteprimaFile);

    //Muove X e Y
    resizeWindow->moveWidgetXY(ui->aggiorna);
    resizeWindow->moveWidgetXY(ui->immaginiQuadrate);
    resizeWindow->moveWidgetXY(ui->sfondoBianco);
    resizeWindow->moveWidgetXY(ui->mostraImmagini);
    resizeWindow->moveWidgetXY(ui->percentualeBianco);
    resizeWindow->moveWidgetXY(ui->mostraDimensione);
    resizeWindow->moveWidgetXY(ui->dimensioneFile);
    resizeWindow->moveWidgetXY(ui->confrontoBianco);
    resizeWindow->moveWidgetXY(ui->latoMinMD);
    resizeWindow->moveWidgetXY(ui->dimMinFileSpinBox);
    resizeWindow->moveWidgetXY(ui->selezionaTutto);
    resizeWindow->moveWidgetXY(ui->opzioniTabellaBox);
    resizeWindow->moveWidgetXY(ui->opzioniTabellaLine);

    //Resize XY
    resizeWindow->resizeWidgetXY(ui->contenutoCartella);

    //Resize Height
    resizeWindow->resizeWidgetY(ui->anteprimaFile);

    //Resize Width
    resizeWindow->resizeWidgetX(ui->directory);

    ui->contenutoCartella->tableResize();
}

void MainWindow::setElementPosition()
{
    resizeWindow->setObjectGeometry(this);

    resizeWindow->setObjectGeometry(ui->indietroDirectory);
    resizeWindow->setObjectGeometry(ui->selezionaDeseleziona);
    resizeWindow->setObjectGeometry(ui->directory);
    resizeWindow->setObjectGeometry(ui->settingsButton);
    resizeWindow->setObjectGeometry(ui->sostituisci1);
    resizeWindow->setObjectGeometry(ui->sostituisci2);
    resizeWindow->setObjectGeometry(ui->sostituisci3);
    resizeWindow->setObjectGeometry(ui->sostituisci4);
    resizeWindow->setObjectGeometry(ui->sostituisci5);
    resizeWindow->setObjectGeometry(ui->modifica1);
    resizeWindow->setObjectGeometry(ui->modifica2);
    resizeWindow->setObjectGeometry(ui->modifica3);
    resizeWindow->setObjectGeometry(ui->modifica4);
    resizeWindow->setObjectGeometry(ui->modifica5);
    resizeWindow->setObjectGeometry(ui->annullaModifiche);
    resizeWindow->setObjectGeometry(ui->label);
    resizeWindow->setObjectGeometry(ui->label_2);
    resizeWindow->setObjectGeometry(ui->label_3);
    resizeWindow->setObjectGeometry(ui->trovareRapido);
    resizeWindow->setObjectGeometry(ui->sostituireRapido);
    resizeWindow->setObjectGeometry(ui->sostituisciRapido);
    resizeWindow->setObjectGeometry(ui->aggiorna);
    resizeWindow->setObjectGeometry(ui->immaginiQuadrate);
    resizeWindow->setObjectGeometry(ui->sfondoBianco);
    resizeWindow->setObjectGeometry(ui->mostraImmagini);
    resizeWindow->setObjectGeometry(ui->contenutoCartella);
    resizeWindow->setObjectGeometry(ui->opzioniTabellaBox);
    resizeWindow->setObjectGeometry(ui->opzioniTabellaLine);
    resizeWindow->setObjectGeometry(ui->trasformaImmaginiBox);
    resizeWindow->setObjectGeometry(ui->sostituisciBox);
    resizeWindow->setObjectGeometry(ui->sostituisciRapidoBox);
    resizeWindow->setObjectGeometry(ui->selezionaTutto);
    resizeWindow->setObjectGeometry(ui->dimMinFileSpinBox);
    resizeWindow->setObjectGeometry(ui->latoMinMD);
    resizeWindow->setObjectGeometry(ui->confrontoBianco);
    resizeWindow->setObjectGeometry(ui->dimensioneFile);
    resizeWindow->setObjectGeometry(ui->mostraDimensione);
    resizeWindow->setObjectGeometry(ui->percentualeBianco);
    resizeWindow->setObjectGeometry(ui->scegliCartella);
    resizeWindow->setObjectGeometry(ui->anteprimaFile);
    resizeWindow->setObjectGeometry(ui->centraRiquadra);
    resizeWindow->setObjectGeometry(ui->tolleranza);
    resizeWindow->setObjectGeometry(ui->label_4);
    resizeWindow->setObjectGeometry(ui->trasformaImmagini);
    resizeWindow->setObjectGeometry(ui->changeImageFormat);
    resizeWindow->setObjectGeometry(ui->label_5);
    resizeWindow->setObjectGeometry(ui->refreshCrediti);
    resizeWindow->setObjectGeometry(ui->creditiRimanenti);
    resizeWindow->setObjectGeometry(ui->removeBg);
    resizeWindow->setObjectGeometry(ui->trasformaImmaginiBox_2);
    resizeWindow->setObjectGeometry(ui->changeImageFormatDropdown);
    resizeWindow->setObjectGeometry(ui->clipDropCredits);
    resizeWindow->setObjectGeometry(ui->sendToClipDrop);
    resizeWindow->setObjectGeometry(ui->trasformaImmaginiBox_3);
    resizeWindow->setObjectGeometry(ui->label_6);
    resizeWindow->setObjectGeometry(ui->clipDropCreditsUpdatedAt);
}

//-----------------------------------------------------------------------------------------------------//
//
//                                          Private slots
//
//-----------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------//
//                               Azionano la sostituzione dei nomi dei file
//-----------------------------------------------------------------------------------------------------//

void MainWindow::on_sostituisciRapido_clicked()
{
    QString filename = qApp->applicationDirPath() + "/temp/temp.csv";
    QFile fileMemory(filename);
    QString trovare = ui->trovareRapido->text();
    QString sostituire = ui->sostituireRapido->text();
    QDir dir(ui->directory->text());
    QList<QFileInfo> fileList = dir.entryInfoList();
    QFile file(ui->directory->text());

    fileMemory.open(QIODevice::WriteOnly | QIODevice::Append);
    if (ui->trovareRapido->text() != "")
    {
        for ( int i=0 ; i < fileList.size() ; i++ )
        {
            QString fileName1 = fileList.at(i).fileName().replace(trovare , sostituire , Qt::CaseSensitive);
            QTextStream stream(&fileMemory);
            if (fileList.at(i).fileName() != fileName1)
            {
                stream << fileName1 << ";" << fileList.at(i).fileName() << Qt::endl;
            }
            file.rename( ui->directory->text() + "/" + fileList.at(i).fileName() , ui->directory->text() + "/" + fileName1  );
        }
        fileMemory.close();
    }
    ui->contenutoCartella->aggiornaLista(ui->directory->text());
}

void MainWindow::on_annullaModifiche_clicked()
{
    QFile fileDatabase1(qApp->applicationDirPath() + "/temp/temp.csv");
    fileDatabase1.open(QIODevice::ReadOnly | QFile::Text);
    QTextStream in(&fileDatabase1);
    QDir dir(ui->directory->text());
    QList<QFileInfo> fileList = dir.entryInfoList();
    QFile file;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QString trovare = line.split(";").at(0);
        QString sostituire = line.split(";").at(1);
        for ( int i=0 ; i < fileList.size() ; i++ )
        {
            QString fileName1 = fileList.at(i).fileName().replace(trovare , sostituire , Qt::CaseSensitive);
            file.rename( ui->directory->text() + "/" + fileList.at(i).fileName() , ui->directory->text() + "/" + fileName1  );
        }
    }
    fileDatabase1.close();
    ui->contenutoCartella->aggiornaLista(ui->directory->text());
    cancellaDatiFile ("/temp/temp.csv");
}

//--------------------------------------------------------------------------------------------------------------//
//                                   Naviga tra le directory e crea memoria con l'ultima cercata
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_scegliCartella_clicked()
{
    QSettings settings;
    QString line = settings.value(SettingsConst::directoryMemory).toString();
    QString filename = QFileDialog::getExistingDirectory(this, "Scegli Cartella" , line);
    if (line != filename && filename != "")
    {
        settings.setValue(SettingsConst::directoryMemory, filename);
    }
    if (filename.isEmpty())
        return;
    ui->directory->setText(filename);
    ui->contenutoCartella->aggiornaLista(ui->directory->text());
}

//--------------------------------------------------------------------------------------------------------------//
//                                                          Apre la cartella di backup
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_settingsButton_clicked()
{
    options->exec();
}

//--------------------------------------------------------------------------------------------------------------//
//                                                             Aggiorna la lista dei file
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_aggiorna_clicked()
{

    ui->contenutoCartella->aggiornaLista(ui->directory->text());
}

//--------------------------------------------------------------------------------------------------------------//
//                                                Torna indietro alla cartella precedente
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_indietroDirectory_clicked()
{
    QSettings settings;
    QString directory = ui->directory->text();
    directory.truncate(directory.lastIndexOf(QChar('/')));
    ui->directory->setText(directory);
    ui->contenutoCartella->aggiornaLista(ui->directory->text());
    settings.setValue(SettingsConst::directoryMemory, directory);
}

//--------------------------------------------------------------------------------------------------------------//
//                                                  Naviga tra le cartelle con doppio click
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_contenutoCartella_itemDoubleClicked(QTableWidgetItem *item)
{
    QSettings settings;
    QString directory = item->text();
    QFile file (directory);
    QFileInfo fileInfo (file);
    if (fileInfo.isDir())
    {
        ui->directory->setText(directory);
        ui->contenutoCartella->aggiornaLista(ui->directory->text());
        settings.setValue(SettingsConst::directoryMemory, directory);
    }
}

//--------------------------------------------------------------------------------------------------------------//
//                                         Seleziona/Deselezione tutte le opzioni della tabella
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_selezionaTutto_stateChanged(int state)
{
    ui->percentualeBianco->setChecked(state);
    ui->mostraDimensione->setChecked(state);
    ui->dimensioneFile->setChecked(state);
    ui->mostraImmagini->setChecked(state);
    ui->sfondoBianco->setChecked(state);
    ui->immaginiQuadrate->setChecked(state);
}

//--------------------------------------------------------------------------------------------------------------//
//                              Seleziona/Deselezione tutti checkbox all'interno della tabella
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_selezionaDeseleziona_stateChanged()
{
    QDir dir(ui->directory->text());
    QList<QFileInfo> fileList = dir.entryInfoList();
    for ( int i=0 ; i < fileList.size() ; i++ )
    {
        QImageReader imageReader (fileList.at(i).absoluteFilePath());
        if (!ui->selezionaDeseleziona->isChecked() && imageReader.canRead())
        {
            ui->contenutoCartella->item( i , 0 )->setCheckState(Qt::Unchecked);
        }
        else if (ui->selezionaDeseleziona->isChecked() && imageReader.canRead())
        {
            ui->contenutoCartella->item( i , 0 )->setCheckState(Qt::Checked);
        }
    }
}

//--------------------------------------------------------------------------------------------------------------//
//                                Comunica alla tabella ogni cambiamento di stato dei checkbox
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_immaginiQuadrate_stateChanged(int state)
{
    ui->contenutoCartella->setImmaginiQuadrate(state);
}

void MainWindow::on_sfondoBianco_stateChanged(int state)
{
    ui->contenutoCartella->setSfondoBianco(state);
}

void MainWindow::on_mostraImmagini_stateChanged(int state)
{
    ui->contenutoCartella->setMostraImmagini(state);
}

void MainWindow::on_percentualeBianco_stateChanged(int state)
{
    ui->contenutoCartella->setPercentualeBianco(state);
}

void MainWindow::on_mostraDimensione_stateChanged(int state)
{
    ui->contenutoCartella->setMostraDimensione(state);
}

void MainWindow::on_dimensioneFile_stateChanged(int state)
{
    ui->contenutoCartella->setDimensioneFile(state);
}

void MainWindow::on_selezionaDeseleziona_stateChanged(int state)
{
    ui->contenutoCartella->setSelezionaDeseleziona(state);
}

void MainWindow::on_latoMinMD_valueChanged(int value)
{
    ui->contenutoCartella->setLatoMinMD(value);
};

void MainWindow::on_dimMinFileSpinBox_valueChanged(int arg1)
{
    ui->contenutoCartella->setDimMinFileSpinBox(arg1);
}

void MainWindow::on_confrontoBianco_valueChanged(int arg1)
{
    ui->contenutoCartella->setConfrontoBianco(arg1);
}


