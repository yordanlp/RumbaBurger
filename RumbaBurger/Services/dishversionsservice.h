#ifndef DISHVERSIONSSERVICE_H
#define DISHVERSIONSSERVICE_H
#include <Services/dishservice.h>
#include <Dto/dishdto.h>
#include <result.h>
#include <utiles.h>

class DishVersionsService
{
public:
    DishVersionsService();
    Result<bool> createVersion( DishDto dish );
    Result<DishDto> getDishById( int dishId );
    Result<DishDto> getDishByOrderAndName(int orderId, QString dishName);
};

#endif // DISHVERSIONSSERVICE_H
