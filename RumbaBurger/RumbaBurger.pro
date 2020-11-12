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
RESOURCES += ../RumbaBurger/qdarkstyle/style.qrc \
    recursos.qrc


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)


SOURCES += main.cpp\
    login.cpp \
    utiles.cpp \
    result.cpp \
    Dto/centralstoragedto.cpp \
    Dto/centralstoragetransactiondto.cpp \
    Dto/dishamountdto.cpp \
    Dto/dishdto.cpp \
    Dto/expensesdto.cpp \
    Dto/ingredientsdto.cpp \
    Dto/orderdishdto.cpp \
    Dto/orderdto.cpp \
    Dto/storagedto.cpp \
    Dto/storagetransactiondto.cpp \
    Dto/userdto.cpp \
    Services/centralstorageservice.cpp \
    Services/centralstoragetransactionservice.cpp \
    Services/dishservice.cpp \
    Services/expensesservice.cpp \
    Services/ingredientsservice.cpp \
    Services/orderdishservice.cpp \
    Services/orderservice.cpp \
    Services/productservice.cpp \
    Services/storageservice.cpp \
    Services/storagetransactionservice.cpp \
    Services/userservice.cpp \
    Dto/productdto.cpp \
    principal.cpp \
    form_almacenes.cpp \
    form_ofertas.cpp \
    Dto/storageproductdto.cpp \
    Services/localstorageservice.cpp \
    Dto/localstoragedto.cpp \
    form_ordenes.cpp \
    form_insertarorden.cpp \
    form_gastos.cpp \
    Services/dishversionsservice.cpp \
    form_reportes.cpp \
    form_modificarorden.cpp \
    form_transacciones.cpp \
    Services/transactionservice.cpp \
    Dto/transactiondto.cpp \
    form_inicial.cpp \
    form_user.cpp \
    form_cambiarpassword.cpp

HEADERS  += \
    login.h \
    utiles.h \
    result.h \
    Dto/centralstoragedto.h \
    Dto/centralstoragetransactiondto.h \
    Dto/dishamountdto.h \
    Dto/dishdto.h \
    Dto/expensesdto.h \
    Dto/ingredientsdto.h \
    Dto/orderdishdto.h \
    Dto/orderdto.h \
    Dto/productdto.h \
    Dto/storagedto.h \
    Dto/storagetransactiondto.h \
    Dto/userdto.h \
    Services/centralstorageservice.h \
    Services/centralstoragetransactionservice.h \
    Services/dishservice.h \
    Services/expensesservice.h \
    Services/ingredientsservice.h \
    Services/orderdishservice.h \
    Services/orderservice.h \
    Services/productservice.h \
    Services/storageservice.h \
    Services/storagetransactionservice.h \
    Services/userservice.h \
    principal.h \
    form_almacenes.h \
    form_ofertas.h \
    Dto/storageproductdto.h \
    Services/localstorageservice.h \
    Dto/localstoragedto.h \
    form_ordenes.h \
    form_insertarorden.h \
    form_gastos.h \
    Services/dishversionsservice.h \
    form_reportes.h \
    form_modificarorden.h \
    form_transacciones.h \
    Services/transactionservice.h \
    Dto/transactiondto.h \
    form_inicial.h \
    form_user.h \
    form_cambiarpassword.h

FORMS    += \
    login.ui \
    principal.ui \
    form_almacenes.ui \
    form_ofertas.ui \
    form_ordenes.ui \
    form_insertarorden.ui \
    form_gastos.ui \
    form_reportes.ui \
    form_modificarorden.ui \
    form_transacciones.ui \
    form_inicial.ui \
    form_user.ui \
    form_cambiarpassword.ui

include(D:/Pincha/RumbaBurger/RumbaBurger/QtRptProject/QtRPT/QtRPT.pri)

RESOURCES +=
