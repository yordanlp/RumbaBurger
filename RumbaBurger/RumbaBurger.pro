#-------------------------------------------------
#
# Project created by QtCreator 2020-08-10T17:50:03
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RumbaBurger
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    dbmanager.cpp \
    productdto.cpp \
    productservice.cpp \
    userdto.cpp \
    userservice.cpp \
    orderdto.cpp \
    orderservice.cpp \
    dishdto.cpp \
    dishservice.cpp \
    expensesdto.cpp \
    expensesservice.cpp \
    orderdishdto.cpp \
    orderdishservice.cpp \
    ingredientsdto.cpp \
    ingredientsservice.cpp

HEADERS  += mainwindow.h \
    login.h \
    dbmanager.h \
    productdto.h \
    productservice.h \
    userdto.h \
    userservice.h \
    orderdto.h \
    orderservice.h \
    dishdto.h \
    dishservice.h \
    expensesdto.h \
    expensesservice.h \
    orderdishdto.h \
    orderdishservice.h \
    ingredientsdto.h \
    ingredientsservice.h

FORMS    += mainwindow.ui \
    login.ui
