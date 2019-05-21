#-------------------------------------------------
#
# Project created by QtCreator 2017-08-02T08:52:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuatroEnLinea
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Juego.cpp \
    Jugador.cpp \
    Tablero.cpp

HEADERS  += mainwindow.h \
    Constantes.h \
    Juego.h \
    Jugador.h \
    Tablero.h

FORMS    += mainwindow.ui \
    mainwindow2.ui \
    PantallaInicial.ui \
    FinDeJuego.ui

RESOURCES += \
    imagenes.qrc
