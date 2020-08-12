#include "orderdishservice.h"

OrderDishService::OrderDishService()
{

}

Result<bool> OrderDishService::insertOrderDish(OrderDishDto od){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("INSERT INTO orderDish (idOrder, idDish, price, amount) VALUES (:idOrder, :idDish, :price, :amount)");
    query.bindValue(":idOrder", od.idOrder);
    query.bindValue(":idDish", od.idDish);
    query.bindValue(":price", od.price);
    query.bindValue(":amount", od.amount);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertOrderDish: " + query.lastError().text();
    qDebug() << "ERROR insertOrderDish: " << query.lastError().text();
    return res;
}


Result<bool> OrderDishService::deleteOrderDish(OrderDishDto od){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("DELETE FROM orderDish WHERE idOrder = :idOrder AND idDish = :idDish");
    query.bindValue(":idOrder", od.idOrder);
    query.bindValue(":idDish", od.idDish);
    if( query.exec() ){
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR deleteOrderDish: " + query.lastError().text();
    qDebug() << "ERROR deleteOrderDish: " << query.lastError().text();
    return res;
}

