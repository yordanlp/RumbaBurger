#ifndef TRANSACTIONSERVICE_H
#define TRANSACTIONSERVICE_H

#include <Dto/transactiondto.h>
#include <result.h>

class TransactionService
{
public:
    TransactionService();
    Result<bool> insertTransaction( TransactionDto t );
    Result<bool> deleteTransaction( int id );
    Result <QList <TransactionDto>> getMovimientos(QDate inicial, QDate final, QString producto, origen origin );
    Result <QList <TransactionDto>> getExtraccionesYCompras(QDate inicial, QDate final, QString producto, operaciones operacion, origen origin );
};

#endif // TRANSACTIONSERVICE_H
