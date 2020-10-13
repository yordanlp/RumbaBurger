#include "orderservice.h"
#include <Services/storageservice.h>
#include <Services/productservice.h>
#include <Services/dishversionsservice.h>

OrderService::OrderService()
{

}

Result<bool> OrderService::deleteOrder(OrderDto o){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("DELETE FROM 'order' WHERE id = :id");
    query.bindValue(":id", o.id);
    if( query.exec() ) {
        restoreIngredientsFromDishes(o.id);
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR deleteOrder: " + query.lastError().text();
    qDebug() << "ERROR deleteOrder: " << query.lastError().text();
    return res;
}

Result<QList<OrderDto> > OrderService::getOrderbyDate(QDate start, QDate end)
{
    Result<QList<OrderDto>> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM 'order' where date BETWEEN :inicial AND :final ORDER BY date DESC, orderNumber DESC");
    query.bindValue(":inicial", start.toString(Qt::ISODate));
    query.bindValue(":final", end.toString(Qt::ISODate));
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = "getOrderbyDate " + query.lastError().text();
        return res;
    }
    res.res = SUCCESS;
    while (query.next()) {
        res.data << OrderDto(query.value(0).toInt(), query.value(2).toDate(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toInt(), query.value(1).toInt(), query.value(6).toDouble());
    }
    return res;
}

Result<int> OrderService::insertOrder(OrderDto o){
    QSqlQuery query;
    Result<int> res;
    query.prepare("INSERT INTO 'order' (orderNumber, date, total, profit, inversion, payed) VALUES (:orderNumber, :date,:total, :profit, :inversion, :payed)");
    query.bindValue(":date", o.date.toString(Qt::ISODate));
    query.bindValue(":total", o.total);
    query.bindValue(":profit", o.profit);
    query.bindValue(":inversion", o.inversion);
    query.bindValue(":payed", o.payed);
    query.bindValue(":orderNumber", o.orderNumber);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        query.first();
        res.data = query.lastInsertId().toInt();
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
    query.prepare("UPDATE 'order' SET date=:date, total=:total, profit=:profit, inversion=:inversion, payed=:payed  WHERE id=:id");
    query.bindValue(":date", o.date.toString(Qt::ISODate));
    query.bindValue(":total", o.total);
    query.bindValue(":payed", o.payed);
    query.bindValue(":profit", o.profit);
    query.bindValue(":inversion", o.inversion);
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

Result<bool> OrderService::restoreIngredientsFromDishes(int idOrder){
    OrderDishService orderDishService;
    DishService dishService;
    auto dishes = orderDishService.getDishesByOrderId(idOrder).data;
    foreach (auto d, dishes) {
        dishService.discountProductFromDish(d.idDish, d.amount, 1);
    }
    Result<bool> res;
    res.res = SUCCESS;
    return res;
}

Result<bool> OrderService::existOrderNumber(int orderNumber, QDate date)
{
    Result<bool> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM 'order' WHERE orderNumber=:orderNumber AND date=:date");
    query.bindValue(":orderNumber", orderNumber);
    query.bindValue(":date",date.toString(Qt::ISODate));
    qDebug() << orderNumber << date.toString(Qt::ISODate);
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = "existOrderNumber " + query.lastError().text();
        qDebug() << "existOrderNumber" << query.lastError().text();
        return res;
    }
    res.res = SUCCESS;
    if( !query.next() )
        res.data = false;
    else {
        qDebug() << query.value(0).toInt() << query.value(1).toInt() << query.value(2).toString();
        res.data = true;
    }
    return res;
}

Result<QStringList> OrderService::validateDishes(QList<DishAmountDto> L)
{
    Result<QStringList> res;
    map<int, double>M;
    IngredientsService ingredientsService;
    storageService StorageService;
    ProductService productService;
    foreach (auto d, L) {
        auto is = ingredientsService.getIngredientsByDishId(IngredientsDto(d.idDish,0,0));
        foreach (auto i, is.data) {
            M[ i.idProduct ] += i.amount * d.amount;
        }
    }

    QStringList Li;
    res.res = SUCCESS;
    for( auto i : M ){
        int idProduct = i.first;
        double amount = i.second;
        auto product = StorageService.getStorageById(idProduct);
        if( amount > product.data.amount ){
            res.res = INSUFICIENT_AMOUNT;
            res.msg = "Cantidad insuficiente";
            Li << productService.getProductByID(ProductDto(idProduct,"",0,0)).data.productName + " => En Almacén: " + QString::number(product.data.amount) + " Falta: " + QString::number(amount - product.data.amount);
        }
    }
    res.data = Li;
    return res;
}

Result<OrderDto> OrderService::getOrderByOrderNumberAndDate(int orderNumber, QDate date)
{
    Result<OrderDto>res;
    QSqlQuery query;
    query.prepare("SELECT * FROM 'order' WHERE orderNumber=:orderNumber and date=:date ORDER BY date DESC, orderNumber DESC");
    query.bindValue(":orderNumber", orderNumber);
    query.bindValue(":date", date.toString(Qt::ISODate));
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = "getOrderByOrderNumberAndDate " + query.lastError().text();
        qDebug() << "getOrderByOrderNumberAndDate " + query.lastError().text();
        return res;
    }

    if( !query.next() )
        res.res = RECORD_NOT_FOUND;
    else{
        res.res = SUCCESS;
        res.data = OrderDto(query.value(0).toInt(), query.value(2).toDate(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toInt(), query.value(1).toInt(), query.value(6).toDouble());
    }
    return res;
}

Result<double> OrderService::getGanancia(int orderId){
    Result<double> res;
    /*DishService dishService;
    OrderDishService orderDishService;
    auto dishes = orderDishService.getDishesByOrderId(orderId);
    QList<DishAmountDto> L;
    foreach (auto d, dishes.data) {
        L << DishAmountDto( d.idDish, d.amount );
    }*/
    //res.data = dishService.totalProfit(L).data;
    res.data = getOrderById(orderId).data.profit;
    res.res = SUCCESS;
    return res;
}

Result<double> OrderService::calcularInversion( int orderId ){
    Result<double> res;
    DishVersionsService dishVersionsService;
    OrderDishService orderDishService;
    auto dishes = orderDishService.getDishesByOrderId(orderId);
    QList<DishAmountDto> L;
    foreach (auto d, dishes.data) {
        res.data += dishVersionsService.productionCost(d.idDish).data * d.amount;
    }
    res.res = SUCCESS;
    return res;
}

Result<double> OrderService::getInversion(int orderId){
    Result<double> res;
    res.data = 0;
    /*DishService dishService;
    OrderDishService orderDishService;
    auto dishes = orderDishService.getDishesByOrderId(orderId);
    QList<DishAmountDto> L;
    foreach (auto d, dishes.data) {
        res.data += dishService.productionCost(d.idDish).data * d.amount;
    }
    res.res = SUCCESS;*/
    //res.data = getOrderById()
    res.data = getOrderById(orderId).data.inversion;
    return res;
}

Result<OrderDto> OrderService::getOrderById(int orderId)
{
    Result<OrderDto> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM 'order' WHERE id=:id");
    query.bindValue(":id", orderId);
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = "Error getOrderById " + query.lastError().text();
        qDebug() << "Error getOrderById " + query.lastError().text();
        return res;
    }

    if( !query.next() ){
        res.res = RECORD_NOT_FOUND;
        return res;
    }
    res.data = OrderDto(query.value(0).toInt(), query.value(2).toDate(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toInt(), query.value(1).toInt(), query.value(6).toDouble());
    res.res = SUCCESS;
    return res;
}
