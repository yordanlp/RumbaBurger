#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H
#include <productdto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class ProductService
{
public:
    ProductService();
    bool insertProduct( ProductDto );
    bool deleteProduct( ProductDto );
    ProductDto getProductByID( ProductDto );
    QList<ProductDto> getAllProduct();
    bool getProductByName( QString );
    bool updateProduct( ProductDto );

};

#endif // PRODUCTSERVICE_H
