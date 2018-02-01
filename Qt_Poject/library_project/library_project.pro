#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T15:02:03
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = library_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    book_in_dialog.cpp \
    borrow_dialog.cpp \
    borrowcard_dialog.cpp \
    return_dialog.cpp \
    book_query.cpp \
    ad_insert_dialog.cpp

HEADERS  += mainwindow.h \
    database.h \
    logindialog.h \
    book_in_dialog.h \
    borrow_dialog.h \
    borrowcard_dialog.h \
    return_dialog.h \
    book_query.h \
    ad_insert_dialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    book_in_dialog.ui \
    borrow_dialog.ui \
    borrowcard_dialog.ui \
    return_dialog.ui \
    book_query.ui \
    ad_insert_dialog.ui

RESOURCES += \
    ziyuan.qrc
