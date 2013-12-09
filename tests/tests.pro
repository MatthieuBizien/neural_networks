include(../defaults.pri)
TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle
CONFIG   -= qt

#UnitTest.commands = make -C UnitTest++
#QMAKE_EXTRA_TARGETS += UnitTest
#PRE_TARGETDEPS += UnitTest

LIBS += -lunittest++

INCLUDEPATH += ./UnitTest
INCLUDEPATH += ../src/app
INCLUDEPATH += ../src/libs

SOURCES += main.cpp \
    matrixsequence_test.cpp

SOURCES += ../src/app/matrixsequence.cpp
