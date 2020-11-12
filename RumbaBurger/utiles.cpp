#include "utiles.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

QDate utiles::stringToDate(QString s){
    QStringList d = s.split("-");
    QString x = d.at(0);
    int anno = x.toInt();
    x = d.at(1);
    int mes = x.toInt();
    x = d.at(2);
    int dia = x.toInt();
    QDate p(anno,mes,dia);
    return p;
}

QString utiles::searchToRegExp(QString search){
    if( search == "" ) return "%";
    return "%" + search.toLower() + "%";
}

QString utiles::unitFromNumber(int unitType){
    if( unitType == 1 ) return "g";
    return "u";
}

double utiles::convertPeso(weigth from, weigth to, double peso ){
    if( to == G ){
        if( from == LB )
            return peso * 453.592333346094;
        if( from == KG )
            return peso * 1000;
        return peso;
    }
    if( to == KG ){
        if( from == LB )
            return peso * 0.4535923333460944;
        if( from == G )
            return peso * 0.001;
        return peso;
    }
    if( from == KG )
        return peso * 2.2046228;
    if ( from == G )
        return peso * 0.0022046228;
    return peso;
}

double utiles::convertPrecio(weigth from, weigth to, double precio ){
    if( to == G ){
        if( from == LB )
            return precio / 453.592333346094;
        if( from == KG )
            return precio / 1000;
        return precio;
    }
    if( to == KG ){
        if( from == LB )
            return precio / 0.4535923333460944;
        if( from == G )
            return precio / 0.001;
        return precio;
    }
    if( from == KG )
        return precio / 2.2046228;
    if ( from == G )
        return precio / 0.0022046228;
    return precio;
}

QString utiles::unitFromPeso(weigth p)
{
    if( p == G ) return "g";
    if( p == KG ) return "kg";
    return "lb";
}


double utiles::trunc(double n, int dec)
{
    qDebug() << n;

    int p10[3] = {1, 10, 100};
    n *= p10[dec];
    double ret = (int)n;
    ret /= p10[dec];
    return ret;
}

QString utiles::truncS(double n, int dec){
    double res = trunc(n, dec);
    QString ret = QString::number( res, 'f', dec );
    return ret;
}

double utiles::GANANCIA = 0.50;
double utiles::IMPUESTO = 0.10;
QString utiles::MONEDA = "CUP";
QString utiles::UNIDAD = "gramos";
int utiles::TextAlign = Qt::AlignHCenter | Qt::AlignVCenter;

/*void utiles::executeQueryFile(QFile &qf, QSqlDatabase &db) {
    //Read query file content
    qf.open(QIODevice::ReadOnly);
    QString queryStr(qf.readAll());
    qf.close();

    //Check if SQL Driver supports Transactions
    if(db.driver()->hasFeature(QSqlDriver::Transactions)) {
        //Replace comments and tabs and new lines with space
        queryStr = queryStr.replace(QRegularExpression("(\\/\\*(.|\\n)*?\\*\\/|^--.*\\n|\\t|\\n)", QRegularExpression::CaseInsensitiveOption|QRegularExpression::MultilineOption), " ");
        //Remove waste spaces
        queryStr = queryStr.trimmed();

        //Extracting queries
        QStringList qList = queryStr.split(';', QString::SkipEmptyParts);

        //Initialize regular expression for detecting special queries (`begin transaction` and `commit`).
        //NOTE: I used new regular expression for Qt5 as recommended by Qt documentation.
        QRegularExpression re_transaction("\\bbegin.transaction.*", QRegularExpression::CaseInsensitiveOption);
        QRegularExpression re_commit("\\bcommit.*", QRegularExpression::CaseInsensitiveOption);

        //Check if query file is already wrapped with a transaction
        bool isStartedWithTransaction = re_transaction.match(qList.at(0)).hasMatch();
        if(!isStartedWithTransaction)
          db.transaction();     //<=== not wrapped with a transaction, so we wrap it with a transaction.

        //Execute each individual queries
        foreach(const QString &s, qList) {
          if(re_transaction.match(s).hasMatch())    //<== detecting special query
              db.transaction();
          else if(re_commit.match(s).hasMatch())    //<== detecting special query
              db.commit();
          else {
              QSqlQuery query;
              query.exec(s);                        //<== execute normal query
              if(query.lastError().type() != QSqlError::NoError) {
                  qDebug() << query.lastError().text();
                  db.rollback();                    //<== rollback the transaction if there is any problem
              }
          }
        }
        if(!isStartedWithTransaction)
          db.commit();          //<== ... completing of wrapping with transaction

    //Sql Driver doesn't supports transaction
    } else {

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
}*/
