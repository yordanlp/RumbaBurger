#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <orderdto.h>
#include "result.h"

class OrderService
{
public:
    OrderService();
    Result<bool> insertOrder( OrderDto );
    Result<bool> deleteOrder( OrderDto );
    Result<QList<OrderDto>> getOrderbyDate( QDate start, QDate end );
    Result<bool> updateOrder( OrderDto );
};

#endif // ORDERSERVICE_H
