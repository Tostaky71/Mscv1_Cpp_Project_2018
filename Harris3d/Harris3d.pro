TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    harrisdetector.cpp \
    mesh.cpp \
    properties.cpp \
    vertex.cpp \
    utility.cpp \
    main.cpp \
    face.cpp

HEADERS += \
    harrisdetector.h \
    mesh.h \
    properties.h \
    vertex.h \
    utility.h \
    face.h
