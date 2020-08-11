#ifndef DISHSERVICE_H
#define DISHSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "dishdto.h"

class DishService
{
public:
    DishService();
    bool insertDish( DishDto );
    bool deleteDish( DishDto );
    DishDto getDishById( DishDto );
    QList<DishDto> getAllDish();
    DishDto getDishByName( DishDto );
};

#endif // DISHSERVICE_H
