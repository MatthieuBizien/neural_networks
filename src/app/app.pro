include('../../defaults.pri')

TEMPLATE = app
TARGET = ../../neuralnetwork
CONFIG += console
CONFIG -= qt

INCLUDEPATH += ../libs

SOURCES += main.cpp \
    matrixsequence.cpp

HEADERS = \
    matrixsequence.h

