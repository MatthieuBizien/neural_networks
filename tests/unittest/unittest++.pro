#CONFIG += plugin

CONFIG += c++11
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x

QMAKE_CXXFLAGS += -Wno-sign-compare

TEMPLATE = lib

HEADERS += *.h

SOURCES += \
AssertException.cpp \
Checks.cpp \
CurrentTest.cpp \
DeferredTestReporter.cpp \
DeferredTestResult.cpp \
MemoryOutStream.cpp \
ReportAssert.cpp \
Test.cpp \
TestDetails.cpp \
TestList.cpp \
TestReporter.cpp \
TestReporterStdout.cpp \
TestResults.cpp \
TestRunner.cpp \
TimeConstraint.cpp \
XmlTestReporter.cpp

win32 {
	SOURCES += Win32/TimeHelpers.cpp \
}

