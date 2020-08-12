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
#include <bits/stdc++.h>
#include <dishamountdto.h>
#include "productdto.h"
using namespace std;

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
    Result<double>totalToPay( QList<DishAmountDto> );
    Result<double>getPrice(int idDish);
    Result<bool> discountProductFromDish( int idDish, double amount, bool type );

};

#endif // DISHSERVICE_H
