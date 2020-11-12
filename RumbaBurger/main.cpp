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
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;


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

    QDir dir;
    //dir.mkpath("./PRUEBAAA/20/10");
    //qDebug() << utiles::truncS(2.98765, 6);

    QApplication a(argc, argv);
    a.setApplicationName("DeDiezApp");

    Document xlsx(":/Template/Template/ReportTemplate.xlsx");

    //xlsx.write("A1", "Hello Qt!"); // write "Hello Qt!" to cell(A,1). it's shared string.
    //xlsx.saveAs("Test.xlsx"); // save the document as 'Test.xlsx'

    QFile f(":/qdarkstyle/style.qss");

    if (!f.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbName = "cafeteriadb.sqlite";
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
            QFile queryFile(":/bd/bd_structure/structure.sql");
            executeQueryFile(queryFile);
        }
    }

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
