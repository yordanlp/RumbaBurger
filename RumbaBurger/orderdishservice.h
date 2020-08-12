#ifndef ORDERDISHSERVICE_H
#define ORDERDISHSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "orderdishdto.h"
#include "result.h"

class OrderDishService
{
public:
    OrderDishService();
    Result<bool> insertOrderDish(OrderDishDto);
    Result<bool> deleteOrderDish(OrderDishDto);

};

#endif // ORDERDISHSERVICE_H
