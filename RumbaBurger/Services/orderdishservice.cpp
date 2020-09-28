#include "orderdishservice.h"


OrderDishService::OrderDishService()
{

}

Result<bool> OrderDishService::insertOrderDish(OrderDishDto od){
    Result<bool>res;
    DishService dishService;
    QSqlQuery query;
    query.prepare("INSERT INTO orderDish (idOrder, idDish, price, amount) VALUES (:idOrder, :idDish, :price, :amount)");
    query.bindValue(":idOrder", od.idOrder);
    query.bindValue(":idDish", od.idDish);
    query.bindValue(":price", od.price);
    query.bindValue(":amount", od.amount);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        res.msg = dishService.discountProductFromDish(od.idDish, od.amount, -1).msg;
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
    DishService dishService;
    query.prepare("DELETE FROM orderDish WHERE idOrder = :idOrder AND idDish = :idDish");
    query.bindValue(":idOrder", od.idOrder);
    query.bindValue(":idDish", od.idDish);
    if( query.exec() ){
        res.res = result::SUCCESS;
        res.msg = dishService.discountProductFromDish(od.idDish, od.amount, 1).msg;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR deleteOrderDish: " + query.lastError().text();
    qDebug() << "ERROR deleteOrderDish: " << query.lastError().text();
    return res;
}

Result<bool> OrderDishService::insertOrderDishes(int orderId, QList<DishAmountDto> L){
    DishService dishService;
    foreach (auto d, L) {
        OrderDishDto od;
        od.idDish = d.idDish;
        od.idOrder = orderId;
        od.amount = d.amount;
        od.price = dishService.getPrice(d.idDish).data;
        insertOrderDish(od);
    }
    Result<bool>res;
    res.res = result::SUCCESS;
    return res;
}

Result<QList<OrderDishDto>> OrderDishService::getDishesByOrderId(int idOrder){
    Result<QList<OrderDishDto>>res;
    QSqlQuery query;
    query.prepare("SELECT * FROM orderDish WHERE idOrder = :idOrder");
    query.bindValue( ":idOrder", idOrder );
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = "Error getDishesByOrderId: " + query.lastError().text();
        return res;
    }

    QList<OrderDishDto>ret;
    while (query.next()) {
        OrderDishDto od(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toDouble(), query.value(3).toInt());
        ret << od;
    }
    res.res = SUCCESS;
    res.data = ret;
    return res;
}
