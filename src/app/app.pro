include('../../defaults.pri')

TEMPLATE = app
TARGET = ../../neuralnetwork
CONFIG += console
CONFIG -= qt

INCLUDEPATH += ../libs

SOURCES += main.cpp \
           ./parsercsv/CSVManager.cpp \

HEADERS += *.h \
    utils/*.h \
    gradientdescent/*.h \
    neuralnets/*.h \
    parsercsv/*.h \
