QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    guimainwindow.cpp \
    main_gui.cpp

HEADERS += \
    guimainwindow.h

FORMS += \
    guimainwindow.ui

include(../build.pri)

!contains(XCONFIG, xoptions) {
    XCONFIG += xoptions
    include(../XOptions/xoptions.pri)
}
