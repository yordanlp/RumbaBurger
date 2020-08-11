#ifndef ORDERDISHDTO_H
#define ORDERDISHDTO_H


class OrderDishDto
{
public:
    OrderDishDto();
    OrderDishDto(int _idOrder, int _idDish, double _price, double _amount);
    int idOrder, idDish;
    double price, amount;
};

#endif // ORDERDISHDTO_H
