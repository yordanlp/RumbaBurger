#include "ingredientsdto.h"

IngredientsDto::IngredientsDto()
{

}

IngredientsDto::IngredientsDto(int _idDish, int _idProduct, double _amount){
    idDish = _idDish;
    idProduct = _idProduct;
    amount = _amount;
}
