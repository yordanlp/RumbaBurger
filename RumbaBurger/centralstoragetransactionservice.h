#ifndef CENTRALSTORAGETRANSACTIONSERVICE_H
#define CENTRALSTORAGETRANSACTIONSERVICE_H
#include<centralstoragetransactiondto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>

class centralStorageTransactionService
{
public:
    centralStorageTransactionService();
    bool insertCentralStorageTransaction(centralStorageTransactionDto);
    bool updateCentralStorageTransaction(centralStorageTransactionDto);
    QList <centralStorageTransactionDto> getCentralStorageTransactionByDate(QDate inicial, QDate final);
};

#endif // CENTRALSTORAGETRANSACTIONSERVICE_H
