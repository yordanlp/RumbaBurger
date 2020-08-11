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
#include <productservice.h>
#include <storagedto.h>
#include <storageservice.h>
#include <storagetransactiondto.h>
#include <storagetransactionservice.h>
#include <centralstoragedto.h>
#include <centralstorageservice.h>
#include <centralstoragetransactiondto.h>
#include <centralstoragetransactionservice.h>
#include <QDebug>


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

    centralStorageTransactionDto p;
    p.date = QDate(2021,10,1);
    p.id = 1;
    p.idProduct = 8;
    p.amount = 20;
    p.idUser = 1;
    p.price = 1100;
    p.type = 1;

    centralStorageTransactionService q;
    q.insertCentralStorageTransaction(p);
    QDate inicial(2022,9,1);
    QDate final(2022,1,1);

    QList<centralStorageTransactionDto> ret;
    ret = q.getCentralStorageTransactionByDate(inicial,final);
    for(int i=0;i<ret.size();i++){
        qDebug() << ret[i].date << "\n";
    }


    /*MainWindow w;
    w.show();*/

    /*Login l;
    l.show();*/

    /*QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("rumbaburgerdb.sqlite");

    if( db.open() ){
        qDebug() << "sii";
        QSqlQuery q;
        q.prepare("SELECT * FROM unit");


        if( q.exec() ){
            QString data;
            while (q.next()) {
                data += q.value(0).toDouble();
            }
            qDebug() << data;
        }else{
            qDebug() << "no cons" << q.lastError().text();
        }

    }else{
        qDebug() << "nooo";
    }*/

    db.close();

    //return a.exec();
    return 0;

    qDebug() << "Hola Mundo";

    //return a.exec();

}
