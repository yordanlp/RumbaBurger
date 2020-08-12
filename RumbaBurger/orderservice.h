#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <orderdto.h>
#include "result.h"
#include "ingredientsservice.h"
#include "ingredientsdto.h"
#include "orderdishdto.h"
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
};

#endif // ORDERSERVICE_H
