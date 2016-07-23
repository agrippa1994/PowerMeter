TEMPLATE = app

QT += qml quick network
CONFIG += c++11

SOURCES += main.cpp \
    application.cpp \
    obdsocket.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    application.h \
    obdsocket.h

ios {
    ios_icon.files = $$files($$PWD/icon/ios/Icon*.png)
    QMAKE_BUNDLE_DATA += ios_icon
}
