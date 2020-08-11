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
