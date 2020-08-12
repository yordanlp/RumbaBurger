#include "centralstorageservice.h"

centralStorageService::centralStorageService()
{

}

Result<bool> centralStorageService::insertCentralStorage(centralStorageDto p){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("INSERT INTO centralStorage (amount) VALUES (:amount)");
    query.bindValue(":amount", p.amount);

    res.res = result::SUCCESS;
    if( query.exec() ) return res;
    qDebug() << "ERROR insertCentralStorage: " << query.lastError().text();
    res.res = result::FAIL;
    res.msg = "ERROR insertCentralStorage: " + query.lastError().text();
    return res;
}


Result<QList<centralStorageDto>> centralStorageService::getAllCentralStorage(){
    Result<QList<centralStorageDto>> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM centralStorage");
    if( !query.exec() ){
        qDebug() << "ERROR getAllCentralStorage:" << query.lastError().text();
        res.res = result::FAIL;
        res.msg = "ERROR getAllCentralStorage: " + query.lastError().text();
        return res;
    }
    QList<centralStorageDto> ret;

    while(query.next()){
        ret.append( centralStorageDto(query.value(0).toInt(), query.value(1).toDouble()) );
    }

    res.res = result::SUCCESS;
    res.data = ret;
    return res;
}

Result<centralStorageDto> centralStorageService::getCentralStorageById(int id){
    QSqlQuery query;
    Result<centralStorageDto> res;
    query.prepare("SELECT * FROM centralStorage WHERE id = :id");
    query.bindValue(":id", id);
    if( !query.exec() ){
        res.res = result::FAIL;
        qDebug() << "ERROR getCentralStorageById:" << query.lastError().text();
        res.msg = "ERROR getCentralStorageById:" + query.lastError().text();
        return res;
    }

    res.res = result::SUCCESS;
    query.next();
    res.data = centralStorageDto(query.value(0).toInt(), query.value(1).toDouble());
    return res;
}

Result<bool> centralStorageService::updateCentralStorageById( centralStorageDto p){
    QSqlQuery query;
    Result<bool> res;
    query.prepare("UPDATE centralStorage SET amount=:amount WHERE id = :id");
    query.bindValue(":id", p.id);
    query.bindValue(":amount", p.amount);
    if( !query.exec() ){
        res.res = result::FAIL;
        qDebug() << "ERROR updateCentralStorageById:" << query.lastError().text();
        res.msg = "ERROR updateCentralStorageById:" + query.lastError().text();
        return res;
    }
    res.res = result::SUCCESS;
    return res;
}
