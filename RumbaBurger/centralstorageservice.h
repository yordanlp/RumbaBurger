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
    //QList <centralStorageDto> getAllCentralStorage();
    Result< QList<centralStorageDto> >getAllCentralStorage();

    bool insertCentralStorage(centralStorageDto);
    centralStorageDto getCentralStorageById(int);
    bool updateCentralStorageById(centralStorageDto);
};

#endif // CENTRALSTORAGESERVICE_H
