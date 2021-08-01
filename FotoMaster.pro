QT       += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomWidgets/qcheckboxcustom.cpp \
    CustomWidgets/qeditorpushbutton.cpp \
    CustomWidgets/qmoveimagepushbutton.cpp \
    CustomWidgets/qpushbuttonblue.cpp \
    CustomWidgets/qpushbuttongreen.cpp \
    CustomWidgets/qpushbuttonred.cpp \
    MainWindow/EditorFoto/editorfoto.cpp \
    MainWindow/EditorFoto/qgraphicsscenecustom.cpp \
    MainWindow/EditorFoto/qgraphicsviewcustom.cpp \
    MainWindow/ModificaDati/modificadati.cpp \
    MainWindow/mainwindow.cpp \
    MainWindow/options.cpp \
    MainWindow/qtablewidgetfilelist.cpp \
    MainWindow/qtablewidgetshowdatabase.cpp \
    MainWindow/resizewindow.cpp \
    Tools/qimgorient.cpp \
    main.cpp \



HEADERS += \
    CustomWidgets/qcheckboxcustom.h \
    CustomWidgets/qeditorpushbutton.h \
    CustomWidgets/qmoveimagepushbutton.h \
    CustomWidgets/qpushbuttonblue.h \
    CustomWidgets/qpushbuttongreen.h \
    CustomWidgets/qpushbuttonred.h \
    MainWindow/EditorFoto/editorfoto.h \
    MainWindow/EditorFoto/qgraphicsscenecustom.h \
    MainWindow/EditorFoto/qgraphicsviewcustom.h \
    MainWindow/ModificaDati/modificadati.h \
    MainWindow/mainwindow.h \
    MainWindow/options.h \
    MainWindow/qtablewidgetfilelist.h \
    MainWindow/qtablewidgetshowdatabase.h \
    MainWindow/resizewindow.h \
    Tools/qimgorient.h \



FORMS += \
    MainWindow/EditorFoto/editorfoto.ui \
    MainWindow/ModificaDati/modificadati.ui \
    MainWindow/mainwindow.ui \
    MainWindow/options.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MyResources.qrc

RC_FILE = myapp.rc

LIBS += -lGdiplus


DISTFILES +=
