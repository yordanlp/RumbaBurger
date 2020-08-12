#ifndef DISHSERVICE_H
#define DISHSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "dishdto.h"
#include "ingredientsdto.h"
#include "ingredientsservice.h"
#include "storagedto.h"
#include "storageservice.h"

class DishService
{
public:
    DishService();
    bool insertDish( DishDto );
    bool deleteDish( DishDto );
    DishDto getDishById( DishDto );
    QList<DishDto> getAllDish();
    DishDto getDishByName( DishDto );
    int howManyDishes( int idDish );
private:
    IngredientsService ingredientsService;
    storageService StorageService;
};

#endif // DISHSERVICE_H
