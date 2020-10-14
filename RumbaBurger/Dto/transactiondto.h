#ifndef TRANSACTIONDTO_H
#define TRANSACTIONDTO_H

#include <QDate>

enum origen { CENTRAL, LOCAL, ALL };
enum operaciones { EXTRACCION, COMPRA, MOVIMIENTO, ALL_OPS };

class TransactionDto
{
public:
    TransactionDto();
    TransactionDto(int _id, operaciones _type, origen _origin,
                    double _amount, int _idProduct, QDate _date,
                    int _idUser, double _price, double _merma,
                    double _aviable_in_local, double _aviable_in_central, QString _productName = "",
                    int _unitType = 0 );
    int id;
    operaciones type;
    origen origin;
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

#endif // TRANSACTIONDTO_H
