#include "dishdto.h"

DishDto::DishDto()
{

}
DishDto::DishDto(int _id, QString _dishName, QString _description, double _price){
    id = _id;
    dishname = _dishName;
    description = _description;
    price = _price;
}
