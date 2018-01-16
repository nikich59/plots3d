#-------------------------------------------------
#
# Project created by QtCreator 2016-03-17T23:02:34
#
#-------------------------------------------------

QT       += core gui
QT += opengl
QMAKE_CXXFLAGS += -std=c++11
LIBS += -lopengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene3d.cpp \
    scene3dxyz.cpp \
    scene3dpolar.cpp \
    scene3dcomplex.cpp \
    settingsdialogxyz.cpp \
    settingswidgetcommon.cpp \
    argumentsdialog.cpp \
    settingscomplexdialog.cpp \
    settingsdialogpolar.cpp \
    scene3drectangular.cpp

HEADERS  += mainwindow.h \
    scene3d.h \
    qoperation.h \
    scene3dxyz.h \
    mathexpression.h \
    scene3dpolar.h \
    scene3dcomplex.h \
    settingsdialogxyz.h \
    settingswidgetcommon.h \
    argumentsdialog.h \
    settingscomplexdialog.h \
    settingsdialogpolar.h \
    scene3drectangular.h

FORMS    += mainwindow.ui \
    settingsdialogxyz.ui \
    settingswidgetcommon.ui \
    argumentsdialog.ui \
    settingscomplexdialog.ui \
    settingsdialogpolar.ui

RESOURCES += \
    resource.qrc
