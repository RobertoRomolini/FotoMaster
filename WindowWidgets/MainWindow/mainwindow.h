#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "WindowWidgets/ModificaDati/modificadati.h"
#include "WindowWidgets/EditorFoto/editorfoto.h"
#include "Tools/qimgorient.h"
#include "WindowWidgets/Settings/optionsWidget.h"
#include "WindowWidgets/Settings/settings.h"
#include "WindowWidgets/Settings/settingsconst.h"
#include "CustomWidgets/qmoveimagepushbutton.h"
#include <Tools/imageprocessor.h>
#include "Tools/logger.h"
#include "Tools/resizewindow.h"
#include <QCoreApplication>
#include <QtNetwork>
#include <QDebug>
#include <QDir>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Remove BG
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkAccessManager *managerCrediti = new QNetworkAccessManager(this);
    void chiamataRemoveBg ();
    void rispostaRemoveBg(QNetworkReply *reply , QString absoluthFilePath);
    void chiamataCreditiRemoveBg ();
    void rispostaCreditiRemoveBg(QNetworkReply *reply);


    // Sostituisci le parole dei nomi file come nel database
    void sostituisci(QString);
    void cancellaDatiFile (QString nomeFile);

    // Istanza pagina modifica dati database
    modificaDati *database = new modificaDati (this);

    // Istanza pagina opzioni
    Options *options = new Options (this);

    // Classe per trasformare finestra responsive
    ResizeWindow *resizeWindow = new ResizeWindow("MainWindow");

    // Salva la posizione degli elementi
    void setElementPosition();

    // Collega azioni del menu a tendina
    void restoreSettings();

    // Metodo per trasformare le immagini
    void trasformaImmagini(QString outputFormat, QFileInfo tempFile, int ratioHeight, int ratioWidth, int quality, QString hexColorBg = nullptr);

    // Controlla lato immagine
    ImageProcessor checkSideSize(ImageProcessor image);

private slots:
    //Azionano la sostituzione dei nomi dei file
    void on_annullaModifiche_clicked();
    void on_sostituisciRapido_clicked();

    //Modifica l'immagine riquadrandola o salvandola in jpog in base alle spunte inserite
    void on_trasformaImmagini_clicked();

    //Seleziona/Deselezione tutti checkbox all'interno della tabella
    void on_selezionaDeseleziona_stateChanged();

    //Seleziona/Deselezione tutte le opzioni della tabella
    void on_selezionaTutto_stateChanged(int state);

    //Naviga tra le cartelle con doppio click
    void on_contenutoCartella_itemDoubleClicked(QTableWidgetItem *item);

    //Naviga tra le directory e crea memoria con l'ultima cercata
    void on_scegliCartella_clicked();

    //Torna indietro alla cartella precedente
    void on_indietroDirectory_clicked();

    //Aggiorna la lista dei file
    void on_aggiorna_clicked();

    //Apre la cartella di backup
    void on_settingsButton_clicked();



    //Comunica alla tabella ogni cambiamento di stato dei checkbox
    void on_immaginiQuadrate_stateChanged(int state);
    void on_sfondoBianco_stateChanged(int state);
    void on_mostraImmagini_stateChanged(int state);
    void on_percentualeBianco_stateChanged(int state);
    void on_mostraDimensione_stateChanged(int state);
    void on_dimensioneFile_stateChanged(int state);
    void on_selezionaDeseleziona_stateChanged(int arg1);
    void on_latoMinMD_valueChanged(int arg1);
    void on_dimMinFileSpinBox_valueChanged(int arg1);
    void on_confrontoBianco_valueChanged(int arg1);

protected:
    //Metodi classe sovrascritti
    virtual void resizeEvent(QResizeEvent *);
    void closeEvent (QCloseEvent *);
};

#endif // MAINWINDOW_H
