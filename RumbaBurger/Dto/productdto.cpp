#include "productdto.h"

ProductDto::ProductDto()
{

}

ProductDto::ProductDto(int _id, QString _productName, int _unitType, double _price){
    id = _id;
    productName = _productName;
    unitType = _unitType;
    price = _price;
}
