#ifndef CENTRALSTORAGETRANSACTIONDTO_H
#define CENTRALSTORAGETRANSACTIONDTO_H
#include<QDate>

class centralStorageTransactionDto
{
public:
    centralStorageTransactionDto();
    centralStorageTransactionDto(int _id,int _type,double amount, int _idProduct, QDate _date,int _idUser,double _price, double _merma, double _aviable_in_local, double _aviable_in_central, QString _productname, int _unitType);
    int id;
    int type;
    double amount;
    int idProduct;
    QDate date;
    int idUser;
    double price;
    double merma;
    double aviable_in_local;
    double aviable_in_central;
    QString productName;
    int unitType;
};

#endif // CENTRALSTORAGETRANSACTIONDTO_H
