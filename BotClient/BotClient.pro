TEMPLATE = app
CONFIG += console
CONFIG = qt
DEFINES += LOGGER

SOURCES += main.cpp \
    helper.cpp \
    connection.cpp \
    algorithm.cpp

HEADERS += \
    helper.h \
    exc.h \
    connection.h \
    algorithm.h

