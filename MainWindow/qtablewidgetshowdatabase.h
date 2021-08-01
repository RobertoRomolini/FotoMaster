#ifndef QTABLEWIDGETSHOWDATABASE_H
#define QTABLEWIDGETSHOWDATABASE_H

#include <QTableWidget>
#include <QWidget>

class QTableWidgetShowDatabase : public QTableWidget
{
    Q_OBJECT
public:
    explicit QTableWidgetShowDatabase(QWidget *parent = 0);

    //Stampa la tabella
    void vediAnteprima(QString fileCSV);

    //Pulizia tabella quando il cursore esce dal pulsante "sostituisci"
    void clearTable();



private:





};

#endif // QTABLEWIDGETSHOWDATABASE_H
