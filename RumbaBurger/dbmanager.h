#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <Dto/productdto.h>

class DBManager
{
private:

public:
    DBManager();
    /** Product **/
    bool insertProduct( ProductDto );
    bool deleteProduct( ProductDto );
    ProductDto getProductByID( int );
    QList<ProductDto> gerProducts();
    bool getProductByName( QString );

    /****/

    QSqlDatabase db;

};

#endif // DBMANAGER_H
