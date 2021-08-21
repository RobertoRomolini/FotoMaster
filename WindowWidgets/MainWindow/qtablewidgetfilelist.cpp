#include "qtablewidgetfilelist.h"

#include <CustomWidgets/qpushbuttongreen.h>
#include <CustomWidgets/qmoveimagepushbutton.h>
#include <CustomWidgets/qpushbuttonblue.h>

QTableWidgetFileList::QTableWidgetFileList(QWidget *parent) : QTableWidget(parent)
{
    //Crea connessione tra l'aggiornamento della riga e la chiusura dell'editor foto
    connect ( editor , &EditorFoto::closeWindow , this , &QTableWidgetFileList::refreshEdit);

    //Crea connessione con il tasto canc con l'eliminazione del file
    QShortcut *deleteItem = new QShortcut(QKeySequence("Del"), this);
    connect ( deleteItem , &QShortcut::activated , this , &QTableWidgetFileList::deleteFile);

    //Attiva il tracking del mouse per aprire l'anteprima
    setMouseTracking(true);

}

//--------------------------------------------------------------------------------------------------------------//
//
//                                  Metodi pubblici di aggiornamento tabella
//
//--------------------------------------------------------------------------------------------------------------//

void QTableWidgetFileList::aggiornaLista(QString directory)
{
    qDebug () << "Inizio a stampare la tabella della cartella: " << directory;
    this->mainDirectory = directory;
    clear();
    setRowCount(0);

    tableHeader();
    QDir dir(directory);
    QList<QFileInfo> fileList = dir.entryInfoList();

    QProgressDialog progress("Caricamento elementi..." , "Annulla" , 0 , fileList.size() , this);
    progress.setWindowTitle("FotoMaster");
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(200);

    for ( int i=0 ; i < fileList.size() ; i++ )
    {
        qDebug () << "Analizzo il file: " << fileList.at(i).fileName();

        progress.setValue(i);
        if (progress.wasCanceled())
        {
            break;
        }

        setRowHeight( i , 20 );
        setRowCount(fileList.size());

        tableCheckbox(fileList.at(i) , i , 0);
        tableEditButton(fileList.at(i) , i , 1);
        tableIcon(fileList.at(i),  i , 2);
        tableFileName(fileList.at(i) ,i, 3 );

        tableDimensioneImmagine(fileList.at(i) , i , dimColumn);

        tableImmaginiQuadrate(fileList.at(i) , i, quadColumn);

        tableDimensioneFile(fileList.at(i), i , fileDimColumn);

        if ((sfondoBianco || percentualeBianco || mostraImmagini))//Crea QImage solo se alcune checkbox sono spuntate, per aumentare la velocità di esecuzione
        {
            QImage image (fileList.at(i).absoluteFilePath() );

            tableMostraImmagini (fileList.at(i) , image, i, imageColumn);
            tableSfondoBianco(fileList.at(i) , image, i, sfondoBiaColumn);
            tablePercentualeBianco(fileList.at(i) , image , i , percenBiaColumn );
        }
    }
    tableResize();
}

void QTableWidgetFileList::aggiornaSingoloFile(QFileInfo file , QImage image , int row)
{
    tableEditButton(file , row , 1);
    tableIcon (file , row , 2);
    tableFileName (file , row , 3);
    tableDimensioneImmagine(file , row , dimColumn);
    tableImmaginiQuadrate(file , row, quadColumn);
    tableMostraImmagini (file , image, row, imageColumn);
    tableSfondoBianco(file , image, row, sfondoBiaColumn );
    tablePercentualeBianco(file , image , row , percenBiaColumn );
    tableDimensioneFile(file, row , fileDimColumn);
}

void QTableWidgetFileList::tableResize()
{
    resizeColumnsToContents();
    setColumnWidth( 3 , width() - columnWidth(0) - columnWidth(1) - columnWidth(2) - columnWidth(4) - columnWidth(5)
                    - columnWidth(6) - columnWidth(7) - columnWidth(8) - columnWidth(9) - 20);
}

//--------------------------------------------------------------------------------------------------------------//
//
//                                                       Controllo se la tabella è aggiornata
//
//--------------------------------------------------------------------------------------------------------------//

void QTableWidgetFileList::checkTableUpdate(QString directory)
{
    QDir dir(directory);
    QList<QFileInfo> fileList = dir.entryInfoList();


    if (rowCount() != fileList.size())
    {
        QMessageBox messageBox (QMessageBox::Warning , "Cartella non aggiornata" , "La cartella non è stata aggiornata prima del comando");

        QPushButton *updateButton =  messageBox.addButton("Aggiorna Tabella" , QMessageBox::AcceptRole);
        connect( updateButton , &QPushButton::clicked , this, [directory , this ]
        {
            aggiornaLista(directory);
        });
        messageBox.exec();
    }

}

//--------------------------------------------------------------------------------------------------------------//
//
//                                                       Metodi generazione tabella
//
//--------------------------------------------------------------------------------------------------------------//

void QTableWidgetFileList::tableHeader()
{
    setColumnCount(4);

    QTableWidgetItem *nomeCheckbox = new QTableWidgetItem ("",QTableWidgetItem::Type);
    setHorizontalHeaderItem(0 , nomeCheckbox );

    QTableWidgetItem *nomeButton = new QTableWidgetItem ("",QTableWidgetItem::Type);
    setHorizontalHeaderItem(1 , nomeButton );

    QTableWidgetItem *nomeIcona = new QTableWidgetItem ("",QTableWidgetItem::Type);
    setHorizontalHeaderItem(2 , nomeIcona );

    QTableWidgetItem *nomeFile = new QTableWidgetItem ("Nome File",QTableWidgetItem::Type);
    setHorizontalHeaderItem(3 , nomeFile );

    imageColumn = 0;
    if ( mostraImmagini )
    {
        setColumnCount(columnCount() +1 );
        QTableWidgetItem *mostraImmagine = new QTableWidgetItem ("Anteprima",QTableWidgetItem::Type);
        setHorizontalHeaderItem(columnCount()-1 , mostraImmagine );
        imageColumn = columnCount() - 1;
    }

    quadColumn = 0;
    if (immaginiQuadrate)
    {
        setColumnCount(columnCount() + 1 );
        QTableWidgetItem *nomeQuadrato = new QTableWidgetItem (QString ("Q"),QTableWidgetItem::Type);
        nomeQuadrato->setToolTip("Immagini Quadrate");
        setHorizontalHeaderItem(columnCount() - 1 ,nomeQuadrato );
        quadColumn = columnCount() - 1;
    }

    sfondoBiaColumn = 0;
    if (sfondoBianco)
    {
        setColumnCount(columnCount() + 1 );
        QTableWidgetItem *nomeBianco = new QTableWidgetItem (QString ("B"),QTableWidgetItem::Type);
        nomeBianco->setToolTip("Sfondo Bianco");
        setHorizontalHeaderItem(columnCount() - 1 ,nomeBianco );
        sfondoBiaColumn = columnCount() - 1;
    }

    percenBiaColumn = 0;
    if (percentualeBianco)
    {
        setColumnCount(columnCount() + 1 );
        QTableWidgetItem *percentualeBianco = new QTableWidgetItem (QString ("%B"),QTableWidgetItem::Type);
        percentualeBianco->setToolTip("% Sfondo Bianco");
        setHorizontalHeaderItem(columnCount() - 1 , percentualeBianco );
        percenBiaColumn = columnCount() - 1;
    }

    dimColumn = 0;
    if (mostraDimensione)
    {
        setColumnCount(columnCount() +1 );
        QTableWidgetItem *mostraDim = new QTableWidgetItem (QString ("Dim"),QTableWidgetItem::Type);
        setHorizontalHeaderItem(columnCount()-1 , mostraDim );
        mostraDim->setToolTip("Mostra Dimensione");
        dimColumn = columnCount() - 1;
    }

    fileDimColumn = 0;
    if (dimensioneFile)
    {
        setColumnCount(columnCount() +1 );
        QTableWidgetItem *mostraDimFile = new QTableWidgetItem (QString ("D. File"),QTableWidgetItem::Type);
        setHorizontalHeaderItem(columnCount()-1 , mostraDimFile );
        mostraDimFile->setToolTip("Mostra Dimensione File");
        fileDimColumn = columnCount() - 1;
    }

}

void QTableWidgetFileList::tableIcon(QFileInfo file, int row, int column)
{
    QFileIconProvider ip;
    QIcon icon = ip.icon(QFileInfo(file.absoluteFilePath()));
    QTableWidgetItem *iconItem = new QTableWidgetItem;
    iconItem->setIcon(icon);
    setItem( row , column , iconItem );
}

void QTableWidgetFileList::tableFileName(QFileInfo file, int row, int column)
{
    QFont font;
    font.setPointSize(10);
    if (file.isFile())
    {
        QTableWidgetItem *nameItem = new QTableWidgetItem (file.fileName());
        nameItem->setFont(font);
        setItem( row , column , nameItem );
    }
    else if (file.isDir() )
    {
        QTableWidgetItem *folderItem = new QTableWidgetItem (file.absoluteFilePath());
        folderItem->setFont(font);
        setItem( row , column , folderItem );
    }
    if (file.absoluteFilePath() == this->mainDirectory) //Cancella la stessa directory in cui ci troviamo
    {
        removeRow(row);
        hideRow(row);
    }
}



void QTableWidgetFileList::tableCheckbox(QFileInfo file , int row, int column)
{
    QImageReader imageReader (file.absoluteFilePath());
    if ( imageReader.canRead() )
    {
        QTableWidgetItem *checkboxItem = new QTableWidgetItem;
        if (selezionaDeseleziona)
        {
            checkboxItem->setCheckState(Qt::Checked);
        }
        else
        {
            checkboxItem->setCheckState(Qt::Unchecked);
        }
        setItem( row , column , checkboxItem );
    }
}

void QTableWidgetFileList::tableEditButton(QFileInfo file , int row, int column)
{
    QImageReader imageReader (file.absoluteFilePath());
    if ( imageReader.canRead() )
    {

        QPushButtonBlue *editButtonTable = new  QPushButtonBlue (this);
        QIcon editButtonEdit (":/Files/Files/editButton2.png");
        editButtonTable->setFixedSize( 16 , 16 );
        editButtonTable->setIconSize(QSize(13, 13));
        editButtonTable->setIcon(editButtonEdit);
        QWidget *editButtonWidget = new QWidget();
        QHBoxLayout *layoutEditButton = new QHBoxLayout(editButtonWidget);
        layoutEditButton->addWidget(editButtonTable);
        layoutEditButton->setAlignment(Qt::AlignCenter);
        layoutEditButton->setContentsMargins(0,0,0,0);
        setCellWidget( row , column , editButtonWidget );
        QString absoluthFileName (file.absoluteFilePath());
        QString fileName (file.fileName());
        connect(editButtonTable, &QPushButtonBlue::clicked, this, [ absoluthFileName , fileName, row , this ]
        {
            openEditor(absoluthFileName , fileName , row );
        });
        connect(editButtonTable, &QPushButtonBlue::signalEnterMouse, this, [ absoluthFileName , this ]
        {
            showImagePreview(absoluthFileName);
        });
        connect(editButtonTable, &QPushButtonBlue::signalLeaveMouse, [this] ()
        {
            hideImagePreview();
        });

    }

}

void QTableWidgetFileList::tableDimensioneImmagine(QFileInfo file , int row, int column)
{
    if (mostraDimensione)
    {
        QFont font;
        font.setPointSize(12);
        QImageReader imageReader (file.absoluteFilePath());
        if (imageReader.canRead())
        {
            QTableWidgetItem *dimImage = new QTableWidgetItem;
            QString width = QString::number(imageReader.size().width());
            QString height = QString::number(imageReader.size().height());
            dimImage->setText( width + "x" + height);
            dimImage->setFont(font);
            dimImage->setTextAlignment(Qt::AlignCenter);
            qDebug () << "La dimensionde dell'immagine è: " << imageReader.size().width() << "x" << imageReader.size().height();
            if (imageReader.size().width() >= latoMinMD && imageReader.size().height() >= latoMinMD)
            {
                dimImage->setForeground(green);
                qDebug () << "L'immagine è maggiore di: " << latoMinMD << "x" << latoMinMD;
            }
            else
            {
                dimImage->setForeground(red);
                qDebug () << "L'immagine è minore di: " << latoMinMD;
            }
            setItem( row , column , dimImage );
        }
    }
}

void QTableWidgetFileList::tableDimensioneFile(QFileInfo file , int row, int column)
{
    QImageReader imageReader (file.absoluteFilePath());
    if (dimensioneFile && imageReader.canRead())
    {
        QFont font;
        font.setPointSize(12);
        QTableWidgetItem *dimFile = new QTableWidgetItem;
        int size = file.size()/1000;
        QString sizeText = QString::number(size) + " Kb";
        dimFile->setText(sizeText);
        dimFile->setFont(font);
        dimFile->setTextAlignment(Qt::AlignCenter);
        qDebug () << "La dimensione del file è: " + sizeText;
        if (size <= dimMinFileSpinBox)
        {
            dimFile->setForeground(green);
        }
        else
        {
            dimFile->setForeground(red);
        }
        setItem( row , column , dimFile );
    }
}

void QTableWidgetFileList::tableImmaginiQuadrate(QFileInfo file  , int row, int column)
{
    if (immaginiQuadrate)
    {
        QFont font;
        font.setBold(true);
        font.setPointSize(12);
        QImageReader imageReader (file.absoluteFilePath());
        if ( imageReader.canRead() )
        {
            if (imageReader.size().width() == imageReader.size().height())
            {
                QTableWidgetItem *si =  new QTableWidgetItem;
                si->setText("Si");
                si->setTextAlignment(Qt::AlignCenter);
                si->setFont(font);
                si->setForeground(green);
                setItem( row , column , si );
                qDebug () << "L'immagine e' quadrata";
            }
            else
            {
                QTableWidgetItem *no =  new QTableWidgetItem;
                no->setText("No");
                no->setTextAlignment(Qt::AlignCenter);
                no->setFont(font);
                no->setForeground(red);
                setItem( row , column , no  );
                qDebug () << "L'immagine non e' quadrata";
            }
        }
    }
}

void QTableWidgetFileList::tableMostraImmagini (QFileInfo file , QImage image,  int row, int column)
{
    if (mostraImmagini && !image.isNull() && file.fileName() != ".." && file.fileName() != ".")
    {

        qDebug () << "Mostro l'immagine";
        setRowHeight( row , 100);
        QPixmap pix ( QPixmap::fromImage(image) );
        pix = pix.scaled(100 , 100 , Qt::KeepAspectRatio );
        QTableWidgetItem *imageItem = new QTableWidgetItem;
        imageItem->setData(Qt::DecorationRole , pix);
        setItem( row , column , imageItem );
    }
}

void QTableWidgetFileList::tableSfondoBianco(QFileInfo file , QImage image, int row, int column)
{
    if (sfondoBianco && !image.isNull() && file.fileName() != ".." && file.fileName() != ".")
    {
        qDebug () << "Controllo se i lati dell'immagine sono bianchi";
        setRowHeight( row , 100);
        QMoveImagePushButton *left = new QMoveImagePushButton (this);
        QMoveImagePushButton *top = new QMoveImagePushButton (this);
        QMoveImagePushButton *right = new QMoveImagePushButton (this);
        QMoveImagePushButton *down = new QMoveImagePushButton (this);
        QIcon leftIcon (":/Files/Files/left.png");
        left->setIcon(leftIcon);
        left->setIconSize(QSize(14, 14));
        left->setFixedSize(16,16);
        QIcon topIcon (":/Files/Files/up.png");
        top->setIcon(topIcon);
        top->setIconSize(QSize(14, 14));
        top->setFixedSize(16,16);
        QIcon rightIcon (":/Files/Files/right.png");
        right->setIcon(rightIcon);
        right->setIconSize(QSize(14, 14));
        right->setFixedSize(16,16);
        QIcon downIcon (":/Files/Files/down.png");
        down->setIcon(downIcon);
        down->setIconSize(QSize(14, 14));
        down->setFixedSize(16,16);

        QWidget *labelWidget = new QWidget();
        QVBoxLayout *verticalLayout = new QVBoxLayout(labelWidget);
        QHBoxLayout *horizontalLayout1 = new QHBoxLayout(labelWidget);
        QHBoxLayout *horizontalLayout2 = new QHBoxLayout(labelWidget);
        QHBoxLayout *horizontalLayout3 = new QHBoxLayout(labelWidget);

        QColor pixel;
        for ( int i=0 ; i<image.height() ; i++ ) // controllo lato sinistro
        {
            pixel =  image.pixelColor( 0 , i );
            if ( pixel != white && pixel.alphaF() > 0.02 )
            {
                left->setStyleSheet(left->redButton);
                left->checked = false;
                qDebug () << "Il lato sinistro non e' bianco";
                break;
            }
        }
        for ( int i=0 ; i<image.width() ; i++ ) // controllo lato superiore
        {
            pixel =  image.pixelColor( i , 0 );
            if ( pixel != white && pixel.alphaF() > 0.02)
            {
                top->setStyleSheet(top->redButton);
                top->checked = false;
                qDebug () << "Il lato superiore non e' bianco";
                break;
            }
        }
        for ( int i=0 ; i<image.height() ; i++ ) // controllo lato destro
        {
            pixel =  image.pixelColor( image.width()-1 , i );
            if ( pixel != white && pixel.alphaF() > 0.02)
            {
                right->setStyleSheet(right->redButton);
                right->checked = false;
                qDebug () << "Il lato destro non e' bianco";
                break;
            }
        }
        for ( int i=0 ; i<image.width() ; i++ ) // controllo lato inferiore
        {
            pixel =  image.pixelColor(  i , image.height()-1 );
            if ( pixel != white && pixel.alphaF() > 0.02)
            {
                down->setStyleSheet(down->redButton);
                down->checked = false;
                qDebug () << "Il lato sotto non e' bianco";
                break;
            }
        }
        int orientation;
        QString fileName (file.absoluteFilePath());
        orientation = 1;//left
        connect(left, &QMoveImagePushButton::clicked, this, [ fileName , row , orientation, this ]
        {
            moveImage( fileName , row , orientation);
        });
        orientation = 2;//top
        connect(top, &QMoveImagePushButton::clicked, this, [ fileName , row , orientation , this ]
        {
            moveImage( fileName , row , orientation);
        });
        orientation = 3;//right
        connect(right, &QMoveImagePushButton::clicked, this, [  fileName , row , orientation , this ]
        {
            moveImage( fileName , row , orientation);
        });
        orientation = 4;//bottom
        connect(down, &QMoveImagePushButton::clicked, this, [ fileName , row , orientation , this ]
        {
            moveImage( fileName , row , orientation );
        });


        horizontalLayout1->addWidget(top);
        horizontalLayout1->setAlignment(Qt::AlignCenter);
        horizontalLayout1->setContentsMargins(0,2,0,0);
        horizontalLayout2->addWidget(left);
        horizontalLayout2->addWidget(right);
        horizontalLayout2->setAlignment(Qt::AlignCenter);
        horizontalLayout2->setSpacing(20);
        horizontalLayout2->setContentsMargins(0,0,0,0);
        horizontalLayout3->addWidget(down);
        horizontalLayout3->setAlignment(Qt::AlignCenter);
        horizontalLayout3->setContentsMargins(0,0,0,2);
        verticalLayout->addLayout(horizontalLayout1);
        verticalLayout->addLayout(horizontalLayout2);
        verticalLayout->addLayout(horizontalLayout3);
        verticalLayout->setAlignment(Qt::AlignCenter);
        setCellWidget( row , column , labelWidget );
    }
}

void QTableWidgetFileList::tablePercentualeBianco(QFileInfo file , QImage image , int row , int column )
{
    if (percentualeBianco && !image.isNull() && file.fileName() != ".." && file.fileName() != ".")
    {
        QFont font;
        font.setBold(true);
        font.setPointSize(12);
        unsigned long int a=0;
        QColor pixel;
        for ( int i=0 ; i<image.width() ; i++ )
        {
            for ( int j=0 ; j<image.height() ; j++ )
            {
                pixel =  image.pixelColor(i,j);
                if (pixel == white)
                {
                    a++;
                }
            }
        }
        int percBianco =  100 * a / (image.width() * image.height());
        QTableWidgetItem *percWhite =  new QTableWidgetItem;
        QString text = QString::number(percBianco) + " %";
        percWhite->setText(text);
        percWhite->setTextAlignment(Qt::AlignCenter);
        percWhite->setFont(font);
        if (percBianco < confrontoBianco)
        {
            percWhite->setForeground(red);
        }
        else
        {
            percWhite->setForeground(green);
        }
        setItem( row , column , percWhite );
    }
}

//--------------------------------------------------------------------------------------------------------------//
//
//                                                                 Editor Foto
//
//--------------------------------------------------------------------------------------------------------------//

void QTableWidgetFileList::openEditor(QString absoluthfileName , QString fileName , int row)
{
    this->currentRow = row;
    editor->changeLabel(fileName, absoluthfileName);
    editor->setWindowModality(Qt::ApplicationModal);
    editor->show();
}

void QTableWidgetFileList::refreshEdit()
{
    QImage image (mainDirectory + "/" + item(currentRow , 3)->text());
    QFile file (mainDirectory + "/" + item(currentRow , 3)->text());
    aggiornaSingoloFile(QFileInfo(file) , image , currentRow);
}

//--------------------------------------------------------------------------------------------------------------//
//
//                                                        Elimina file tramite tasto canc
//
//--------------------------------------------------------------------------------------------------------------//

void QTableWidgetFileList::deleteFile()
{
    QModelIndexList indexes = selectionModel()->selectedRows();
    QMessageBox deleteConfirm;
    QString valueNumbers = QString::number(indexes.count());
    if (indexes.count() != 0)
    {
        deleteConfirm.setText("Sei sicuro di voler eliminare " + valueNumbers + " elementi/o selezionati/o?          ");
        deleteConfirm.addButton("Si" , QMessageBox::YesRole);
        deleteConfirm.addButton("No" , QMessageBox::NoRole);
        int ret = deleteConfirm.exec();
        if ( ret == 0)
        {
            for ( int i=0 ; i<indexes.count() ; i++ )
            {
                QString path (item( indexes.at(i).row() , 3 )->text());
                if ( !QFileInfo (path).isDir() )
                {
                    QString absoluthPathFile = this->mainDirectory + "/" + item( indexes.at(i).row() , 3 )->text();
                    QFile deleteImage (absoluthPathFile);
                    deleteImage.copy(qApp->applicationDirPath() + "/backup/" + item( indexes.at(i).row() , 3 )->text());
                    deleteImage.remove();
                }
                else
                {
                    QDir (path).removeRecursively();
                }

                //Elimino la riga una volta eliminato il file o la cartella
                hideRow(indexes.at(i).row() );
            }

        }
    }
}

//--------------------------------------------------------------------------------------------------------------//
//
//                                                   Mostra anteprima immagine
//
//--------------------------------------------------------------------------------------------------------------//

void QTableWidgetFileList::showImagePreview(QString absolutePath)
{

    QPixmap pixScaled = QPixmap ( absolutePath ).scaledToHeight(this->height()-4);
    this->imageLabel->setPixmap(pixScaled);
    this->imageLabel->setGeometry( this->width() -this->height()-4 , 2 , this->height()-20, this->height()-4 );
    this->imageLabel->setStyleSheet("background-color: #c3c3c3; border: 2px solid black; border-radius: 1px;");
    this->imageLabel->show();

}

void QTableWidgetFileList::hideImagePreview()
{
    this->imageLabel->clear();
    this->imageLabel->hide();
}

//--------------------------------------------------------------------------------------------------------------//
//
//                                     Metodo collegato ai pulsanti per spostare l'immagine
//
//--------------------------------------------------------------------------------------------------------------//

void QTableWidgetFileList::moveImage(QString fileName , int row , int orientation)
{
    QPainter painter;
    QImage newImage;
    QColor pixel;
    QImage image (fileName);
    QImageReader imageReader(fileName);

    if (orientation == 1)//left
    {
        int left = 0;
        for ( int i=0 ; i<image.width() ; i++ )
        {
            for ( int j=0 ; j<image.height(); j++ )
            {
                pixel =  image.pixelColor( i , j );
                if (pixel.red() <= 240 && pixel.green() <= 240 && pixel.blue() <= 240 && pixel.alphaF() > 0.02)
                {
                    left = i;
                    j=image.height();
                    i=image.width();
                }
            }
        }
        qDebug () << "Left: " << left;

        if (left != 0)
        {
            int newWidth = image.width() - left;
            QRect rect ( left , 0 , newWidth , image.height() );
            newImage = image.copy(rect);
        }
        else
        {           
            if (imageReader.format() == "jpeg")
            {
                newImage.load(":/Files/Files/whiteImage.jpg");
            }
            else
            {
                newImage.load(":/Files/Files/pngTransparent.png");
            }
            newImage = newImage.scaled(image.width()+20 , image.height() , Qt::IgnoreAspectRatio);
            painter.begin(&newImage);
            painter.drawImage( 20 , 0 , image );
        }
    }
    if (orientation == 2)//top
    {
        int top = 0;
        for ( int i=0 ; i<image.height() ; i++ )
        {
            for ( int j=0 ; j<image.width(); j++ )
            {
                pixel =  image.pixelColor( j , i );
                if (pixel.red() <= 240 && pixel.green() <= 240 && pixel.blue() <= 240 && pixel.alphaF() > 0.02)
                {
                    top = i;
                    j=image.width();
                    i=image.height();
                }
            }
        }
        if (top != 0)
        {
            int newHeight = image.height() - top;
            QRect rect ( 0 , top , image.width() , newHeight );
            newImage = image.copy(rect);
        }
        else
        {
            if (imageReader.format() == "jpeg")
            {
                newImage.load(":/Files/Files/whiteImage.jpg");
            }
            else
            {
                newImage.load(":/Files/Files/pngTransparent.png");
            }
            newImage = newImage.scaled(image.width() , image.height()+20 , Qt::IgnoreAspectRatio);
            painter.begin(&newImage);
            painter.drawImage( 0 , 20 , image );
        }
    }
    if (orientation == 3)//right
    {
        int right = 0;
        for ( int i=image.width()-1 ; i>0 ; i-- )
        {
            for ( int j=0 ; j<image.height(); j++ )
            {
                pixel =  image.pixelColor( i , j );
                if (pixel.red() <= 240 && pixel.green() <= 240 && pixel.blue() <= 240 && pixel.alphaF() > 0.02)
                {
                    right = image.width()- i -1;
                    j=image.height();
                    i=0;
                }
            }
        }
        qDebug () << "Right: " << right;
        if (right != 0)
        {
            int newWidth = image.width() - right;
            QRect rect ( 0 , 0 , newWidth , image.height() );
            newImage = image.copy(rect);
        }
        else
        {
            if (imageReader.format() == "jpeg")
            {
                newImage.load(":/Files/Files/whiteImage.jpg");
            }
            else
            {
                newImage.load(":/Files/Files/pngTransparent.png");
            }
            newImage = newImage.scaled(image.width()+20 , image.height() , Qt::IgnoreAspectRatio);
            painter.begin(&newImage);
            painter.drawImage( 0 , 0 , image );
        }
    }
    if (orientation == 4)//bottom
    {
        int down = 0;
        for ( int i=image.height()-1 ; i>0 ; i-- )
        {
            for ( int j=0 ; j<image.width(); j++ )
            {
                pixel =  image.pixelColor( j , i );
                if (pixel.red() <= 240 && pixel.green() <= 240 && pixel.blue() <= 240 && pixel.alphaF() > 0.02)
                {
                    down = image.height() - i -1;
                    j=image.width();
                    i=0;
                }
            }
        }
        qDebug () << "Down: " << down;
        if (down != 0)
        {
            int newHeight = image.height() - down;
            qDebug () << "newHeight: " << newHeight;
            QRect rect ( 0 , 0 , image.width() , newHeight );
            qDebug () << "Rect: " << rect;
            newImage = image.copy(rect);
        }
        else
        {
            if (imageReader.format() == "jpeg")
            {
                newImage.load(":/Files/Files/whiteImage.jpg");
            }
            else
            {
                newImage.load(":/Files/Files/pngTransparent.png");
            }
            newImage = newImage.scaled(image.width() , image.height()+20 , Qt::IgnoreAspectRatio);
            painter.begin(&newImage);
            painter.drawImage( 0 , 0 , image );
        }
    }

    painter.end();


    newImage.save(fileName , nullptr, 85);

    aggiornaSingoloFile(QFileInfo(fileName) , newImage , row);
    tableResize();

}

//--------------------------------------------------------------------------------------------------------------//
//
//                                      Drag and Drop dei file all'interno della cartella
//
//--------------------------------------------------------------------------------------------------------------//

void QTableWidgetFileList::dragEnterEvent(QDragEnterEvent *event)
{

    if (event->mimeData()->hasUrls())
    {
        event->accept();
        qDebug () << event;
    }
    else
    {
        event->ignore();
    }
}

void QTableWidgetFileList::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}


void QTableWidgetFileList::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->setDropAction(Qt::CopyAction);
        event->accept();

        QList<QUrl> urls = event->mimeData()->urls();

        QProgressDialog progress("Copio i file nella cartella..." , "Annulla" , 0 , urls.size() , this);
        progress.setWindowTitle("FotoMaster");
        progress.setWindowModality(Qt::WindowModal);
        progress.setMinimumDuration(1);
        for (int i=0; i< urls.size() ; i++ )
        {
            progress.setValue(i);
            if (progress.wasCanceled())
            {
                break;
            }
            QFile::copy(urls.at(i).toLocalFile() , mainDirectory + "/" + urls.at(i).fileName());
        }
        aggiornaLista(mainDirectory);
    }
}

//--------------------------------------------------------------------------------------------------------------//
//
//                                                             Getters and Setters
//
//--------------------------------------------------------------------------------------------------------------//

int QTableWidgetFileList::getCurrentRow() const
{
    return currentRow;
}

void QTableWidgetFileList::setCurrentRow(int value)
{
    this->currentRow = value;
}

void QTableWidgetFileList::setDimensioneFile(bool value)
{
    this->dimensioneFile = value;
}

void QTableWidgetFileList::setMostraDimensione(bool value)
{
    this->mostraDimensione = value;
}

void QTableWidgetFileList::setPercentualeBianco(bool value)
{
    this->percentualeBianco = value;
}

void QTableWidgetFileList::setSfondoBianco(bool value)
{
    this->sfondoBianco = value;
}

void QTableWidgetFileList::setImmaginiQuadrate(bool value)
{
    this->immaginiQuadrate = value;
}

void QTableWidgetFileList::setMostraImmagini(bool value)
{
    this->mostraImmagini = value;
}

void QTableWidgetFileList::setLatoMinMD(int value)
{
    this->latoMinMD = value;
}

void QTableWidgetFileList::setSelezionaDeseleziona(bool value)
{
    this->selezionaDeseleziona = value;
}

void QTableWidgetFileList::setConfrontoBianco(int value)
{
    this->confrontoBianco = value;
}

void QTableWidgetFileList::setDimMinFileSpinBox(int value)
{
    this->dimMinFileSpinBox = value;
}
