#include "productservice.h"
#include <QSqlQuery>

ProductService::ProductService()
{

}

Result<int> ProductService::insertProduct(ProductDto p){
    Result<int>res;
    QSqlQuery query;
    query.prepare("INSERT INTO product (productName, unitType, price) VALUES (:productName, :unitType, :price)");
    query.bindValue(":productName", p.productName);
    query.bindValue(":unitType", p.unitType);
    query.bindValue(":price", p.price);

    if( query.exec() ){
        res.res = result::SUCCESS;
        query.first();
        res.data = query.lastInsertId().toInt();
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertProduct: " + query.lastError().text();
    qDebug() << "ERROR insertProduct: " << query.lastError().text();
    return res;
}

Result<bool> ProductService::deleteProduct(ProductDto p){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("DELETE FROM product WHERE id = :id");
    query.bindValue(":id", p.id);
    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR deleteProduct: " + query.lastError().text();
    qDebug() << "ERROR deleteProduct: " << query.lastError().text();
    return res;
}

Result<ProductDto> ProductService::getProductByID(ProductDto p){
    Result<ProductDto> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM product WHERE id = :id");
    query.bindValue(":id", p.id);
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "ERROR getProductByID:" + query.lastError().text();
        qDebug() << "ERROR getProductByID:" << query.lastError().text();
        return res;
    }

    if( query.next() ){
        res.res = result::SUCCESS;
        res.data =  ProductDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toDouble());
        return res;
    }
    res.res = RECORD_NOT_FOUND;
    return res;
}

Result<QList<ProductDto>> ProductService::getAllProduct(){
    Result<QList<ProductDto>> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM product ORDER BY productName");
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "ERROR getAllProduct:" + query.lastError().text();
        qDebug() << "ERROR getAllProduct:" << query.lastError().text();
        return res;
    }

    QList<ProductDto>ret;
    while( query.next() ){
        ret << ProductDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toDouble());
    }
    res.res = result::SUCCESS;
    res.data = ret;
    return res;
}

Result<ProductDto> ProductService::getProductByName(QString name)
{
    Result<ProductDto> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM product WHERE productName = :name");
    query.bindValue(":name", name);
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = query.lastError().text();
        return res;
    }
    qDebug() << "noombre: " << name;
    if( !query.next() ){
        res.res = RECORD_NOT_FOUND;
        return res;
    }
    res.res = SUCCESS;
    res.data = ProductDto(query.value(0).toInt(),query.value(1).toString(),query.value(2).toInt(),query.value(3).toDouble());
    return res;
}


Result<bool> ProductService::updateProduct(ProductDto p){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("UPDATE product SET productName=:productName, unitType=:unitType, price=:price  WHERE id=:id");
    query.bindValue(":productName", p.productName);
    query.bindValue(":unitType", p.unitType);
    query.bindValue(":price", p.price);
    query.bindValue(":id", p.id);
    if( query.exec() ){
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR updateProductbyID: " + query.lastError().text();
    qDebug() << "ERROR updateProductbyID: " << query.lastError().text();
    return res;
}

Result<double> ProductService::getPrice(int idProduct){
    Result<double> res;
    res.data = 0;
    auto p = getProductByID(ProductDto(idProduct,"",0,0)).data;
    res.data = p.price;
    return res;
}

Result<QStringList> ProductService::getAllProductsToString()
{
    Result<QStringList> res;
    Result<QList<ProductDto>> r = getAllProduct();
    if( r.res == FAIL ){
        res.res = FAIL;
        res.msg = r.msg;
        return res;
    }
    res.res = r.res;
    foreach (auto i, r.data) {
        res.data << i.productName;
    }
    return res;
}
