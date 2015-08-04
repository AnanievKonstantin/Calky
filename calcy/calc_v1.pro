#-------------------------------------------------
#
# Project created by QtCreator 2015-06-23T04:23:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calc_v1
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    Window.cpp \
    Control.cpp \
    Recognizer.cpp \
    Parser.cpp \
    Model.cpp \
    Button.cpp \
    Textedit.cpp


HEADERS  += \
    Window.h \
    Control.h \
    Recognizer.h \
    Parser.h \
    Parser_name_space.h \
    Model.h \
    Button.h \
    Textedit.h

