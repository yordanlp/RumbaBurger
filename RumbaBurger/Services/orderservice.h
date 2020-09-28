#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <Dto/orderdto.h>
#include "result.h"
#include "ingredientsservice.h"
#include "Dto/ingredientsdto.h"
#include "Dto/orderdishdto.h"
#include "dishservice.h"
#include "orderdishservice.h"

class OrderService
{
public:
    OrderService();
    Result<int> insertOrder( OrderDto );
    Result<bool> deleteOrder( OrderDto );
    Result<QList<OrderDto>> getOrderbyDate( QDate start, QDate end );
    Result<bool> updateOrder( OrderDto );
    Result<bool> restoreIngredientsFromDishes(int idOrder);
    Result<bool> existOrderNumber(int orderNumber, QDate date );
    Result<QStringList> validateDishes( QList<DishAmountDto> L );
    Result<OrderDto> getOrderByOrderNumberAndDate( int orderNumber, QDate date );
};

#endif // ORDERSERVICE_H
