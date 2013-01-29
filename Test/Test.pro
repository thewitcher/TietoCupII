#-------------------------------------------------
#
# Project created by QtCreator 2013-01-29T20:00:07
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testtest.cpp \
    ../BotClient/helper.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../BotClient/helper.h
