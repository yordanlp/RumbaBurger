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

double utiles::convertPeso(weigth from, weigth to, double peso ){
    if( to == G ){
        if( from == LB )
            return peso * 453.592;
        if( from == KG )
            return peso * 1000;
        return peso;
    }
    if( to == KG ){
        if( from == LB )
            return peso * 0.453;
        if( from == G )
            return peso * 0.001;
        return peso;
    }
    if( from == KG )
        return peso * 2.2;
    if ( from == G )
        return peso * 0.0022;
    return peso;
}

double utiles::convertPrecio(weigth from, weigth to, double precio ){
    if( to == G ){
        if( from == LB )
            return precio / 453.592;
        if( from == KG )
            return precio / 1000;
        return precio;
    }
    if( to == KG ){
        if( from == LB )
            return precio / 0.453;
        if( from == G )
            return precio / 0.001;
        return precio;
    }
    if( from == KG )
        return precio / 2.2;
    if ( from == G )
        return precio / 0.0022;
    return precio;
}

double utiles::GANANCIA = 0.50;
double utiles::IMPUESTO = 0.10;
