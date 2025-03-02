#-------------------------------------------------
#
# Project created by QtCreator 2020-10-27T22:19:44
#
#-------------------------------------------------

QT       += widgets

TARGET = median_filter_plugin
TEMPLATE = lib
CONFIG += plugin

DEFINES += MEDIAN_FILTER_PLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        median_filter_plugin.cpp

HEADERS += \
        median_filter_plugin.h \
        median_filter_plugin_global.h \ 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH +=$$PWD/../

win32: {
    include(../Opencvpri/opencv.pri)
}

