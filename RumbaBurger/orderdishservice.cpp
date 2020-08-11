#include "orderdishservice.h"

OrderDishService::OrderDishService()
{

}

bool OrderDishService::insertOrderDish(OrderDishDto od){
    QSqlQuery query;
    query.prepare("INSERT INTO orderDish (idOrder, idDish, price, amount) VALUES (:idOrder, :idDish, :price, :amount)");
    query.bindValue(":idOrder", od.idOrder);
    query.bindValue(":idDish", od.idDish);
    query.bindValue(":price", od.price);
    query.bindValue(":amount", od.amount);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertOrderDish: " << query.lastError().text();
    return false;
}


bool OrderDishService::deleteOrderDish(OrderDishDto od){
    QSqlQuery query;
    query.prepare("DELETE FROM orderDish WHERE idOrder = :idOrder AND idDish = :idDish");
    query.bindValue(":idOrder", od.idOrder);
    query.bindValue(":idDish", od.idDish);
    if( query.exec() ) return true;
    qDebug() << "ERROR deleteOrderDish: " << query.lastError().text();
    return false;
}

