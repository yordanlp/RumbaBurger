#include "utiles.h"

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
