#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <dbmanager.h>
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
