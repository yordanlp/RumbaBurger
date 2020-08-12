#ifndef STORAGETRANSACTIONSERVICE_H
#define STORAGETRANSACTIONSERVICE_H
#include <storagetransactiondto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QDate>
#include "result.h"

class storageTransactionService
{
public:
    storageTransactionService();
    Result<bool> insertStorageTransaction(storageTransactionDto);
    Result<bool> updateStorageTransaction(storageTransactionDto);
    Result<QList <storageTransactionDto>> getStorageTransactionByDate(QDate inicial, QDate final);
};

#endif // STORAGETRANSACTIONSERVICE_H
