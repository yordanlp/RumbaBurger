#ifndef CENTRALSTORAGESERVICE_H
#define CENTRALSTORAGESERVICE_H
#include <Dto/centralstoragedto.h>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include "result.h"
#include <Dto/centralstoragetransactiondto.h>
#include <Services/centralstoragetransactionservice.h>
#include <Services//userservice.h>
#include <Dto/productdto.h>
#include <Services/productservice.h>
#include <Services/storageservice.h>
#include <Dto/storagedto.h>

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
