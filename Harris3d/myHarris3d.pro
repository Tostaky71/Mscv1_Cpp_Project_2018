#-------------------------------------------------
#
# Project created by QtCreator 2019-01-06T16:46:29
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myHarris3d
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    harrisdetector.cpp \
    mesh.cpp \
    myglwidget.cpp \
    properties.cpp \
    vertex.cpp

HEADERS += \
    harrisdetector.h \
    mesh.h \
    myglwidget.h \
    properties.h \
    vertex.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += 'C:\Qt libraries\eigen'          # for Lisa's library
INCLUDEPATH += 'C:\Qt Libraries\eigen\eigen'    # for Nahid's library
INCLUDEPATH += /home/blue/eigen                 # for Damien's library

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
