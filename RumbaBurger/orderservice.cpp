#include "orderservice.h"

OrderService::OrderService()
{

}

Result<bool> OrderService::deleteOrder(OrderDto o){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("DELETE FROM 'order' WHERE id = :id");
    query.bindValue(":id", o.id);
    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR deleteOrder: " + query.lastError().text();
    qDebug() << "ERROR deleteOrder: " << query.lastError().text();
    return res;
}

Result<bool> OrderService::insertOrder(OrderDto o){
    QSqlQuery query;
    Result<bool> res;
    query.prepare("INSERT INTO 'order' (date, total, payed) VALUES (:date,:total,:payed)");
    query.bindValue(":date", o.date.toString(Qt::ISODate));
    query.bindValue(":total", o.total);
    query.bindValue(":payed", o.payed);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertOrder: " + query.lastError().text();
    qDebug() << "ERROR insertOrder: " << query.lastError().text();
    return res;
}


Result<bool> OrderService::updateOrder(OrderDto o){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("UPDATE 'order' SET date=:date, total=:total, payed=:payed  WHERE id=:id");
    query.bindValue(":date", o.date.toString(Qt::ISODate));
    query.bindValue(":total", o.total);
    query.bindValue(":payed", o.payed);
    query.bindValue(":id", o.id);
    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR updateOrder: " + query.lastError().text();
    qDebug() << "ERROR updateOrder: " << query.lastError().text();
    return res;
}
