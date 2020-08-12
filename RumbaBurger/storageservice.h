#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H
#include <storagedto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "result.h"
#include <storagetransactionservice.h>
#include <storagetransactiondto.h>
#include <userservice.h>


class storageService
{
public:
    storageService();
    Result<QList <storageDto>> getAllStorage();
    Result<bool> insertStorage(storageDto);
    Result<storageDto> getStorageById(int);
    Result<bool> updateStorageById(storageDto);
    //Requisitos funcionales
    Result<bool> modifyStorage(int,double,bool);
    storageTransactionService storageTransactionServiceObject;

};

#endif // STORAGESERVICE_H
