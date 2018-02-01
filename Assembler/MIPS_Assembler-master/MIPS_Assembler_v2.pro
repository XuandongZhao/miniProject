TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    assembler.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    assembler.h

