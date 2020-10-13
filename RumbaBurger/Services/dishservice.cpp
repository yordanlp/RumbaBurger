#include "dishservice.h"
#include <Services/dishversionsservice.h>


DishService::DishService()
{

}

Result<DishDto> DishService::insertDish(DishDto d){
    Result<DishDto> res;
    QSqlQuery query;

    int parent = d.id;
    res.data = d;

    query.prepare("INSERT INTO dish (dishName, description, price) VALUES (:dishName, :description, :price)");
    query.bindValue(":dishName", d.dishname);
    query.bindValue(":description", d.description);
    query.bindValue(":price", d.price);


    if( query.exec() ) {

        res.res = result::SUCCESS;
        res.data.id = query.lastInsertId().toInt();

        DishVersionsService dishVersiosService;
        dishVersiosService.createVersion(res.data);

        if( parent >= 0 ){
            IngredientsService ingredientsService;
            IngredientsDto idto;
            idto.idDish = parent;
            auto ing = ingredientsService.getIngredientsByDishId(idto);
            foreach (auto i, ing.data) {
                auto idto = i;
                idto.idDish = res.data.id;
                ingredientsService.insertIngredient( idto, false );
            }
        }

        if( parent >= 0 )
            deleteDish( d );

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

    //deleteIngredients(d.id);

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

    if( query.next() ){
        res.res = result::SUCCESS;
        res.data = DishDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toDouble());
        return res;
    }
    res.res = RECORD_NOT_FOUND;
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

Result<DishDto> DishService::getDishByName(DishDto dish)
{
    Result<DishDto> res;
    QSqlQuery query;
    QString name = dish.dishname;
    query.prepare("SELECT * FROM dish WHERE dishName = :name");
    query.bindValue(":name",dish.dishname);
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "ERROR getDishByName:" + query.lastError().text();
        qDebug() << "ERROR getDishByName:" << query.lastError().text();
        return res;
    }

    if( !query.next() ){
        res.res = RECORD_NOT_FOUND;
        return res;
    }

    res.data = DishDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toDouble());
    res.res = SUCCESS;
    return res;
}

/*Result<int> DishService::howManyDishes(int idDish){

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
}*/

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

Result<bool> DishService::discountProductFromDish(int idDish, double amount, int type){
    Result<bool>res;
    IngredientsService ingredientsService;
    storageService StorageService;

    auto products = ingredientsService.getIngredientsByDishId(IngredientsDto(idDish,0,0)).data;

    foreach (auto p, products) {
        StorageService.updateStorage(p.idProduct, amount * p.amount, type);
    }

    return res;
}

Result<double> DishService::totalProfit(QList<DishAmountDto> L){
    Result<double>res;
    res.data = 0;
    double ret = 0;
    foreach (auto d, L) {
        ret += getGanancia(d.idDish).data * d.amount;
    }

    res.data = ret;
    return res;
}


Result<double> DishService::productionCost(int idDish){
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

Result<double> DishService::getPrecioSugerido(int idDish)
{
    Result<double>res;
    res.data = 0;
    double precioProd = getPrecioProduccion(idDish).data;
    double ps = (precioProd * utiles::GANANCIA + precioProd)/(1-utiles::IMPUESTO);
    res.data = ps;
    res.res = SUCCESS;
    return res;
}

Result<double> DishService::getPrecioProduccion(int idDish)
{
    Result<double>res;
    res.data = 0;
    IngredientsService ingredientsService;
    ProductService productService;
    auto ingredients = ingredientsService.getIngredientsByDishId(IngredientsDto(idDish,0,0));
    double price = 0;
    foreach (auto i, ingredients.data) {
        auto precio = productService.getPrice(i.idProduct).data;
        price += i.amount * precio;
    }
    res.data = price;
    res.res = SUCCESS;
    return res;
}

Result<QList<DishDto> > DishService::getDishBySearch(QString search)
{
    qDebug() << "search:" << search;
    Result<QList<DishDto>> res;
    QString q = "SELECT * FROM dish WHERE lower(dishName) LIKE :search";
    QSqlQuery query;
    query.prepare(q);
    query.bindValue(":search", search);
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = query.lastError().text();
        qDebug() << "Error getDishBySearch" <<  query.lastError().text();
        qDebug() << query.lastQuery();
        return res;
    }
    qDebug() << "exito";
    res.res = SUCCESS;
    QList<DishDto> L;
    while( query.next() ){
        L << DishDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toDouble());
    }
    res.data = L;
    return res;
}

Result<double> DishService::getGanancia(int idDish)
{
    Result<double> res;
    res.data = 0;
    double ganancia = 0;
    double precio = getPrice(idDish).data;
    ganancia = precio - getPrecioProduccion(idDish).data;
    res.res = SUCCESS;
    res.data = ganancia;
    return res;
}


Result<int> DishService::getSalen(int idDish)
{
    Result<int>res;
    storageService StorageService;
    IngredientsService ingredientsService;
    auto ingredients = ingredientsService.getIngredientsByDishId(IngredientsDto(idDish, 0,0));
    int salen = numeric_limits<int>::max();
    foreach (auto i, ingredients.data) {
        int cantidad = 0;
        if( i.amount > 0 )
            cantidad = StorageService.getStorageById(i.idProduct).data.amount / i.amount;
        salen = min(salen, cantidad);
    }
    res.data = salen;
    return res;
}

Result<bool> DishService::hasIngredient(int idDish, int idProduct)
{
    Result<bool>res;
    QSqlQuery query;
    query.prepare("SELECT * FROM ingredients WHERE idDish = :idDish AND idProduct = :idProduct");
    query.bindValue(":idDish", idDish);
    query.bindValue(":idProduct", idProduct);
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = "hasIngredient " + query.lastError().text();
        qDebug() << "hasIngredient " + query.lastError().text();
        return res;
    }

    if( !query.next() ){
        res.data = false;
        res.res = RECORD_NOT_FOUND;
        return res;
    }
    res.res = SUCCESS;
    res.data = true;
    return res;

}

Result<DishDto> DishService::updateDish(DishDto d)
{
    Result<DishDto>res;
    auto ins = insertDish( d );
    res.data = ins.data;
    res.res = SUCCESS;
    return res;
}

Result<bool> DishService::deleteIngredients(int idDish)
{
    Result<bool> res;
    QSqlQuery query;
    query.prepare("DELETE FROM ingredients WHERE idDish = :idDish");
    query.bindValue(":idDish", idDish);
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = "deleteIngredients " + query.lastError().text();
        qDebug() << "deleteIngredients " + query.lastError().text();
        return res;
    }
    res.res = SUCCESS;
    return res;
}

Result< QStringList > DishService::getAllDishToString()
{
    Result<QStringList> res;
    QStringList L;
    auto r = getAllDish();
    foreach (auto d, r.data) {
        L << d.dishname;
    }
    res.data = L;
    res.res = SUCCESS;
    return res;
}


