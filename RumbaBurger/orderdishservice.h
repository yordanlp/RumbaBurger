#ifndef ORDERDISHSERVICE_H
#define ORDERDISHSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "orderdishdto.h"

class OrderDishService
{
public:
    OrderDishService();
    bool insertOrderDish(OrderDishDto);
    bool deleteOrderDish(OrderDishDto);

};

#endif // ORDERDISHSERVICE_H
