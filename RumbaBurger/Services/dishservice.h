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
    Result<DishDto> insertDish( DishDto );
    Result<bool> deleteDish( DishDto );
    Result<DishDto> getDishById( DishDto );
    Result<QList<DishDto>> getAllDish();
    Result<DishDto> getDishByName( DishDto dish );
    //Result<int> howManyDishes( int idDish );
    Result<double>totalToPay( QList<DishAmountDto> );
    Result<double>getPrice(int idDish);
    Result<bool> discountProductFromDish(int idDish, double amount, int type );
    Result<double> totalProfit(QList<DishAmountDto>);
    Result<double> productionCost( int idDish );
    Result<double> getPrecioSugerido( int idDish );
    Result<double> getPrecioProduccion( int idDish );
    Result<QList<DishDto>> getDishBySearch( QString search );
    Result<double> getGanancia( int idDish );
    Result<int> getSalen( int idDish );
    Result<bool> hasIngredient( int idDish, int idProduct );
    Result<DishDto> updateDish( DishDto d );
    Result<bool> deleteIngredients( int idDish );
    Result<QStringList> getAllDishToString();
    Result<DishDto> getDishByOrderAndName( int orderId, QString dishName );
};

#endif // DISHSERVICE_H
