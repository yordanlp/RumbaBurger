#ifndef CENTRALSTORAGETRANSACTIONSERVICE_H
#define CENTRALSTORAGETRANSACTIONSERVICE_H
#include <Dto/centralstoragetransactiondto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <result.h>

enum { COMPRA, EXTRACCION, CENTRAL_TO_LOCAL, LOCAL_TO_CENTRAL } transactions;

class centralStorageTransactionService
{
public:
    centralStorageTransactionService();
    Result<bool> insertCentralStorageTransaction(centralStorageTransactionDto);
    Result<bool> updateCentralStorageTransaction(centralStorageTransactionDto);
    Result <QList <centralStorageTransactionDto>> getCentralStorageTransactionByDate(QDate inicial, QDate final);
};

#endif // CENTRALSTORAGETRANSACTIONSERVICE_H
