include(../defaults.pri)
TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle
CONFIG   -= qt

win32 {
    UnitTest.target = ./unittest/libunittest++.dll
    POST_TARGETDEPS += ./unittest/libunittest++.dll
}
!win32 {
    UnitTest.target = ./unittest/libunittest++.so
    POST_TARGETDEPS += ./unittest/libunittest++.so
}

UnitTest.commands = cd unittest && qmake && make
QMAKE_EXTRA_TARGETS += UnitTest

INCLUDEPATH += ./unittest
SOURCES += ./unittest/*.cpp
SOURCES += ./unittest/Posix/*.cpp

INCLUDEPATH += ../src/app
INCLUDEPATH += ../src/libs

SOURCES += main.cpp \
    matrixsequence_test.cpp \
    multilayerperceptron_test.cpp \
    gradientdescent_test.cpp \
    rprop_test.cpp\
