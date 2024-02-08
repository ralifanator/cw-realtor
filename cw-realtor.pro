#-------------------------------------------------
#
# Project created by QtCreator 2023-08-26T17:49:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cw-realtor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        dialogdelete.cpp \
        dialogedit.cpp \
        dialogredaction.cpp \
        main.cpp \
        mainwindow.cpp \
    dialogauthor.cpp \
    model.cpp

HEADERS += \
        dialogdelete.h \
        dialogedit.h \
        dialogredaction.h \
        mainwindow.h \
    dialogauthor.h \
    model.h

FORMS += \
        dialogdelete.ui \
        dialogedit.ui \
        dialogredaction.ui \
        mainwindow.ui \
        dialogauthor.ui

TRANSLATIONS += tr/cw-realtor_ru_RU.ts \
                tr/cw-realtor_en_US.ts \
                tr/cw-realtor_deu_DEU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
