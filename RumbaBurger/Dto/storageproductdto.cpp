#include "storageproductdto.h"

StorageProductDto::StorageProductDto()
{

}

StorageProductDto::StorageProductDto(int _id, QString _name, double _amount, double _price, int unitType)
{
    id = _id;
    name = _name;
    amount = _amount;
    price = _price;
    this->unitType = unitType;
}
