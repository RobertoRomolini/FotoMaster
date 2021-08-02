#include "MainWindow/EditorFoto/editorfoto.h"
#include "ui_editorfoto.h"
#include <QDebug>
#include <QResizeEvent>


EditorFoto::EditorFoto(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorFoto)
{
    ui->setupUi(this);

    createOptionsCommands();
    createConnectionSignal();


    //_Set Icon in push button_____________________//
    QIcon eraserIcon(":/Files/Files/eraser.png");
    ui->eraserButton->setIcon(eraserIcon);
    ui->eraserButton->setIconSize(QSize(17, 17));
    QIcon handMoveIcon(":/Files/Files/handMove.png");
    ui->handMoveButton ->setIcon(handMoveIcon);
    ui->handMoveButton->setIconSize(QSize(17, 17));
    QIcon broomIcon(":/Files/Files/broomIcon.png");
    ui->broomButton ->setIcon(broomIcon);
    ui->broomButton->setIconSize(QSize(17, 17));
    //_______________________________________//

    //_Set size widget to resize window_______________________________________//
    resizeWindow->setObjectGeometry(this);
    resizeWindow->setObjectGeometry(ui->graphicsView);
    resizeWindow->setObjectGeometry(ui->zoomPercentage);

    //_________________________________________________________________//

}

EditorFoto::~EditorFoto()
{
    delete ui;
}

void EditorFoto::closeEvent (QCloseEvent *)
{
    QDir dirTemporary (qApp->applicationDirPath() + "/temp/temporaryImage/");
    dirTemporary.removeRecursively();
    scene->saveClose(ui->nameImage->toolTip());
    scene->removeItem(scene->pixmapItem);
    scene->clear();

    emit closeWindow();
}

void EditorFoto::save()
{
    scene->save(ui->nameImage->toolTip());

}

void EditorFoto::undo()
{
    scene->undo();
}

//_Function to start the editor___________________________//
void EditorFoto::changeLabel(QString labelText , QString toolTip)
{
    ui->nameImage->setText(labelText);
    ui->nameImage->setToolTip(toolTip);
    ui->nameImage->adjustSize();
    QDir dirTemporary (qApp->applicationDirPath() + "/temp/temporaryImage/");
    if (!dirTemporary.exists())
    {
        dirTemporary.mkpath(qApp->applicationDirPath() + "/temp/temporaryImage/");
    }
    showImage();
}
//________________________________________________//

//_Broom actions________________________________________________________________________________________________//
void EditorFoto::chooseColorDialog()
{
    QColor color = QColorDialog::getColor(Qt::white,this , "Seleziona colore");
    broomColorButton->setStyleSheet("background-color:" + color.name(QColor::HexRgb) + ";border-radius:2px; border:1px solid #000000;");

}

void EditorFoto::broomChangePixelColor()
{
    if ( broomTransformationButton->isChecked() )
    {
        QColor colorFound = broomLabelStartColor->palette().color(QPalette::Base);
        QColor colorRepleace = broomColorButton->palette().color(QPalette::Base);
        scene->changePixelColor(colorFound,colorRepleace ,broomToleranceSpinBox->value() );
    }
}
//_____________________________________________________________________________________________________________//



//_Show image in graphicsScene_______________________________________________________________________________//
void EditorFoto::showImage()
{
    scene->loadImage(ui->nameImage->toolTip(), ui->graphicsView->height() , ui->zoomPercentage);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->sceneRect() , Qt::KeepAspectRatio);
}
//______________________________________________________________________________________________________//

//_Action buttons______________________________________________//
void EditorFoto::uncheckAllButtons()
{
   ui->handMoveButton->setChecked(false);
   ui->handMoveButton->setStyleSheet(ui->handMoveButton->neutralButton);
   ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
   ui->eraserButton->setChecked(false);
   ui->eraserButton->setStyleSheet(ui->eraserButton->neutralButton);
   ui->broomButton->setChecked(false);
   ui->broomButton->setStyleSheet(ui->broomButton->neutralButton);
}
//__________________________________________________________//

//_Restore cursor when mouse leave the QGraphicsScene________________//
void EditorFoto::restoreCursor()
{
    QApplication::restoreOverrideCursor();
}
//______________________________________________________//

//_Change cursor when enter in QGraphicsScene__________________________________________________________________________________//
void EditorFoto::changeCursorEnter()
{
    if (ui->handMoveButton->isChecked())
    {
        ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    }
    if (ui->eraserButton->isChecked())
    {
        updateEraserSize ();
    }
    if (ui->broomButton->isChecked())
    {
        QPixmap broomCursor = QPixmap (":/Files/Files/broomCursor.png").scaled( 18 , 18 , Qt::KeepAspectRatio );
        QApplication::setOverrideCursor(QCursor (broomCursor,0,0 ) );
    }
}
//_______________________________________________________________________________________________________________________//


//_Eraser____________________________________________________________________________________________________________//
void EditorFoto::updateEraserSize ()
{
    QApplication::restoreOverrideCursor();
    QPixmap pngTransparent = QPixmap (":/Files/Files/pngTransparent.png").scaledToHeight(eraserSpinBox->value() * ui->zoomPercentage->value()/100 *2);
    QPainter painter;
    painter.begin(&pngTransparent);
    painter.drawEllipse(pngTransparent.width()/4 ,pngTransparent.height()/4 , pngTransparent.width()/2 ,pngTransparent.height()/2);
    painter.end();
    QApplication::setOverrideCursor(QCursor (pngTransparent ));
}
void EditorFoto::updateEraserAltRightButton ()
{
    if (ui->eraserButton->isChecked())
    {
        eraserSpinBox->setValue(startDimensionResize +  (scene->mouseScreenPosMove.x() - scene->mouseScreenPosPress.x())*2.0  );
        updateEraserSize ();
    }
}

void EditorFoto::restoreImageClick()
{
    if (ui->eraserButton->isChecked())
    {
        scene->restoreImageClick(eraserSpinBox->value());
    }
}

void EditorFoto::restoreImageMove()
{
    if (ui->eraserButton->isChecked())
    {
        scene->restoreImageMove(eraserSpinBox->value());
    }
}

//________________________________________________________________________________________________________________________//

//_Action rightbutton____________________________________________________________________________________________________________________//
void EditorFoto::actionRightButtonClick()
{
    if (ui->eraserButton->isChecked())
    {
        startDimensionResize = eraserSpinBox->value();
    }

}
//_________________________________________________________________________________________________________________________________//

//_Action leftbutton____________________________________________________________________________________________________________________//
void EditorFoto::actionLeftButtonClick()
{
    if ( ui->eraserButton->isChecked())
    {
        if (gradientButton->isChecked())
        {
            scene->eraserPointGradient(eraserSpinBox->value(), gradientSpinBox->value());
        }
        else
        {
            scene->eraserPoint ( eraserSpinBox->value());
        }
    }
    if (ui->broomButton->isChecked())
    {
        scene->selectedPixelColor(broomLabelStartColor);
    }
}

void EditorFoto::actionLeftButtonMove()
{
    if (ui->eraserButton->isChecked() )
    {
        if (gradientButton->isChecked())
        {
            scene->eraserLineGradient(eraserSpinBox->value(), gradientSpinBox->value());
        }
        else
        {
            scene->eraserLine(eraserSpinBox->value());
        }
    }
    if (ui->broomButton->isChecked())
    {
        scene->selectedPixelColor(broomLabelStartColor);
    }
}

void EditorFoto::actionLeftButtonReleased()
{
    if(ui->eraserButton->isChecked())
    {
        scene->saveImageUndo();
    }
}
void EditorFoto::actionShiftLeftButtonClick()
{
    if (ui->eraserButton->isChecked())
    {
        scene->eraserLinePointToPoint( eraserSpinBox->value());
    }
}

//_________________________________________________________________________________________________________________________________//

//_Show options active icon_____________________________________________________________//
void EditorFoto::activeOption()
{
    ui->currentCommand->clear();
    if ( ui->handMoveButton->isChecked() )
    {

    }
    if ( ui->eraserButton->isChecked() )
    {
        QPixmap eraserIcon = QPixmap (":/Files/Files/eraser.png").scaled( 18 , 18 , Qt::KeepAspectRatio );
        ui->currentCommand->setPixmap(eraserIcon);
        ui->currentCommand->show();
        eraserSpinBox->show();
        gradientButton->show();
        gradientSpinBox->show();
    }
    else if ( !ui->eraserButton->isChecked() )
    {
        eraserSpinBox->hide();
        gradientButton->hide();
        gradientSpinBox->hide();
    }
    if (ui->broomButton->isChecked())
    {
        QPixmap broomIcon = QPixmap (":/Files/Files/broomIcon.png").scaled( 20 , 20 , Qt::KeepAspectRatio );
        ui->currentCommand->setPixmap(broomIcon);
        ui->currentCommand->show();
        broomLabelDescription->show();
        broomLabelStartColor->show();
        broomLabelDescription2->show();
        broomColorButton->show();
        broomTransformationButton->show();
        broomToleranceSpinBox->show();
    }
    else if (!ui->broomButton->isChecked())
    {
        broomLabelDescription->hide();
        broomLabelStartColor->hide();
        broomLabelDescription2->hide();
        broomColorButton->hide();
        broomTransformationButton->hide();
        broomToleranceSpinBox->hide();
    }
}

//_________________________________________________________________________________//

//_Zoom____________________________________________________________________________//
void EditorFoto::zoomIn()
{
    qDebug () << "ZoomIn";
    ui->graphicsView->scale( 1.05 , 1.05);
    ui->zoomPercentage->setValue( ui->zoomPercentage->value() * 1.05 );
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (ui->eraserButton->isChecked())
    {
        updateEraserSize();
    }
}

void EditorFoto::zoomOut()
{
    qDebug () << "ZoomOut";
    ui->graphicsView->scale( 0.95 , 0.95);
    ui->zoomPercentage->setValue( ui->zoomPercentage->value() * 0.95 );
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (ui->eraserButton->isChecked())
    {
        updateEraserSize();
    }
}
//___________________________________________________________________________________//

void EditorFoto::resizeEvent(QResizeEvent *event)
{
    resizeWindow->setWidthHeightIncrement(event , this);
    resizeWindow->resizeWidgetXY(ui->graphicsView);
    resizeWindow->moveWidgetY(ui->zoomPercentage);

}

void EditorFoto::createOptionsCommands()
{
    //_Eraser
    eraserSpinBox = new QDoubleSpinBox (this);
    eraserSpinBox->setGeometry(80,50,60,20);
    eraserSpinBox->setStyleSheet("background-color:#C3C3C3; border-radius:1px; border:1px solid #000000;" );
    eraserSpinBox->setMinimum(5);
    eraserSpinBox->setMaximum(2000);
    eraserSpinBox->setValue(100);
    eraserSpinBox->setSuffix(" px");
    eraserSpinBox->setDecimals(0);
    eraserSpinBox->hide();

    gradientButton = new QEditorPushButton (this);
    gradientButton->setGeometry(170 , 50 , 20 , 20);
    QIcon gradientIcon(":/Files/Files/gradient.png");
    gradientButton->setIcon(gradientIcon);
    gradientButton->setIconSize(QSize(17, 17));
    gradientButton->hide();

    gradientSpinBox = new QDoubleSpinBox (this);
    gradientSpinBox->setGeometry(200,50,50,20);
    gradientSpinBox->setStyleSheet("background-color:#C3C3C3;border-radius:1px; border:1px solid #000000;");
    gradientSpinBox->setMinimum(0.01);
    gradientSpinBox->setMaximum(0.99);
    gradientSpinBox->setValue(0.6);
    gradientSpinBox->setToolTip("Seleziona durezza gomma");
    gradientSpinBox->setDecimals(2);
    gradientSpinBox->setSingleStep(0.05);
    gradientSpinBox->hide();

    //_Broom
    broomLabelDescription = new QLabel (this);
    broomLabelDescription->setGeometry(80,50,100,20);
    broomLabelDescription->setText("Colore selezionato:");
    broomLabelDescription->setAlignment(Qt::AlignVCenter);
    broomLabelDescription->hide();

    broomLabelStartColor = new QLabel (this);
    broomLabelStartColor->setGeometry(180,50,20,20);
    broomLabelStartColor->setStyleSheet("border-radius:2px; border:1px solid #ffffff;");
    broomLabelStartColor->hide();

    broomLabelDescription2 = new QLabel (this);
    broomLabelDescription2->setGeometry(210,50,100,20);
    broomLabelDescription2->setText("Trasforma in:");
    broomLabelDescription2->setAlignment(Qt::AlignVCenter);
    broomLabelDescription2->hide();

    broomColorButton = new QPushButton (this);
    broomColorButton->setGeometry(280,50,20,20);
    broomColorButton->setStyleSheet("background-color:#FFFFFF; border-radius:2px; border:1px solid #000000;");
    broomColorButton->hide();
    connect ( broomColorButton , &QPushButton::clicked , this , &EditorFoto::chooseColorDialog );

    broomTransformationButton = new QEditorPushButton (this);
    broomTransformationButton->setGeometry(310,50,60,20);
    broomTransformationButton->setText("Trasforma");
    broomTransformationButton->hide();
    connect ( broomTransformationButton , &QEditorPushButton::buttonStateChangedSignal , this , &EditorFoto::broomChangePixelColor );

    broomToleranceSpinBox = new QSpinBox (this);
    broomToleranceSpinBox->setGeometry(380,50,40,20);
    broomToleranceSpinBox->setStyleSheet("background-color:#C3C3C3; border-radius:1px; border:1px solid #000000;" );
    broomToleranceSpinBox->setMinimum(0);
    broomToleranceSpinBox->setMaximum(255);
    broomToleranceSpinBox->setValue(10);
    broomToleranceSpinBox->setSingleStep(1);
    broomToleranceSpinBox->hide();
    connect(broomToleranceSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),[this](){broomChangePixelColor();});
    connect ( scene , &QGraphicsSceneCustom::leftButtonClick , this , &EditorFoto::broomChangePixelColor );

}

void EditorFoto::createConnectionSignal()
{
    //_Connect signals enter in the QGraphicsSceneCustom_____________________________________//
    connect ( scene , &QGraphicsSceneCustom::signalEnterMouse , this , &EditorFoto::changeCursorEnter );
    connect ( scene , &QGraphicsSceneCustom::signalLeaveMouse , this , &EditorFoto::restoreCursor );
    connect ( scene , &QGraphicsSceneCustom::leftButtonClick , this , &EditorFoto::actionLeftButtonClick );
    connect ( scene , &QGraphicsSceneCustom::rightButtonClick , this , &EditorFoto::actionRightButtonClick );
    connect ( scene , &QGraphicsSceneCustom::mouseLeftMoveSignal , this , &EditorFoto::actionLeftButtonMove );
    connect ( scene , &QGraphicsSceneCustom::leftButtonRelease , this , &EditorFoto::actionLeftButtonReleased );
    connect ( scene , &QGraphicsSceneCustom::altRightButtonMoveSignal , this , &EditorFoto::updateEraserAltRightButton );
    connect ( scene , &QGraphicsSceneCustom::altLeftButtonMoveSignal , this , &EditorFoto::restoreImageMove );
    connect ( scene , &QGraphicsSceneCustom::altLeftButtonClick , this , &EditorFoto::restoreImageClick );
    connect ( scene , &QGraphicsSceneCustom::shiftLeftButtonClick , this , &EditorFoto::actionShiftLeftButtonClick );
    connect ( ui->graphicsView , &QGraphicsViewCustom::altScrollUpSignal , this , &EditorFoto::zoomIn );
    connect ( ui->graphicsView , &QGraphicsViewCustom::altScrollDownSignal , this , &EditorFoto::zoomOut );
    //______________________________________________________________________________//

    //_Connect signals editButton___________________________________________________________________//
    connect ( ui->handMoveButton , &QEditorPushButton::buttonActiveSignal , this , &EditorFoto::uncheckAllButtons );
    connect ( ui->eraserButton , &QEditorPushButton::buttonActiveSignal , this , &EditorFoto::uncheckAllButtons );
    connect ( ui->broomButton , &QEditorPushButton::buttonActiveSignal , this , &EditorFoto::uncheckAllButtons );

    connect ( ui->eraserButton , &QEditorPushButton::buttonStateChangedSignal , this , &EditorFoto::activeOption );
    connect ( ui->handMoveButton , &QEditorPushButton::buttonStateChangedSignal , this , &EditorFoto::activeOption );
    connect ( ui->broomButton , &QEditorPushButton::buttonStateChangedSignal , this , &EditorFoto::activeOption );
    //__________________________________________________________________________________________//

    //_Connect signals from QMenu_________________________________________________//
    connect ( ui->actionEsci , &QAction::triggered , this, &EditorFoto::close  );
    connect ( ui->actionSalva , &QAction::triggered , this, &EditorFoto::save  );
    connect ( ui->actionZoomAvanti  , &QAction::triggered , this, &EditorFoto::zoomIn  );
    connect ( ui->actionZoomIndietro  , &QAction::triggered , this, &EditorFoto::zoomOut  );
    connect ( ui->actionAnnulla  , &QAction::triggered , this, &EditorFoto::undo  );
    //________________________________________________________________________//

}

