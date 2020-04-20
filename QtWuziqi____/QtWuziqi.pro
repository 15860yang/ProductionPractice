#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T10:50:43
#
#-------------------------------------------------

QT       += core gui multimedia
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtWuziqi
TEMPLATE = app


SOURCES += main.cpp\
        Game.cpp \
        GameWindow.cpp \
        createroomconfigwindow.cpp \
        enterroomconfigwindow.cpp \
        remoteserviceutil.cpp \
        selectonlinebattletypewindow.cpp \
        snowmanwindow.cpp

HEADERS  += \
    Game.h \
    GameWindow.h \
    createroomconfigwindow.h \
    enterroomconfigwindow.h \
    remoteserviceutil.h \
    selectonlinebattletypewindow.h \
    snowmanwindow.h

RESOURCES += \
    resource.qrc

FORMS += \
    createroomconfigwindow.ui \
    enterroomconfigwindow.ui \
    selectonlinebattletypewindow.ui \
    snowmanwindow.ui
