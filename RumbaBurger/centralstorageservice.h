#ifndef CENTRALSTORAGESERVICE_H
#define CENTRALSTORAGESERVICE_H
#include<centralstoragedto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "result.h"

class centralStorageService
{
public:
    centralStorageService();
    Result< QList<centralStorageDto> >getAllCentralStorage();
    Result< bool > insertCentralStorage(centralStorageDto);
    Result<centralStorageDto> getCentralStorageById(int);
    Result<bool> updateCentralStorageById(centralStorageDto);
};

#endif // CENTRALSTORAGESERVICE_H
