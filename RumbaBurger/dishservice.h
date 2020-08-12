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
#include "result.h"

class DishService
{
public:
    DishService();
    Result<bool> insertDish( DishDto );
    Result<bool> deleteDish( DishDto );
    Result<DishDto> getDishById( DishDto );
    Result<QList<DishDto>> getAllDish();
    Result<DishDto> getDishByName( DishDto );
    Result<int> howManyDishes( int idDish );
private:
    IngredientsService ingredientsService;
    storageService StorageService;
};

#endif // DISHSERVICE_H
