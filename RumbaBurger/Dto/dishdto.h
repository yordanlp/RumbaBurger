#ifndef DISHDTO_H
#define DISHDTO_H
#include <QString>

class DishDto
{
public:
    DishDto();
    int id;
    QString dishname;
    QString description;
    double price;
    DishDto(int _id, QString _dishName, QString _description, double _price);
};

#endif // DISHDTO_H
