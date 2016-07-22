TEMPLATE = app

QT += qml quick network
CONFIG += c++11

SOURCES += main.cpp \
    application.cpp \
    obdsocket.cpp \
    logger.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    application.h \
    obdsocket.h \
    logger.h
