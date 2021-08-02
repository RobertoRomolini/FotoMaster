#include "MainWindow/ModificaDati/modificadati.h"
#include "ui_modificadati.h"
#include "MainWindow/mainwindow.h"
#include <QDebug>

modificaDati::modificaDati(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modificaDati)
{
    ui->setupUi(this);


}

modificaDati::~modificaDati()
{
    delete ui;
}

void modificaDati::changeLabel(QString databaseNameLabel , QString databaseFile)
{
    ui->labelTitolo->setText(databaseNameLabel);
    vediAnteprima(databaseFile , ui->anteprimaFile);
}

void modificaDati::vediAnteprima (QString fileCSV , QTableWidget *table)
{
    int a=0;
    int lineCount=0;
    QFile file(fileCSV);
    file.open(QFile::ReadOnly | QFile::Text);
    table->clear();
    table->setRowCount(0);
    QFont fnt;
    fnt.setPointSize(12);
    QTableWidgetItem *firtsHeader = new QTableWidgetItem ("Trovare:");
    QTableWidgetItem *secondHeader = new QTableWidgetItem ("Sostituire con:");
    firtsHeader->setFont(fnt);
    secondHeader->setFont(fnt);
    table->setHorizontalHeaderItem(0, firtsHeader);
    table->setHorizontalHeaderItem(1, secondHeader);
    QTextStream in(&file);
    while (!in.atEnd())
    {
        lineCount++;
        ui->anteprimaFile->setRowCount(lineCount);
        QString line = in.readLine();
        QFont font;
        QString element1 = line.split(";").at(0);
        QString element2 = line.split(";").at(1);
        QTableWidgetItem *pCell1 = new QTableWidgetItem;
        pCell1->setText(element1);
        pCell1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
        QTableWidgetItem *pCell2 = new QTableWidgetItem;
        pCell2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
        pCell2->setText(element2);
        table->setItem(a,0,pCell1);
        table->setItem(a,1,pCell2);
        a++;
    }
    file.close();
}

void modificaDati::changedsave(QString filePath)
{
    QFile oldFile( filePath );
    oldFile.remove();
    QFile file( filePath );
    file.open(QFile::WriteOnly | QFile::Text);
    for ( int i=0 ; i< ui->anteprimaFile->rowCount() ; i++  )
    {
        if ( !ui->anteprimaFile->item(i , 0)->text().isEmpty() )
        {
            if ( !ui->anteprimaFile->item(i , 0)->text().isEmpty() ||  !ui->anteprimaFile->item(i , 1)->text().isEmpty() )//delete rows both empty
            {
                QTextStream stream(&file);
                stream << ui->anteprimaFile->item(i , 0)->text() << ";" << ui->anteprimaFile->item(i , 1)->text() << Qt::endl;
            }
        }
    }
    file.close();
    this->close(); //close database window
}

void modificaDati::on_salvaModifiche_clicked()
{
    if ( ui->labelTitolo->text() == "Database 1")
    {
        changedsave (qApp->applicationDirPath() + "/temp/database1.csv");
    }
    else if ( ui->labelTitolo->text() == "Database 2" )
    {
        changedsave (qApp->applicationDirPath() + "/temp/database2.csv");
    }
    else if ( ui->labelTitolo->text() == "Database 3" )
    {
        changedsave (qApp->applicationDirPath() + "/temp/database3.csv");
    }
    else if ( ui->labelTitolo->text() == "Database 4" )
    {
        changedsave (qApp->applicationDirPath() + "/temp/database4.csv");
    }
    else if ( ui->labelTitolo->text() == "Database 5" )
    {
        changedsave (qApp->applicationDirPath() + "/temp/database5.csv");
    }
}

void modificaDati::on_aggiungiRiga_clicked()
{
    ui->anteprimaFile->insertRow(ui->anteprimaFile->rowCount());
    QTableWidgetItem *pCell1 = new QTableWidgetItem;
    QTableWidgetItem *pCell2 = new QTableWidgetItem;
    pCell1->setText(""); //if I don't put "" the program crash when save it
    pCell2->setText("");
    ui->anteprimaFile->setItem( ui->anteprimaFile->rowCount()-1 , 0 , pCell1 );
    ui->anteprimaFile->setItem( ui->anteprimaFile->rowCount()-1 , 1 , pCell2 );
}
