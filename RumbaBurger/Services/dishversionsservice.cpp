#include "dishversionsservice.h"
#include <Services/ingredientsservice.h>

DishVersionsService::DishVersionsService()
{

}

Result<bool> DishVersionsService::createVersion(DishDto dish){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("INSERT INTO dishVersions (id, dishName, description, price) VALUES (:id, :dishName, :description, :price)");
    query.bindValue(":id", dish.id);
    query.bindValue(":dishName", dish.dishname);
    query.bindValue(":description", dish.description);
    query.bindValue(":price", dish.price);

    if( !query.exec() ) {
        res.res = result::FAIL;
        return res;
    }

    res.res = SUCCESS;
    res.msg = "createVersion " + query.lastError().text();

    return res;
}

Result<DishDto> DishVersionsService::getDishById(int dishId)
{
    Result<DishDto>res;
    QSqlQuery query;
    query.prepare("SELECT * FROM dishVersions WHERE id = :id");
    query.bindValue(":id", dishId);
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "DishVersionsService ERROR getDishById:" + query.lastError().text();
        qDebug() << "DishVersionsService ERROR getDishById:" << query.lastError().text();
        return res;
    }

    if( query.next() ){
        res.res = result::SUCCESS;
        res.data = DishDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toDouble());
        return res;
    }
    res.res = RECORD_NOT_FOUND;
    return res;
}

Result<DishDto> DishVersionsService::getDishByOrderAndName(int orderId, QString dishName)
{
    Result<DishDto> res;
    QSqlQuery query;
    query.prepare("SELECT dishVersions.id, dishVersions.dishName, dishVersions.description, dishVersions.price FROM orderDish INNER JOIN dishVersions ON orderDish.idDish = dishVersions.id WHERE idOrder = :orderId AND dishName = :dishName");
    query.bindValue(":orderId", orderId);
    query.bindValue(":dishName", dishName);
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = "getDishByOrderAndName " + query.lastError().text();
        qDebug() << "getDishByOrderAndName " + query.lastError().text();
        return res;
    }
    if( !query.next() ){
        res.res = RECORD_NOT_FOUND;
        return res;
    }

    res.res = SUCCESS;
    res.data = DishDto(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(), query.value(3).toDouble());
    return res;
}


Result<double> DishVersionsService::productionCost(int idDish)
{
    IngredientsService ingredientsService;
    ProductService productService;
    auto L = ingredientsService.getIngredientsByDishId(IngredientsDto(idDish,0,0)).data;

    Result<double>res;
    double ret = 0;
    foreach (auto i, L) {
        ret += productService.getPrice(i.idProduct).data * i.amount;
    }

    res.data = ret;
    return res;
}
