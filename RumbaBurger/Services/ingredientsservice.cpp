#include "ingredientsservice.h"

IngredientsService::IngredientsService()
{

}

Result<bool> IngredientsService::insertIngredient(IngredientsDto i){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("INSERT INTO ingredients (idDish, idProduct, amount) VALUES (:idDish, :idProduct, :amount)");
    query.bindValue(":idDish", i.idDish);
    query.bindValue(":idProduct", i.idProduct);
    query.bindValue(":amount", i.amount);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertIngredient: " + query.lastError().text();
    qDebug() << "ERROR insertIngredient: " << query.lastError().text();
    return res;
}

Result<bool> IngredientsService::deleteIngredient(IngredientsDto i){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("DELETE FROM ingredients WHERE idDish = :idDish AND idProduct=:idProduct");
    query.bindValue(":idDish", i.idDish);
    query.bindValue(":idProduct", i.idProduct);
    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR deleteIngredient: " + query.lastError().text();
    qDebug() << "ERROR deleteIngredient: " << query.lastError().text();
    return res;
}

Result<QList<IngredientsDto>> IngredientsService::getDishByProductId(IngredientsDto i){
    Result<QList<IngredientsDto>>res;
    QSqlQuery query;
    query.prepare("SELECT * FROM ingredients WHERE idProduct=:idProduct");
    query.bindValue(":idProduct", i.idProduct);
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "ERROR getDishByProductId:" + query.lastError().text();
        qDebug() << "ERROR getDishByProductId:" << query.lastError().text();
        return res;
    }

    QList<IngredientsDto>ret;
    while( query.next() ){
        ret << IngredientsDto(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toDouble());
    }
    res.res = result::SUCCESS;
    res.data = ret;
    return res;
}

Result<QList<IngredientsDto>> IngredientsService::getIngredientsByDishId(IngredientsDto i){
    Result<QList<IngredientsDto>> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM ingredients WHERE idDish=:idDish");
    query.bindValue(":idDish", i.idDish);
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "ERROR getIngredientsByDishId:" + query.lastError().text();
        qDebug() << "ERROR getIngredientsByDishId:" << query.lastError().text();
        return res;
    }

    QList<IngredientsDto>ret;
    while( query.next() ){
        ret << IngredientsDto(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toDouble());
    }
    res.res = result::SUCCESS;
    res.data = ret;
    return res;
}


