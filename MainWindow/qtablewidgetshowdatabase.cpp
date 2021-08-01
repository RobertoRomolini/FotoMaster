#include "qtablewidgetshowdatabase.h"

#include <QFile>
#include <QTextStream>

QTableWidgetShowDatabase::QTableWidgetShowDatabase(QWidget *parent) : QTableWidget(parent)
{

}

void QTableWidgetShowDatabase::vediAnteprima (QString fileCSV)
{
    int a=0;
    int lineCount=0;
    QFile file(fileCSV);
    file.open(QFile::ReadWrite | QFile::Text);
    clear();
    setRowCount(0);
    QFont fnt;
    fnt.setPointSize(12);
    QTableWidgetItem *firtsHeader = new QTableWidgetItem ("Trovare:");
    QTableWidgetItem *secondHeader = new QTableWidgetItem ("Sostituire con:");
    firtsHeader->setFont(fnt);
    secondHeader->setFont(fnt);
    setHorizontalHeaderItem(0, firtsHeader);
    setHorizontalHeaderItem(1, secondHeader);
    QTextStream in(&file);
    while (!in.atEnd())
    {
        lineCount++;
        setRowCount(lineCount);
        QString line = in.readLine();
        QFont font;
        QString element1 = line.split(";").first();
        QString element2 = line.split(";").last();
        QTableWidgetItem *pCell1 = new QTableWidgetItem;
        pCell1->setText(element1);
        pCell1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        QTableWidgetItem *pCell2 = new QTableWidgetItem;
        pCell2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        pCell2->setText(element2);
        setItem(a,0,pCell1);
        setItem(a,1,pCell2);
        a++;
    }
    file.close();
}

void QTableWidgetShowDatabase::clearTable()
{
    clearContents();
    setRowCount(0);

}
