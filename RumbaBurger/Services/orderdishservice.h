#ifndef ORDERDISHSERVICE_H
#define ORDERDISHSERVICE_H
#include "result.h"
#include "Dto/orderdishdto.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "dishservice.h"
#include "Dto/orderdto.h"
#include <QDate>
#include "orderservice.h"


class OrderDishService
{
public:
    OrderDishService();
    Result<bool> insertOrderDish(OrderDishDto);
    Result<bool> deleteOrderDish(OrderDishDto);
    Result<bool> insertOrderDishes( QList<DishAmountDto>, bool );
    Result<QList<OrderDishDto>>getDishesByOrderId( int idOrder );
};

#endif // ORDERDISHSERVICE_H
