#ifndef EXPENSESDTO_H
#define EXPENSESDTO_H
#include <QString>
#include <QtCore>

class ExpensesDto
{
public:
    ExpensesDto();
    ExpensesDto(int _id, QString _description, double _price, QDate _date);
    int id;
    QString description;
    double price;
    QDate date;
};

#endif // EXPENSESDTO_H
