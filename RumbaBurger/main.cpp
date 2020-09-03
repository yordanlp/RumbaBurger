#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDebug>
#include "result.h"
#include <QtCore>
#include <QtWidgets>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("rumbaburgerdb.sqlite");
    if( !db.open() )
        qDebug() << "Database not open";

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    Login *l;
    l = new Login();
    l->show();


    return a.exec();
}
