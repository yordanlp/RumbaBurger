#include "ingredientsservice.h"

IngredientsService::IngredientsService()
{

}

bool IngredientsService::insertIngredient(IngredientsDto i){
    QSqlQuery query;
    query.prepare("INSERT INTO ingredients (idDish, idProduct, amount) VALUES (:idDish, :idProduct, :amount)");
    query.bindValue(":idDish", i.idDish);
    query.bindValue(":idProduct", i.idProduct);
    query.bindValue(":amount", i.amount);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertIngredient: " << query.lastError().text();
    return false;
}

bool IngredientsService::deleteIngredient(IngredientsDto i){
    QSqlQuery query;
    query.prepare("DELETE FROM ingredients WHERE idDish = :idDish AND idProduct=:idProduct");
    query.bindValue(":idDish", i.idDish);
    query.bindValue(":idProduct", i.idProduct);
    if( query.exec() ) return true;
    qDebug() << "ERROR deleteIngredient: " << query.lastError().text();
    return false;
}

QList<IngredientsDto> IngredientsService::getDishByProductId(IngredientsDto i){
    QSqlQuery query;
    query.prepare("SELECT * FROM ingredients WHERE idProduct=:idProduct");
    query.bindValue(":idProduct", i.idProduct);
    if( !query.exec() ){
        qDebug() << "ERROR getDishByProductId:" << query.lastError().text();
        return QList<IngredientsDto>();
    }

    QList<IngredientsDto>ret;
    while( query.next() ){
        ret << IngredientsDto(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toDouble());
    }
    return ret;
}

QList<IngredientsDto> IngredientsService::getIngredientsByDishId(IngredientsDto i){
    QSqlQuery query;
    query.prepare("SELECT * FROM ingredients WHERE idDish=:idDish");
    query.bindValue(":idDish", i.idDish);
    if( !query.exec() ){
        qDebug() << "ERROR getIngredientsByDishId:" << query.lastError().text();
        return QList<IngredientsDto>();
    }

    QList<IngredientsDto>ret;
    while( query.next() ){
        ret << IngredientsDto(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toDouble());
    }
    return ret;
}


