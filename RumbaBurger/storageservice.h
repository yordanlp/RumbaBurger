#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H
#include <storagedto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>

class storageService
{
public:
    storageService();
    QList <storageDto> getAllStorage();
    bool insertStorage(storageDto);
    storageDto getStorageById(int);
    bool updateStorageById(storageDto);
};

#endif // STORAGESERVICE_H
