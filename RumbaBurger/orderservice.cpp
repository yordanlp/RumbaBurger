#include "orderservice.h"

OrderService::OrderService()
{

}

bool OrderService::deleteOrder(OrderDto o){
    QSqlQuery query;
    query.prepare("DELETE FROM 'order' WHERE id = :id");
    query.bindValue(":id", o.id);
    if( query.exec() ) return true;
    qDebug() << "ERROR deleteOrder: " << query.lastError().text();
    return false;
}

bool OrderService::insertOrder(OrderDto o){
    QSqlQuery query;
    query.prepare("INSERT INTO 'order' (date, total, payed) VALUES (:date,:total,:payed)");
    query.bindValue(":date", o.date.toString(Qt::ISODate));
    query.bindValue(":total", o.total);
    query.bindValue(":payed", o.payed);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertOrder: " << query.lastError().text();
    return false;
}


bool OrderService::updateOrder(OrderDto o){
    QSqlQuery query;
    query.prepare("UPDATE 'order' SET date=:date, total=:total, payed=:payed  WHERE id=:id");
    query.bindValue(":date", o.date.toString(Qt::ISODate));
    query.bindValue(":total", o.total);
    query.bindValue(":payed", o.payed);
    query.bindValue(":id", o.id);
    if( query.exec() ) return true;
    qDebug() << "ERROR updateOrder: " << query.lastError().text();
    return false;
}
