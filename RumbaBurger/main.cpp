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
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "rumbaburgerdb.sqlite";
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
    //QApplication::setStyle(QStyleFactory::create("Fusion"));

    Login *l;
    l = new Login();
    l->show();


    return a.exec();
}
