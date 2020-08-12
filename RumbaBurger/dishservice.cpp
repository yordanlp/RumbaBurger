#include "dishservice.h"


DishService::DishService()
{

}

Result<bool> DishService::insertDish(DishDto d){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("INSERT INTO dish (dishName, description, price) VALUES (:dishName, :description, :price)");
    query.bindValue(":dishName", d.dishname);
    query.bindValue(":description", d.description);
    query.bindValue(":price", d.price);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertDish: " + query.lastError().text();
    qDebug() << "ERROR insertDish: " << query.lastError().text();
    return res;
}

Result<bool> DishService::deleteDish(DishDto d){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("DELETE FROM dish WHERE id = :id");
    query.bindValue(":id", d.id);
    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR deleteDish: " + query.lastError().text();
    qDebug() << "ERROR deleteDish: " << query.lastError().text();
    return res;
}

Result<DishDto> DishService::getDishById(DishDto d){
    Result<DishDto>res;
    QSqlQuery query;
    query.prepare("SELECT * FROM dish WHERE id = :id");
    query.bindValue(":id", d.id);
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "ERROR getDishById:" + query.lastError().text();
        qDebug() << "ERROR getDishById:" << query.lastError().text();
        return res;
    }

    res.res = result::SUCCESS;
    query.next();
    res.data = DishDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toDouble());
    return res;
}

Result<QList<DishDto>> DishService::getAllDish(){
    Result<QList<DishDto>> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM dish");
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "ERROR DishService:" + query.lastError().text();
        qDebug() << "ERROR DishService:" << query.lastError().text();
        return res;
    }

    QList<DishDto>ret;
    while( query.next() ){
        ret << DishDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toDouble());
    }
    res.data = ret;
    res.res = result::SUCCESS;
    return res;
}

Result<int> DishService::howManyDishes(int idDish){

    Result<int>res;
    IngredientsService ingredientsService;
    storageService StorageService;
    auto r = ingredientsService.getIngredientsByDishId(IngredientsDto(idDish,0,0));
    if( r.res == result::FAIL ){
        res.res = result::FAIL;
        res.msg = r.msg;
        return res;
    }

    auto L = r.data;

    int ret = 1 << 30;
    foreach (auto ingredient, L) {
        auto p = StorageService.getStorageById(ingredient.idProduct).data;
        int cantProd = 0;
        if( ingredient.amount > 0 )
            cantProd = p.amount / ingredient.amount;
        ret = min(ret, cantProd);
    }

    res.res = result::SUCCESS;
    res.data = ret;
    return res;
}

Result<double> DishService::getPrice(int idDish){
    Result<double> res;
    double price = getDishById(DishDto(idDish,"","",0)).data.price;
    res.data = price;
    return res;
}

Result<double> DishService::totalToPay(QList<DishAmountDto> L){
    Result<double> res;
    double total = 0;
    foreach (auto i, L) {
        total += getPrice(i.idDish).data * i.amount;
    }
    res.data = total;
    return res;
}

Result<bool> DishService::discountProductFromDish(int idDish, double amount, bool type){
    Result<bool>res;
    IngredientsService ingredientsService;
    storageService StorageService;

    auto products = ingredientsService.getIngredientsByDishId(IngredientsDto(idDish,0,0)).data;

    foreach (auto p, products) {
        StorageService.modifyStorage(p.idProduct, amount * p.amount, type);
    }

    return res;
}

