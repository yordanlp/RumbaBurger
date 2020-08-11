#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <orderdto.h>


class OrderService
{
public:
    OrderService();
    bool insertOrder( OrderDto );
    bool deleteOrder( OrderDto );
    QList<OrderDto> getOrderbyDate( QDate start, QDate end );
    bool updateOrder( OrderDto );
};

#endif // ORDERSERVICE_H
