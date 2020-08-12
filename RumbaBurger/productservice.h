#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H
#include <productdto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "result.h"

class ProductService
{
public:
    ProductService();
    Result<bool> insertProduct( ProductDto );
    Result<bool> deleteProduct( ProductDto );
    Result<ProductDto> getProductByID( ProductDto );
    Result<QList<ProductDto>> getAllProduct();
    Result<bool> getProductByName( QString );
    Result<bool> updateProduct( ProductDto );
    Result<double> getPrice( int idProduct );

};

#endif // PRODUCTSERVICE_H
