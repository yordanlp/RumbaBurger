#ifndef STORAGEPRODUCTDTO_H
#define STORAGEPRODUCTDTO_H
#include <QtCore>
#include <utiles.h>

class StorageProductDto
{
public:
    int id;
    double amount;
    QString name;
    double price;
    int unitType;
    StorageProductDto();
    StorageProductDto( int _id, QString _name, double _amount, double _price, int unitType );

};

#endif // STORAGEPRODUCTDTO_H
