#ifndef INGREDIENTSSERVICE_H
#define INGREDIENTSSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "ingredientsdto.h"
#include "result.h"


class IngredientsService
{
public:
    IngredientsService();
    Result<bool> insertIngredient( IngredientsDto );
    Result<bool> deleteIngredient( IngredientsDto );
    Result<QList<IngredientsDto>> getIngredientsByDishId(IngredientsDto);
    Result<QList<IngredientsDto>> getDishByProductId(IngredientsDto);
    Result<bool> updateIngredient( IngredientsDto );
};

#endif // INGREDIENTSSERVICE_H
