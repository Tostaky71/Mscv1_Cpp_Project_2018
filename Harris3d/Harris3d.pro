TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    harrisdetector.cpp \
    mesh.cpp \
    properties.cpp \
    vertex.cpp \
    main.cpp \

HEADERS += \
    harrisdetector.h \
    mesh.h \
    properties.h \
    vertex.h \


INCLUDEPATH += 'C:\Qt Libraries\eigen\eigen'
INCLUDEPATH += /home/blue/eigen
