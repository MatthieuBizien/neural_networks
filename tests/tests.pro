include(../defaults.pri)
TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle
CONFIG   -= qt

#UnitTest.commands = make -C UnitTest++
#QMAKE_EXTRA_TARGETS += UnitTest
#PRE_TARGETDEPS += UnitTest

#INCLUDEPATH += ./unittest++
INCLUDEPATH += ../src/app
INCLUDEPATH += ../src/libs

SOURCES += main.cpp \
    matrixsequence_test.cpp \
    multilayerperceptron_test.cpp \
    gradientdescent_test.cpp \
    rprop_test.cpp\
