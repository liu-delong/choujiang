QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controlview.cpp \
    main.cpp \
    mainwindow.cpp \
    mingdanboxview.cpp \
    mingdanview.cpp \
    myframe.cpp \
    mytableview.cpp

HEADERS += \
    controlview.h \
    mainwindow.h \
    mingdanboxview.h \
    mingdanview.h \
    myframe.h \
    mytableview.h

FORMS += \
    controlview.ui \
    mainwindow.ui \
    mingdanboxview.ui \
    mingdanview.ui

TRANSLATIONS += \
    choujiang_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations
CONFIG += static
RC_ICONS = icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
