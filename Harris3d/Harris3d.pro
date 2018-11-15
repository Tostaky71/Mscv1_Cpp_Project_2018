TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    HarrisDetector.cpp \
    Mesh.cpp \
    Properties.cpp \
    Vertex.cpp

HEADERS += \
    Face.h \
    HarrisDetector.h \
    Mesh.h \
    Properties.h \
    Vertex.h
