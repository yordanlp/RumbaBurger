#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H
#include <storagedto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "result.h"

class storageService
{
public:
    storageService();
    Result<QList <storageDto>> getAllStorage();
    Result<bool> insertStorage(storageDto);
    Result<storageDto> getStorageById(int);
    Result<bool> updateStorageById(storageDto);
};

#endif // STORAGESERVICE_H
