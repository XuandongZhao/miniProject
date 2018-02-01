#-------------------------------------------------
#
# Project created by QtCreator 2015-05-03T20:53:35
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets
QT       += network
QT       += winextras


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExcellentMusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mymaindlg.cpp \
    downloadinfodlg.cpp \
    mylrc.cpp \
    mymaintablewidget.cpp \
    mynetwork.cpp \
    myplaylist.cpp \
    qsingleapplication.cpp \
    searchlrcdlg.cpp \
    skinbox.cpp \
    musicmarqueewidget.cpp \
    mybutton.cpp

HEADERS  += mymaindlg.h \
    downloadinfodlg.h \
    mylrc.h \
    mymaintablewidget.h \
    mynetwork.h \
    myplaylist.h \
    qsingleapplication.h \
    searchlrcdlg.h \
    skinbox.h \
    musicmarqueewidget.h \
    mybutton.h

FORMS    += mymaindlg.ui \
    downloadinfodlg.ui \
    searchlrcdlg.ui \
    skinbox.ui

RESOURCES += \
    resource.qrc
RC_FILE = image/sysicon.rc
