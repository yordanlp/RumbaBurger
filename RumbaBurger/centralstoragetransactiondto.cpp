#include "centralstoragetransactiondto.h"

centralStorageTransactionDto::centralStorageTransactionDto()
{

}

centralStorageTransactionDto::centralStorageTransactionDto(int _id, bool _type, double _amount, int _idProduct, QDate _date,int _idUser,double _price){
    id = _id;
    type = _type;
    amount = _amount;
    idProduct = _idProduct;
    date = _date;
    idUser = _idUser;
    price = _price;
}
