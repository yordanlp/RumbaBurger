#include "dishservice.h"

DishService::DishService()
{

}

bool DishService::insertDish(DishDto d){
    QSqlQuery query;
    query.prepare("INSERT INTO dish (dishName, description, price) VALUES (:dishName, :description, :price)");
    query.bindValue(":dishName", d.dishname);
    query.bindValue(":description", d.description);
    query.bindValue(":price", d.price);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertDish: " << query.lastError().text();
    return false;
}

bool DishService::deleteDish(DishDto d){
    QSqlQuery query;
    query.prepare("DELETE FROM dish WHERE id = :id");
    query.bindValue(":id", d.id);
    if( query.exec() ) return true;
    qDebug() << "ERROR deleteDish: " << query.lastError().text();
    return false;
}

DishDto DishService::getDishById(DishDto d){
    QSqlQuery query;
    query.prepare("SELECT * FROM dish WHERE id = :id");
    query.bindValue(":id", d.id);
    if( !query.exec() ){
        qDebug() << "ERROR getDishById:" << query.lastError().text();
        return DishDto(-1,"","",-1);
    }

    query.next();
    return DishDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toDouble());
}

QList<DishDto> DishService::getAllDish(){
    QSqlQuery query;
    query.prepare("SELECT * FROM dish");
    if( !query.exec() ){
        qDebug() << "ERROR DishService:" << query.lastError().text();
        return QList<DishDto>();
    }

    QList<DishDto>ret;
    while( query.next() ){
        ret << DishDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toDouble());
    }
    return ret;
}
