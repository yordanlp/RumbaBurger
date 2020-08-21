#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H
#include <Dto/storagedto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "result.h"
#include <Services/storagetransactionservice.h>
#include <Dto/storagetransactiondto.h>
#include <Services/userservice.h>


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
