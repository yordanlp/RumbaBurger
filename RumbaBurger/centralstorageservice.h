#ifndef CENTRALSTORAGESERVICE_H
#define CENTRALSTORAGESERVICE_H
#include<centralstoragedto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>

class centralStorageService
{
public:
    centralStorageService();
    QList <centralStorageDto> getAllCentralStorage();
    bool insertCentralStorage(centralStorageDto);
    centralStorageDto getCentralStorageById(int);
    bool updateCentralStorageById(centralStorageDto);
};

#endif // CENTRALSTORAGESERVICE_H
