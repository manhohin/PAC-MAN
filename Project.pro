QT       += core gui\
        multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attack.cpp \
    bigdots.cpp \
    catwall.cpp \
    graphics.cpp \
    entities.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwindow.cpp \
    map.cpp \
    player.cpp \
    ghost.cpp \
    powerup.cpp \
    scorebuff.cpp \
    smalldots.cpp \
    speeddown.cpp \
    speedup.cpp \
    wall.cpp \
    winwidget.cpp \
    winwindow.cpp

HEADERS += \
    attack.h \
    bigdots.h \
    catwall.h \
    entities.h \
    graphics.h \
    mainwindow.h \
    menuwindow.h \
    map.h \
    player.h \
    ghost.h \
    powerup.h \
    scorebuff.h \
    smalldots.h \
    speeddown.h \
    speedup.h \
    wall.h \
    winwidget.h \
    winwindow.h

FORMS += \
    mainwindow.ui \
    menuwindow.ui \
    winwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    sounds.qrc
