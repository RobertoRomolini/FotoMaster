#ifndef QGRAPHICSSCENECUSTOM_H
#define QGRAPHICSSCENECUSTOM_H

#include <QtWidgets>

class QGraphicsSceneCustom : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QGraphicsSceneCustom(QWidget *parent = 0);
    QGraphicsPixmapItem *pixmapItem;
    QPointF mousePosPress;
    QPointF oldMousePos;
    QPointF mousePosMove;
    QPointF oldMousePosMove;
    QPointF scrollPos;
    QPointF mousePosMoveLastScene;
    QPointF mousePosPressShift;
    QPoint mouseScreenPosMove;
    QPoint mouseScreenPosPress;
    void eraserLine( double dimension);
    void eraserPoint( double dimension);
    void eraserLineGradient(double dimension , double gradient);
    void eraserPointGradient( double dimension , double gradient);
    void loadImage(QString fileName , int heightGraphicsView , QDoubleSpinBox *zoomPercentage);
    void save(QString fileName);
    void saveClose(QString fileName);
    void undo();
    void selectedPixelColor (QLabel *label);
    void changePixelColor(QColor colorFound , QColor colorRepleace , int tolerance);
    void restoreImageClick (double dimension);
    void restoreImageMove(double dimension);
    void eraserLinePointToPoint( double dimension);

    void saveImageUndo();
    void clearImageBackup();
    QImage getLastImageBackupImage();

protected:
    virtual bool event(QEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent  *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent  *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent  *event) override;

signals:
    void signalEnterMouse ();
    void signalLeaveMouse ();
    void leftButtonClick ();
    void rightButtonClick ();
    void leftButtonRelease ();
    void mouseLeftMoveSignal();
    void altRightButtonMoveSignal ();
    void altLeftButtonClick ();
    void altLeftButtonMoveSignal ();
    void shiftLeftButtonClick ();

private:
    QString fileName;
    QImage image;
    QPainter painter;
    bool isSaved;
    QList<QImage> backupImages;
};

#endif // QGRAPHICSSCENECUSTOM_H
