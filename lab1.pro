#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T11:30:04
#
#-------------------------------------------------

QT       += core gui xml opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab1
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    glwidget.cpp \

HEADERS  += mainwindow.h \
    glwidget.h \

FORMS    += mainwindow.ui \

DISTFILES += \
    basicShader.frag \
    basicShader.vert

CONFIG += C++11
