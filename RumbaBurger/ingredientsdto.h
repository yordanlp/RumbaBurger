#ifndef INGREDIENTSDTO_H
#define INGREDIENTSDTO_H


class IngredientsDto
{
public:
    IngredientsDto();
    IngredientsDto( int _idDish, int _idProduct, double _amount);
    int idDish, idProduct;
    double amount;
};

#endif // INGREDIENTSDTO_H
