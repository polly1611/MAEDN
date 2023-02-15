QT += gui

CONFIG += c++17 console
QT += network \
    widgets
QT += sql
CONFIG -= app_bundle

QT += websockets

SOURCES += \
        game.cpp \
        main.cpp \
        mainwindow.cpp \
        player.cpp \
        playercommunimanager.cpp \
        queuemanager.cpp \
        routes/httptestroute.cpp \
        routes/jsontestroute.cpp \
        socket/websocketserver.cpp \
        utils/jsonutils.cpp \
        utils/mariadb.cpp \
        utils/ws_utils.cpp \
        ws/webserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    game.h \
    mainwindow.h \
    player.h \
    playercommunimanager.h \
    queuemanager.h \
    routes/httptestroute.h \
    routes/iroutehandler.h \
    routes/jsontestroute.h \
    socket/websocketserver.h \
    utils/jsonutils.h \
    utils/mariadb.h \
    utils/ws_utils.h \
    ws/webserver.h

FORMS += \
    mainwindow.ui
