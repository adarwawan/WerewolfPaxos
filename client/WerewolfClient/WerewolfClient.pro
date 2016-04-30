#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T21:02:48
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WerewolfClient
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    handler_server.cpp \
    ready.cpp \
    interface.cpp \
    handler_client.cpp

HEADERS  += login.h \
    handler_server.h \
    ready.h \
    interface.h \
    handler_client.h

FORMS    += login.ui \
    ready.ui
