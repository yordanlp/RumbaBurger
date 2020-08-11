#ifndef INGREDIENTSSERVICE_H
#define INGREDIENTSSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "ingredientsdto.h"

class IngredientsService
{
public:
    IngredientsService();
    bool insertIngredient( IngredientsDto );
    bool deleteIngredient( IngredientsDto );
    QList<IngredientsDto> getIngredientsByDishId(IngredientsDto);
    QList<IngredientsDto> getDishByProductId(IngredientsDto);
    bool updateIngredient( IngredientsDto );
};

#endif // INGREDIENTSSERVICE_H
