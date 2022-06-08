QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    dialogoptions.cpp \
    guimainwindow.cpp \
    main_gui.cpp

HEADERS += \
    dialogoptions.h \
    guimainwindow.h

FORMS += \
    dialogoptions.ui \
    guimainwindow.ui

include(../build.pri)

XCONFIG += use_disasm
XCONFIG += use_extrabuttons

!contains(XCONFIG, archive_widget) {
    XCONFIG += archive_widget
    include(../archive_widget/archive_widget.pri)
}

!contains(XCONFIG, dialogattachprocess) {
    XCONFIG += dialogattachprocess
    include(../../_mylibs/XProcessWidget/dialogattachprocess.pri)
}

