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
#include <utiles.h>

QSqlDatabase db;
void executeQueryFile(QFile &qf) {
    //Read query file content
    qf.open(QIODevice::ReadOnly);
    QString queryStr(qf.readAll());
    qf.close();

    //Check if SQL Driver supports Transactions
    {
        //...so we need to remove special queries (`begin transaction` and `commit`)
        queryStr = queryStr.replace(QRegularExpression("(\\bbegin.transaction.*;|\\bcommit.*;|\\/\\*(.|\\n)*?\\*\\/|^--.*\\n|\\t|\\n)", QRegularExpression::CaseInsensitiveOption|QRegularExpression::MultilineOption), " ");
        queryStr = queryStr.trimmed();

        //Execute each individual queries
        QStringList qList = queryStr.split(';', QString::SkipEmptyParts);
        foreach(const QString &s, qList) {
          QSqlQuery query;
          query.exec(s);
          if(query.lastError().type() != QSqlError::NoError) qDebug() << query.lastError().text();
        }
    }
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setApplicationName("RumbaBurgerApp");

    QFile f(":qdarkstyle/style.qss");

    if (!f.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "rumbaburgerdb1.sqlite";
    db.setDatabaseName(dbName);


    if( !db.open() ){
        qDebug() << "Error al abrir la base de datos";
    }else{
        QFile database(dbName);
        if( database.size() == 0 ){
            qDebug() << "No existe";
            if( !database.open(QFile::WriteOnly | QFile::Text) ){
                qDebug() << "Error al crear la base de datos. No se pudo abrir el archivo";
                return a.exec();
            }
            QFile queryFile("structure.sql");
            executeQueryFile(queryFile);
            /*QSqlQuery query;
            QString q = "INSERT INTO users VALUES (0, 'admin', 'admin', 'Administrador')";
            query.exec(q);*/

        }
    }

    QSettings settings("Limitless", "RumbaBurger");
    settings.beginGroup("Settings");
    utiles::IMPUESTO = settings.value("ONAT", 10).toDouble()/100.0;
    utiles::GANANCIA = settings.value("Ganancia", 100).toDouble()/100.0;
    utiles::MONEDA = settings.value("Moneda", "CUP").toString();
    utiles::UNIDAD = settings.value("Unidad", "G").toString();
    settings.endGroup();

    qDebug() << "IMPUESTO" << utiles::IMPUESTO;
    qDebug() << "GANANCIA" << utiles::GANANCIA;
    qDebug() << "MONEDA" << utiles::MONEDA;
    qDebug() << "UNIDAD" << utiles::UNIDAD;

    /*QSettings settings("Limitless", "RumbaBurger");
    settings.beginGroup("Impuestos");
    settings.setValue("ONAT", 10.0);
    settings.setValue("Ganancia", 100.0);
    settings.endGroup();
    settings.beginGroup("Moneda");
    settings.setValue("Moneda", "CUP");
    settings.endGroup();
    settings.beginGroup("Unidades");
    settings.setValue("Unidad", "gramos");
    settings.endGroup();*/




    Login *l;
    l = new Login();
    l->show();

    return a.exec();
}
