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
#include "dishdto.h"
#include "dishservice.h"
#include "expensesdto.h"
#include "expensesservice.h"
#include "orderdishdto.h"
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
#include "result.h"


int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("rumbaburgerdb.sqlite");
    if( !db.open() )
        qDebug() << "Database not open";

    centralStorageService t;
    t.modifyCentralStorage(9,20,1,2);

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
}
