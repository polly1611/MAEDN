QT += gui

CONFIG += c++17 console
QT += network \
    widgets
QT += sql
CONFIG -= app_bundle

QT += websockets

SOURCES += \
        csvfile.cpp \
        gamemanager.cpp \
        main.cpp \
        mainwindow.cpp \
        startwindow.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    csvfile.h \
    gamemanager.h \
    mainwindow.h \
    startwindow.h

FORMS += \
    mainwindow.ui \
    startwindow.ui
