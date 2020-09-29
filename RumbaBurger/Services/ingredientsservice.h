#ifndef INGREDIENTSSERVICE_H
#define INGREDIENTSSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "Dto/ingredientsdto.h"
#include "result.h"
#include <Dto/dishdto.h>


class IngredientsService
{
public:
    IngredientsService();
    Result<DishDto> insertIngredient(IngredientsDto , bool mkcopy = true);
    Result<DishDto> deleteIngredient( IngredientsDto );
    Result<QList<IngredientsDto>> getIngredientsByDishId(IngredientsDto);
    Result<QList<IngredientsDto>> getDishByProductId(IngredientsDto);
    Result<bool> updateIngredient( IngredientsDto );
};

#endif // INGREDIENTSSERVICE_H
