#ifndef STORAGETRANSACTIONSERVICE_H
#define STORAGETRANSACTIONSERVICE_H
#include <storagetransactiondto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QDate>

class storageTransactionService
{
public:
    storageTransactionService();
    bool insertStorageTransaction(storageTransactionDto);
    bool updateStorageTransaction(storageTransactionDto);
    QList <storageTransactionDto> getStorageTransactionByDate(QDate inicial, QDate final);
};

#endif // STORAGETRANSACTIONSERVICE_H
