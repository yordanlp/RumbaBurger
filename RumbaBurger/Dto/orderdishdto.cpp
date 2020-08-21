#include "orderdishdto.h"

OrderDishDto::OrderDishDto()
{

}
OrderDishDto::OrderDishDto(int _idOrder, int _idDish, double _price, double _amount){
    idOrder = _idOrder;
    idDish = _idDish;
    price = _price;
    amount = _amount;

}
