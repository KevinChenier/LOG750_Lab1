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
    QGLViewer/camera.cpp \
    QGLViewer/constraint.cpp \
    QGLViewer/frame.cpp \
    QGLViewer/keyFrameInterpolator.cpp \
    QGLViewer/manipulatedCameraFrame.cpp \
    QGLViewer/manipulatedFrame.cpp \
    QGLViewer/mouseGrabber.cpp \
    QGLViewer/qglviewer.cpp \
    QGLViewer/quaternion.cpp \
    QGLViewer/saveSnapshot.cpp \
    QGLViewer/vec.cpp \
        mainwindow.cpp \
    glwidget.cpp \
    simpleViewer.cpp

HEADERS  += mainwindow.h \
    QGLViewer/camera.h \
    QGLViewer/config.h \
    QGLViewer/constraint.h \
    QGLViewer/domUtils.h \
    QGLViewer/frame.h \
    QGLViewer/keyFrameInterpolator.h \
    QGLViewer/manipulatedCameraFrame.h \
    QGLViewer/manipulatedFrame.h \
    QGLViewer/mouseGrabber.h \
    QGLViewer/qglviewer.h \
    QGLViewer/quaternion.h \
    QGLViewer/vec.h \
    glwidget.h \
    simpleViewer.h

FORMS    += mainwindow.ui \
    QGLViewer/ImageInterface.ui \
    QGLViewer/VRenderInterface.ui

DISTFILES += \
    QGLViewer/README.md \
    QGLViewer/qglviewer-icon.xpm \
    QGLViewer/qglviewer.icns \
    QGLViewer/qglviewer_fr.qm \
    QGLViewer/qglviewer_fr.ts \
    basicShader.frag \
    basicShader.vert

CONFIG += C++11

SUBDIRS += \
    QGLViewer/QGLViewer.pro
