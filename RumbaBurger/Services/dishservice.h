#ifndef DISHSERVICE_H
#define DISHSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "Dto/dishdto.h"
#include "Dto/ingredientsdto.h"
#include "ingredientsservice.h"
#include "Dto/storagedto.h"
#include "storageservice.h"
#include "result.h"
#include <bits/stdc++.h>
#include <Dto/dishamountdto.h>
#include "Dto/productdto.h"
#include "productservice.h"
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
    Result<double> totalProfit(QList<DishAmountDto>);
    Result<double> individualProfit( int idDish );
    Result<double> productionCost( int idDish );

};

#endif // DISHSERVICE_H
