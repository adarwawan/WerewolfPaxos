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
    interface.cpp \
    comm_server.cpp \
    listplayer.cpp \
    gameplay.cpp \
    comm_client.cpp

HEADERS  += login.h \
    interface.h \
    comm_server.h \
    listplayer.h \
    gameplay.h \
    comm_client.h

FORMS    += login.ui \
    gameplay.ui
