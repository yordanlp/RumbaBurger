#include "orderdto.h"

OrderDto::OrderDto()
{

}

OrderDto::OrderDto(int _id, QDate _date, double _total, double _profit, int _payed, int _orderNumber, double _inversion){
    id = _id;
    date = _date;
    total = _total;
    payed = _payed;
    profit = _profit;
    orderNumber = _orderNumber;
    inversion = _inversion;
}
