#ifndef ORDERDTO_H
#define ORDERDTO_H
#include <QString>
#include <QDate>

class OrderDto
{
public:
    int id;
    QDate date;
    double total;
    double profit;
    int payed;

    OrderDto();
    OrderDto( int _id, QDate _date, double _total, double _profit, int _payed);
};

#endif // ORDERDTO_H
