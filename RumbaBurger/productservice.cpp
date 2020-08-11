#include "productservice.h"
#include <QSqlQuery>

ProductService::ProductService()
{

}

bool ProductService::insertProduct(ProductDto p){
    QSqlQuery query;
    query.prepare("INSERT INTO product (productName, unitType, price) VALUES (:productName, :unitType, :price)");
    query.bindValue(":productName", p.productName);
    query.bindValue(":unitType", p.unitType);
    query.bindValue(":price", p.price);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertProduct: " << query.lastError().text();
    return false;
}

bool ProductService::deleteProduct(ProductDto p){
    QSqlQuery query;
    query.prepare("DELETE FROM product WHERE id = :id");
    query.bindValue(":id", p.id);
    if( query.exec() ) return true;
    qDebug() << "ERROR deleteProduct: " << query.lastError().text();
    return false;
}

ProductDto ProductService::getProductByID(ProductDto p){
    QSqlQuery query;
    query.prepare("SELECT * FROM product WHERE id = :id");
    query.bindValue(":id", p.id);
    if( !query.exec() ){
        qDebug() << "ERROR getProductByID:" << query.lastError().text();
        return ProductDto(-1,"",-1,-1);
    }

    query.next();
    return ProductDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toDouble());
}

QList<ProductDto> ProductService::getAllProduct(){
    QSqlQuery query;
    query.prepare("SELECT * FROM product");
    if( !query.exec() ){
        qDebug() << "ERROR getProductByID:" << query.lastError().text();
        return QList<ProductDto>();
    }

    QList<ProductDto>ret;
    while( query.next() ){
        ret << ProductDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toDouble());
    }
    return ret;
}

bool ProductService::updateProduct(ProductDto p){
    QSqlQuery query;
    query.prepare("UPDATE product SET productName=:productName, unitType=:unitType, price=:price  WHERE id=:id");
    query.bindValue(":productName", p.productName);
    query.bindValue(":unitType", p.unitType);
    query.bindValue(":price", p.price);
    query.bindValue(":id", p.id);
    if( query.exec() ) return true;
    qDebug() << "ERROR updateProductbyID: " << query.lastError().text();
    return false;
}
