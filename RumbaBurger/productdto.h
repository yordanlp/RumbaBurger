#ifndef PRODUCTDTO_H
#define PRODUCTDTO_H
#include <QString>
#include<bits/stdc++.h>


class ProductDto
{
public:
    ProductDto();
    ProductDto( int _id, QString _productName, int _unitType, double _price );
    int id;
    QString productName;
    int unitType;
    double price;

};

#endif // PRODUCTDTO_H
