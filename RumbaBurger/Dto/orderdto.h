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
    double inversion;
    int payed;
    int orderNumber;

    OrderDto();
    OrderDto( int _id, QDate _date, double _total, double _profit, int _payed, int _orderNumber, double _inversion );
};

#endif // ORDERDTO_H
