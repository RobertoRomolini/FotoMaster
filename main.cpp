#include "WindowWidgets/MainWindow/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("FotoMaster");
    QApplication::setApplicationName("settings");
    MainWindow w;
    w.show();
    return a.exec();
}
