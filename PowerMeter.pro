TEMPLATE = app

QT += qml quick network
CONFIG += c++11

SOURCES += main.cpp \
    application.cpp \
    obdsocket.cpp \
    obddatahandler.cpp \
    obdrequest.cpp \
    obdpid.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    application.h \
    obdsocket.h \
    obddatahandler.h \
    obdrequest.h \
    obd.h \
    obdpid.h
