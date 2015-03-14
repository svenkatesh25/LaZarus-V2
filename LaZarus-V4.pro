#-------------------------------------------------
#
# Project created by QtCreator 2015-03-01T10:57:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaZarus-V4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp \
    gameboardobject.cpp \
    objectdirectory.cpp \
    pausemenu.cpp \
    player.cpp \
    zombie.cpp \
    item.cpp \
    gun.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    doclib.h \
    gameboard.h \
    gameboardobject.h \
    objectdirectory.h \
    pausemenu.h \
    player.h \
    zombie.h \
    item.h \
    gun.h \
    game.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    biohazard bin.jpg \
    bloodsplatter.jpeg \
    Dana 1.jpg \
    Gray.jpg \
    Zombie fanart.jpg \
    Down Arrow.png \
    LaZarus.png \
    Left arrow.png \
    Right Arrow.png \
    Up Arrow.png \
    Black.jpg
