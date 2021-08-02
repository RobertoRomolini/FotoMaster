#ifndef EDITORFOTO_H
#define EDITORFOTO_H
#include <QMainWindow>
#include <QCoreApplication>
#include <Tools/resizewindow.h>
#include "qgraphicsscenecustom.h"
#include "qgraphicsviewcustom.h"
#include "CustomWidgets/qeditorpushbutton.h"


QT_BEGIN_NAMESPACE
namespace Ui { class EditorFoto; }
QT_END_NAMESPACE

class EditorFoto : public QMainWindow
{
    Q_OBJECT

public:
    EditorFoto(QWidget *parent = nullptr);
    ~EditorFoto();
    void changeLabel(QString labelText , QString toolTip);

protected:
    virtual void resizeEvent(QResizeEvent *);
    void closeEvent (QCloseEvent *event);

public slots:
    void restoreCursor();

signals:
    void closeWindow();

private:
    Ui::EditorFoto *ui;
    void showImage ();
    void activeOption ();
    void zoomIn ();
    void zoomOut();
    void changeCursorEnter ();
    void actionLeftButtonReleased();
    void actionLeftButtonMove();
    void actionLeftButtonClick();
    void uncheckAllButtons();
    void updateEraserSize ();
    void updateEraserAltRightButton ();
    void actionRightButtonClick();
    void save();
    void undo();
    void createOptionsCommands();
    void restoreImageClick();
    void restoreImageMove();
    void actionShiftLeftButtonClick();
    void createConnectionSignal ();

    //Classe per trasformare finestra responsive
    ResizeWindow *resizeWindow = new ResizeWindow("EditorFoto");


    QGraphicsSceneCustom *scene = new QGraphicsSceneCustom;

    //_Eraser Commands
    int startDimensionResize;
    QDoubleSpinBox *eraserSpinBox;
    QEditorPushButton *gradientButton;
    QDoubleSpinBox *gradientSpinBox;

    //_Broom Commands
    QLabel *broomLabelDescription;
    QLabel *broomLabelStartColor;
    QLabel *broomLabelDescription2;
    QPushButton *broomColorButton;
    QEditorPushButton *broomTransformationButton;
    QSpinBox *broomToleranceSpinBox;
    void chooseColorDialog();
    void broomChangePixelColor();
};

#endif // EDITORFOTO_H
