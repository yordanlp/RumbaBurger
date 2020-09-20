#ifndef UTILES_H
#define UTILES_H


#include<QDate>
#include<QString>
#include<QStringList>

enum weigth{
    LB, G, KG
};

const unsigned int SOLIDO = 1, UNIDAD = 2; 

class utiles
{
public:
    utiles();

    static QDate stringToDate(QString);
    static QString searchToRegExp(QString search);
    static QString unitFromNumber( int unitType );
    static double convertPeso(weigth from, weigth to, double peso);
    static double convertPrecio(weigth from, weigth to, double precio);
    static double GANANCIA, IMPUESTO;
};


#endif // UTILES_H
