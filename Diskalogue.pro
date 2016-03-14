#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T20:08:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Diskalogue
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    mediaitem.cpp \
    func.cpp \
    catalog.cpp \
    testunit.cpp \
    qdevicewatcher.cpp \
    qdevicewatcher_wince.cpp \
    qdevicewatcher_win32.cpp \
    qdevicewatcher_linux.cpp

HEADERS  += mainwindow.h \
    mediaitem.h \
    mediatypes.h \
    func.h \
    catalog.h \
    testunit.h \
    qdevicewatcher.h \
    qdevicewatcher_p.h \
    devicewatcher.h

FORMS    += mainwindow.ui
