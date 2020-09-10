#ifndef CENTRALSTORAGETRANSACTIONDTO_H
#define CENTRALSTORAGETRANSACTIONDTO_H
#include<QDate>

class centralStorageTransactionDto
{
public:
    centralStorageTransactionDto();
    centralStorageTransactionDto(int _id,bool _type,double amount, int _idProduct, QDate _date,int _idUser,double _price, double _merma);
    int id;
    bool type;
    double amount;
    int idProduct;
    QDate date;
    int idUser;
    double price;
    double merma;
};

#endif // CENTRALSTORAGETRANSACTIONDTO_H
