#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Tools/imageprocessor.h>

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
    QIcon backupIcon (":/Files/Files/backupFolder.png");
    ui->backupFolder->setIcon(backupIcon);
    ui->backupFolder->setIconSize(QSize(22, 22));
    QIcon refreshRemoveBgIcon (":/Files/Files/refreshIcon.png");
    ui->refreshCrediti->setIcon(refreshRemoveBgIcon);
    ui->refreshCrediti->setIconSize(QSize(18, 18));
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //
    //                                           Crea le cartelle di sistema e verifica che la cartella di backup non superi i 200 MB
    //
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    QDir dirTemp (qApp->applicationDirPath() + "/temp/");
    QDir dirBackup (qApp->applicationDirPath() + "/backup/");
    QFileInfoList list = dirBackup.entryInfoList();
    long int sizex = 0;
    for(int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        if ( fileInfo.fileName() != "." && fileInfo.fileName() != ".." )
        {
            sizex +=  fileInfo.size();
        }
    }
    if ( sizex > 200000000 )
    {
        dirBackup.removeRecursively();
    }
    qDebug () << "La dimensione della cartella Backup è: " << sizex/1000000 << " Megabytes";
    if (!dirTemp.exists())
        dirTemp.mkpath(qApp->applicationDirPath() + "/temp/");
    if (!dirBackup.exists())
        dirBackup.mkpath(qApp->applicationDirPath() + "/backup/");

    //------------------------------------------------------------------------------------------------------------------------------------------------//
    //
    //                                                       Apre la directory di default o in alternativa l'ultima cercata
    //
    //------------------------------------------------------------------------------------------------------------------------------------------------//
    QString directoryBackup(Settings::getSettingsString(SettingsConst::directoryBackup));
    if (directoryBackup != "" && QDir(directoryBackup).exists() )
    {
        ui->directory->setText(directoryBackup);
    }
    else
    {
        QString line = Settings::getSettingsString(SettingsConst::directoryMemory);
        if ( QDir(line).exists()) //se la directory non esiste il programma crasha
        {
            ui->directory->setText(line);
        }
    }
    ui->contenutoCartella->aggiornaLista(ui->directory->text());


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
    ui->tolleranza->setValue(Settings::getSettingsInt(SettingsConst::tolleranza));
    ui->confrontoBianco->setValue(Settings::getSettingsInt(SettingsConst::confrontoBianco));
    ui->latoMinMD->setValue(Settings::getSettingsInt(SettingsConst::latoMinMD));
    ui->dimMinFileSpinBox->setValue(Settings::getSettingsInt(SettingsConst::dimMinFileSpinBox));

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

    //Aggiorno i crediti rimanenti quando apro l'applicazione
    chiamataCreditiRemoveBg();

}

//Distruttore
MainWindow::~MainWindow()
{
    delete ui;
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

    //Creo una lista di file
    QDir dir(ui->directory->text());
    QList<QFileInfo> fileList = dir.entryInfoList();

    //Conto le immagini inviabili a remove bg
    int numeroImmagini = 0;
    for ( int i=0 ; i < fileList.size() ; i++ )
    {
        QImageReader image (fileList.at(i).absoluteFilePath());
        if ((image.format() == "jpeg" || image.format() == "png") && ui->contenutoCartella->item( i , 0 )->checkState() == Qt::Checked)
        {
            numeroImmagini++;
        }
    }

    //Chiedo conferma prima di inviare i file a removebg
    QMessageBox confermaInvio;
    QString valueNumbers = QString::number(numeroImmagini);
    if (numeroImmagini != 0)
    {
        confermaInvio.setText("Sei sicuro di voler inviare a removebg " + valueNumbers + " immagine/i?          ");
        confermaInvio.addButton("Si" , QMessageBox::YesRole);
        confermaInvio.addButton("No" , QMessageBox::NoRole);
        int ret = confermaInvio.exec();
        if ( ret == 0)
        {
            //Creo la cartella originali se non esiste
            if (! QDir(ui->directory->text() + "/originali").exists())
            {
                QDir().mkpath(ui->directory->text() + "/originali" );
            }

            //Creo la cartella temporanea di appoggio dei file
            if (! QDir(ui->directory->text() + "/temp").exists())
            {
                QDir().mkpath(ui->directory->text() + "/temp" );
            }

            QProgressDialog progress("Invio foto a removebg..." , "Annulla" , 0 , fileList.size() , this);
            progress.setWindowModality(Qt::WindowModal);
            progress.setMinimumDuration(200);

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
                    format.setBody(ui->fileOutputRemoveBG->currentText().toUtf8());

                    QHttpPart size;
                    size.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"size\""));
                    size.setBody(Settings::getSettingsString(SettingsConst::removeBgImageSize).toUtf8());

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

                    QNetworkRequest request;
                    request.setUrl(QUrl(Settings::getSettingsString(SettingsConst::urlRemoveBG)));
                    request.setRawHeader("X-Api-Key", Settings::getSettingsString(SettingsConst::apiKeyRemoveBG).toUtf8());


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
    QFileInfo fileInfo(absoluthFilePath);

    QByteArray data (reply->readAll());
    qDebug () << reply;

    //Sposto i file nella cartella "originali" se non ci sono errori
    if (reply->error() == 0)
    {
        QFile::rename(absoluthFilePath  , ui->directory->text() + "/originali/" +fileInfo.fileName());
    }




    if (ui->fileOutputRemoveBG->currentText().toUtf8() == "zip")
    {
        QFile file (ui->directory->text() + "/" + fileInfo.completeBaseName() +"." + ui->fileOutputRemoveBG->currentText().toUtf8());
        file.open(QIODevice::WriteOnly);
        file.write(data);
        file.flush();
        file.close();
    }
    else
    {
        QPixmap img;
        img.loadFromData(data);
        img.save(ui->directory->text() + "/" + fileInfo.completeBaseName() +"." + ui->fileOutputRemoveBG->currentText().toUtf8() );
    }
    manager->disconnect();
    reply->deleteLater();
}

void MainWindow::chiamataCreditiRemoveBg()
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.remove.bg/v1.0/account"));
    request.setRawHeader("X-Api-Key", Settings::getSettingsString(SettingsConst::apiKeyRemoveBG).toUtf8());

    connect(managerCrediti, &QNetworkAccessManager::finished, this, &MainWindow::rispostaCreditiRemoveBg);
    managerCrediti->get(request);

}

void MainWindow::rispostaCreditiRemoveBg(QNetworkReply *reply)
{

    qDebug () << reply;
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
    ui->latoMinMD->setValue( 600);
    ui->dimMinFileSpinBox->setValue(500);
}

//------------------------------------------------------------------------------------------------------------------------------------------------//
//
//                                          Modifica l'immagine riquadrandola o salvandola in jpeg in base alle spunte inserite
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
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(200);

    for ( int i=0 ; i < fileList.size() ; i++ )
    {
        progress.setValue(i);
        if (progress.wasCanceled())
        {
            break;
        }

        QImageReader imageReader (fileList.at(i).absoluteFilePath());

        if ( imageReader.canRead() && ui->contenutoCartella->item( i , 0 )->checkState() == Qt::Checked)
        {
            Logger::addLog("File name: " + fileList.at(i).absoluteFilePath() );

            QString imageOutputFormat(Settings::getSettingsString(SettingsConst::imageOutputFormat));

            ImageProcessor image (fileList.at(i).absoluteFilePath(), imageOutputFormat);

            image.fixOrientationImage();

            image.saveImage(qApp->applicationDirPath() + "/backup/" + fileList.at(i).fileName(), 100);

            if (ui->changeImageFormat->isChecked())
            {
                Logger::addLog("'Trasforma' is checked");
                image.modifyImageFormat();
            }

            else if (ui->centraRiquadra->isChecked())
            {
                Logger::addLog("'Centra e Riquadra' is checked");

                image.centerImage(ui->tolleranza->value(),
                                  Settings::getSettingsInt(SettingsConst::ratioHeight),
                                  Settings::getSettingsInt(SettingsConst::ratioWidth),
                                  Settings::getSettingsInt(SettingsConst::percAumento));

                // Controlla se il lato è minore o maggiore del valore dello spinbox e ridimensiona la foto
                if (Settings::getSettingsBool(SettingsConst::ridimensionaMin))
                {
                    image.scaledNewImageToMin(Settings::getSettingsInt(SettingsConst::latoMin));
                }
                if (Settings::getSettingsBool(SettingsConst::ridimensionaMax))
                {
                    image.scaledNewImageToMax(Settings::getSettingsInt(SettingsConst::latoMax));
                }
            }

            //Assegno un nuovo file per poterlo eliminare
            imageReader.setFileName("");

            //Elimino il file precedente
            if (QFile::remove(fileList.at(i).absoluteFilePath()))
            {
                 Logger::addLog("Delete the first file: " + fileList.at(i).absoluteFilePath());
            }
            else
            {
                Logger::addLog("Unable to delete the first file: " + fileList.at(i).absoluteFilePath());
            }

            //Salva l'immagine in base alla qualità se il checkbox è spuntato e in base al formato di output scelto
            QString newFilename(ui->directory->text() + "/" + fileList.at(i).completeBaseName() + "." + imageOutputFormat);
            if (Settings::getSettingsBool(SettingsConst::trasformaQualita))
            {
                Logger::addLog("Save image in " + imageOutputFormat + " format with quality: " + QString::number(Settings::getSettingsInt(SettingsConst::qualitaSalvataggio)));
                image.saveNewImage(newFilename, Settings::getSettingsInt(SettingsConst::qualitaSalvataggio));
            }
            else
            {
                Logger::addLog("Save image in " + imageOutputFormat + " format with quality: 100");
                image.saveNewImage(newFilename);
            }
            QFile newFile(newFilename);
            ui->contenutoCartella->aggiornaSingoloFile(QFileInfo(newFile) , image.getNewImage() , i );
        }
    }
    ui->contenutoCartella->tableResize();
}

//-------------------------------------------------------------------------------------------------------------//
//                                         Overrided methods
//-------------------------------------------------------------------------------------------------------------//
void MainWindow::closeEvent(QCloseEvent *)
{
    Settings::setSettings(SettingsConst::tolleranza, ui->tolleranza->value());
    Settings::setSettings(SettingsConst::confrontoBianco, ui->confrontoBianco->value());
    Settings::setSettings(SettingsConst::latoMinMD, ui->latoMinMD->value());
    Settings::setSettings(SettingsConst::dimMinFileSpinBox, ui->dimMinFileSpinBox->value());

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeWindow->setWidthHeightIncrement(event , this);

    //Muove solo Y
    resizeWindow->moveWidgetY(ui->centraRiquadra);
    resizeWindow->moveWidgetY(ui->tolleranza);
    resizeWindow->moveWidgetY(ui->label_4);
    resizeWindow->moveWidgetY(ui->trasformaImmagini);
    resizeWindow->moveWidgetY(ui->trasformaImmaginiBox);
    resizeWindow->moveWidgetY(ui->changeImageFormat);

    resizeWindow->moveWidgetY(ui->label_5);
    resizeWindow->moveWidgetY(ui->refreshCrediti);
    resizeWindow->moveWidgetY(ui->creditiRimanenti);
    resizeWindow->moveWidgetY(ui->fileOutputRemoveBG);
    resizeWindow->moveWidgetY(ui->removeBg);
    resizeWindow->moveWidgetY(ui->trasformaImmaginiBox_2);

    //Muove solo X
    resizeWindow->moveWidgetY(ui->selezionaDeseleziona);
    resizeWindow->moveWidgetX(ui->indietroDirectory);
    resizeWindow->moveWidgetX(ui->scegliCartella);
    resizeWindow->moveWidgetX(ui->backupFolder);
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
    resizeWindow->setObjectGeometry(ui->backupFolder);
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
    resizeWindow->setObjectGeometry(ui->fileOutputRemoveBG);
    resizeWindow->setObjectGeometry(ui->removeBg);
    resizeWindow->setObjectGeometry(ui->trasformaImmaginiBox_2);

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
    QString line = Settings::getSettingsString(SettingsConst::directoryMemory);
    QString filename = QFileDialog::getExistingDirectory(this, "Scegli Cartella" , line);
    if (line != filename && filename != "")
    {
        Settings::setSettings(SettingsConst::directoryMemory, filename);
    }
    if (filename.isEmpty())
        return;
    ui->directory->setText(filename);
    ui->contenutoCartella->aggiornaLista(ui->directory->text());
}

//--------------------------------------------------------------------------------------------------------------//
//                                                          Apre la cartella di backup
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_backupFolder_clicked()
{

    QDesktopServices::openUrl(QUrl::fromLocalFile(qApp->applicationDirPath() + "/backup"));
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

    QString directory = ui->directory->text();
    directory.truncate(directory.lastIndexOf(QChar('/')));
    ui->directory->setText(directory);
    ui->contenutoCartella->aggiornaLista(ui->directory->text());
    Settings::setSettings(SettingsConst::directoryMemory, directory);
}

//--------------------------------------------------------------------------------------------------------------//
//                                                  Naviga tra le cartelle con doppio click
//--------------------------------------------------------------------------------------------------------------//

void MainWindow::on_contenutoCartella_itemDoubleClicked(QTableWidgetItem *item)
{
    QString directory = item->text();
    QFile file (directory);
    QFileInfo fileInfo (file);
    if (fileInfo.isDir())
    {
        ui->directory->setText(directory);
        ui->contenutoCartella->aggiornaLista(ui->directory->text());
        Settings::setSettings(SettingsConst::directoryMemory, directory);
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


