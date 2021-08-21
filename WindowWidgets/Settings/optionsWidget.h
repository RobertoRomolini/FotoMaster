#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QDialog>
#include <QSettings>
#include <QCoreApplication>
#include <QFileDialog>
#include <WindowWidgets/Settings/settingsconst.h>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);
    ~Options();

private slots:
    void on_chooseDirectory_clicked();
    void on_deleteDirectory_clicked();
    void on_saveSettings_clicked();
    void on_reset_settings_clicked();

private:
    Ui::Options *ui;
};

#endif // OPTIONSWIDGET_H
