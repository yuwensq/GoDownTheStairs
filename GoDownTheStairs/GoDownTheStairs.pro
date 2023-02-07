#-------------------------------------------------
#
# Project created by QtCreator 2021-04-04T17:53:14
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
CONFIG += resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoDownTheStairs
TEMPLATE = app


SOURCES += main.cpp\
        godownthestairs.cpp \
    start.cpp \
    stair.cpp \
    people.cpp

HEADERS  += godownthestairs.h \
    start.h \
    stair.h \
    people.h

FORMS    += godownthestairs.ui \
    start.ui

RESOURCES += \
    resource.qrc \
    img.qrc

