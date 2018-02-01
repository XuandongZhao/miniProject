#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T10:10:17
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QTPLUGIN += QSQLMYSQL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyLibrary
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    insertbook.cpp \
    login.cpp \
    searchbook.cpp \
    borrow.cpp

HEADERS  += mainwindow.h \
    Link.h \
    insertbook.h \
    login.h \
    searchbook.h \
    borrow.h

FORMS    += mainwindow.ui \
    insertbook.ui \
    login.ui \
    searchbook.ui \
    borrow.ui
