#ifndef STORAGETRANSACTIONDTO_H
#define STORAGETRANSACTIONDTO_H
#include<QDate>

class storageTransactionDto
{
public:
    storageTransactionDto();
    storageTransactionDto(int _id,bool _type,double amount, int _idProduct, QDate _date,int _idUser,double _price);
    int id;
    bool type;
    double amount;
    int idProduct;
    QDate date;
    int idUser;
    double price;

};

#endif // STORAGETRANSACTIONDTO_H
