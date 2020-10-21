#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H
#include <Dto/productdto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "result.h"

class ProductService
{
public:
    ProductService();
    Result<int> insertProduct( ProductDto );
    Result<bool> deleteProduct( ProductDto );
    Result<ProductDto> getProductByID(ProductDto id );
    Result<QList<ProductDto>> getAllProduct();
    Result<ProductDto> getProductByName( QString );
    Result<bool> updateProduct( ProductDto );
    Result<double> getPrice( int idProduct );
    Result<QStringList> getAllProductsToString();
    Result<QStringList> isUsed( int productId );

};

#endif // PRODUCTSERVICE_H
