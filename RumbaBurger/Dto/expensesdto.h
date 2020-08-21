#ifndef EXPENSESDTO_H
#define EXPENSESDTO_H
#include <QString>

class ExpensesDto
{
public:
    ExpensesDto();
    ExpensesDto(int _id, QString _description, double _price);
    int id;
    QString description;
    double price;
};

#endif // EXPENSESDTO_H
