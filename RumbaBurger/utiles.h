#ifndef UTILES_H
#define UTILES_H


#include<QDate>
#include<QString>
#include<QStringList>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>

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
    static QString MONEDA, UNIDAD;
    static QString unitFromPeso( weigth p );
    static int TextAlign;
    static double trunc( double n, int dec );
    static QString truncS( double n, int dec );

    //static void executeQueryFile(QFile &qf, QSqlDatabase &db);
};


#endif // UTILES_H
