#ifndef CENTRALSTORAGESERVICE_H
#define CENTRALSTORAGESERVICE_H
#include<centralstoragedto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "result.h"
#include <centralstoragetransactiondto.h>
#include <centralstoragetransactionservice.h>
#include <userservice.h>
#include <productdto.h>
#include <productservice.h>
#include <storageservice.h>
#include <storagedto.h>

class centralStorageService
{
public:
    centralStorageService();
    Result< QList<centralStorageDto> >getAllCentralStorage();
    Result< bool > insertCentralStorage(centralStorageDto);
    Result<centralStorageDto> getCentralStorageById(int);
    Result<bool> updateCentralStorageById(centralStorageDto);
    //Requerimientos funcionales
    centralStorageTransactionService centralStorageTransactionServiceObject;
    ProductService ProductServiceObject;
    storageService storageServiceObject;
    Result<bool> modifyCentralStorage(int,double,bool,double=0);
};

#endif // CENTRALSTORAGESERVICE_H
