include('../../defaults.pri')

TEMPLATE = app
TARGET = ../../neuralnetwork
CONFIG += console
CONFIG -= qt

INCLUDEPATH += ../libs

SOURCES += main.cpp \
    matrixsequence.cpp \
    multilayerperceptron.cpp

HEADERS = \
    matrixsequence.h \
    dimensionalexception.h \
    minimizeur.h \
    multilayerperceptron.h \
    gradientdescent.h \
    rprop.h
