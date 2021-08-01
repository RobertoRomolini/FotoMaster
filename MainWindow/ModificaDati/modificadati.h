#ifndef MODIFICADATI_H
#define MODIFICADATI_H
#include <QDialog>
#include <QTableWidget>

namespace Ui {
class modificaDati;
}

class modificaDati : public QDialog
{
    Q_OBJECT

public:
    explicit modificaDati(QWidget *parent = nullptr);
    ~modificaDati();
    void vediAnteprima(QString , QTableWidget*);
    void changedsave (QString);


public slots:
    void changeLabel(QString databaseNameLabel , QString databaseFile);

private slots:
    void on_salvaModifiche_clicked();
    void on_aggiungiRiga_clicked ();



private:
    Ui::modificaDati *ui;

};

#endif // MODIFICADATI_H
