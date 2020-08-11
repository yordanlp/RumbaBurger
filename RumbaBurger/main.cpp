#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <dbmanager.h>
#include <productdto.h>
#include "productservice.h"
#include "userservice.h"
#include "orderdto.h"
#include "orderservice.h"
#include "dishdto.h"
#include "dishservice.h"
#include "expensesdto.h"
#include "expensesservice.h"
#include "orderdishdto.h"
#include "orderdishservice.h"
#include "ingredientsdto.h"
#include "ingredientsservice.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("rumbaburgerdb.sqlite");
    if( !db.open() )
        qDebug() << "Database not open";

    IngredientsDto id;
    id.idDish = 3;
    id.idProduct = 10;
    id.amount = 10;

    IngredientsService is;
    qDebug() << is.getIngredientsByDishId(id).size();

    db.close();

    //return a.exec();
    return 0;
}
