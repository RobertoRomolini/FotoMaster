#ifndef QTABLEWIDGETFILELIST_H
#define QTABLEWIDGETFILELIST_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QFileInfo>

#include <MainWindow/EditorFoto/editorfoto.h>

class QTableWidgetFileList : public QTableWidget
{
    Q_OBJECT
public:
    explicit QTableWidgetFileList(QWidget *parent = 0);

    //Metodi pubblici di aggiornamento tabella
    void aggiornaLista(QString directory);
    void aggiornaSingoloFile(QFileInfo file , QImage image , int row);
    void tableResize ();

    //Controllo se la tabella è agigornata
    void checkTableUpdate(QString directory);

    //Getters and Setters
    int getCurrentRow() const;
    void setCurrentRow(int value);
    void setMostraImmagini(bool value);
    void setImmaginiQuadrate(bool value);
    void setSfondoBianco(bool value);
    void setPercentualeBianco(bool value);
    void setMostraDimensione(bool value);
    void setDimensioneFile(bool value);
    void setSelezionaDeseleziona(bool value);
    void setLatoMinMD(int value);
    void setDimMinFileSpinBox(int value);
    void setConfrontoBianco(int value);


private:
    //Metodi generazione tabella
    void tableHeader ();
    void tableIcon (QFileInfo file , int row , int column);
    void tableFileName (QFileInfo file , int row , int column);
    void tableCheckbox (QFileInfo file , int row , int column);
    void tableEditButton (QFileInfo file , int row , int column);
    void tableDimensioneImmagine (QFileInfo file , int row, int column);
    void tableDimensioneFile ( QFileInfo file , int row, int column);
    void tableImmaginiQuadrate ( QFileInfo file , int row, int column);
    void tableMostraImmagini (QFileInfo file , QImage image, int row, int column);
    void tableSfondoBianco (QFileInfo file , QImage image, int row, int column);
    void tablePercentualeBianco (QFileInfo file , QImage image , int row, int column);

    //Colonne tabella
    int imageColumn;
    int quadColumn;
    int sfondoBiaColumn;
    int percenBiaColumn;
    int dimColumn;
    int fileDimColumn;

    //Riga attualmente in uso con l'editor
    int currentRow;
    QString mainDirectory;

    //Mostra anteprima immagine
    QLabel *imageLabel = new QLabel (this);
    void showImagePreview(QString absolutePath);
    void hideImagePreview();

    //Elementi da stampare nella tabella
    bool mostraImmagini = false;
    bool immaginiQuadrate = false;
    bool sfondoBianco = false;
    bool percentualeBianco = false;
    bool mostraDimensione = false;
    bool dimensioneFile = false;
    bool selezionaDeseleziona = true;
    int latoMinMD;
    int dimMinFileSpinBox;
    int confrontoBianco;

    //Elimina file tramite tasto canc
    void deleteFile();

    //Metodo collegato ai pulsanti per spostare l'immagine
    void moveImage (QString fileName , int row , int orientation);

    //Colori standard
    QColor white = QColor(255 , 255 , 255);
    QColor green = QColor(90 , 212 , 9);
    QColor red = QColor(251 , 54 , 45);

    //Editor Foto
    EditorFoto *editor = new EditorFoto (this);
    void openEditor(QString absoluthfileName , QString fileName , int currentRow);
    void refreshEdit();

protected:
    //Drag e Drop file nella tabella
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent  *event) override;

};

#endif // QTABLEWIDGETFILELIST_H
