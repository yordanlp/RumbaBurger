#include "transactiondto.h"

TransactionDto::TransactionDto()
{

}

TransactionDto::TransactionDto(int _id, operaciones _type, origen _origin, double _amount, int _idProduct, QDate _date, int _idUser, double _price, double _merma, double _aviable_in_local, double _aviable_in_central, QString _productName, int _unitType)
{
    id = _id;
    type = _type;
    origin = _origin;
    amount = _amount;
    idProduct = _idProduct;
    date = _date;
    idUser = _idUser;
    price = _price;
    merma = _merma;
    aviable_in_central = _aviable_in_central;
    aviable_in_local = _aviable_in_local;
    productName = _productName;
    unitType = _unitType;
}
