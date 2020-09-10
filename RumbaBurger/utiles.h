#ifndef UTILES_H
#define UTILES_H


#include<QDate>
#include<QString>
#include<QStringList>

class utiles
{
public:
    utiles();

    static QDate stringToDate(QString);
    static QString searchToRegExp(QString search);
    static QString unitFromNumber( int unitType );
};


#endif // UTILES_H
