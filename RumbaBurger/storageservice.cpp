#include "storageservice.h"
#include <QSqlQuery>

storageService::storageService()
{

}

Result<bool> storageService::insertStorage(storageDto p){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("INSERT INTO storage (amount) VALUES (:amount)");
    query.bindValue(":amount", p.amount);

    if( query.exec() ){
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertStorage: " + query.lastError().text();
    qDebug() << "ERROR insertStorage: " << query.lastError().text();
    return res;
}


Result<QList<storageDto>> storageService::getAllStorage(){
    Result<QList<storageDto>> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM storage");
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "ERROR getAllStorage:" + query.lastError().text();
        qDebug() << "ERROR getAllStorage:" << query.lastError().text();
        return res;
    }
    QList<storageDto> ret;

    while(query.next()){
        ret.append( storageDto(query.value(0).toInt(), query.value(1).toDouble()) );
    }

    res.data = ret;
    res.res = result::SUCCESS;
    return res;
}

Result<storageDto> storageService::getStorageById(int id){
    Result<storageDto> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM storage WHERE id = :id");
    query.bindValue(":id", id);
    if( !query.exec() ){
        res.msg = "ERROR getStorageById:" + query.lastError().text();
        res.res = result::FAIL;
        qDebug() << "ERROR getStorageById:" << query.lastError().text();
        return res;
    }

    res.res = SUCCESS;
    query.next();

    res.data = storageDto(query.value(0).toInt(), query.value(1).toDouble());
    return res;
}

Result<bool> storageService::updateStorageById( storageDto p){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("UPDATE storage SET amount=:amount WHERE id = :id");
    query.bindValue(":id", p.id);
    query.bindValue(":amount", p.amount);
    if( !query.exec() ){
        res.msg = "ERROR updateStorageById:" + query.lastError().text();
        res.res = result::FAIL;
        qDebug() << "ERROR updateStorageById:" << query.lastError().text();
        return res;
    }
    res.res = result::SUCCESS;
    return res;
}

Result<bool> storageService::modifyStorage(int idProduct, double amount, bool type){
    Result<bool>res;
    return res;
}
