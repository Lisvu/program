QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animationmanager.cpp \
    databasemanager.cpp \
    gameengine.cpp \
    gamescreen.cpp \
    main.cpp \
    mainwindow.cpp \
    shopmanager.cpp \
    skillmanager.cpp \
    soundmanager.cpp \
    usermanager.cpp

HEADERS += \
    animationmanager.h \
    databasemanager.h \
    gameengine.h \
    gamescreen.h \
    mainwindow.h \
    shopmanager.h \
    skillmanager.h \
    soundmanager.h \
    usermanager.h

FORMS += \
    gamescreen.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
