#include "expensesdto.h"

ExpensesDto::ExpensesDto()
{

}
ExpensesDto::ExpensesDto(int _id, QString _description, double _price, QDate _date){
    id = _id;
    description = _description;
    price = _price;
    date = _date;
}
