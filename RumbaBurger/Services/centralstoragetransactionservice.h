#ifndef CENTRALSTORAGETRANSACTIONSERVICE_H
#define CENTRALSTORAGETRANSACTIONSERVICE_H
#include <Dto/centralstoragetransactiondto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <result.h>

class centralStorageTransactionService
{
public:
    centralStorageTransactionService();
    Result<bool> insertCentralStorageTransaction(centralStorageTransactionDto);
    //Result<bool> updateCentralStorageTransaction(centralStorageTransactionDto);
    //Result <QList <centralStorageTransactionDto>> getCentralStorageTransactionByDate(QDate inicial, QDate final);
    Result <QList <centralStorageTransactionDto>> getMovimientos(QDate inicial, QDate final, QString producto, int central, int local );
    Result <QList <centralStorageTransactionDto>> getExtraccionesYCompras(QDate inicial, QDate final, QString producto, int extraccion, int compra);
};

#endif // CENTRALSTORAGETRANSACTIONSERVICE_H
