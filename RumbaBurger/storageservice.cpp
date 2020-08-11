#include "storageservice.h"
#include <QSqlQuery>

storageService::storageService()
{

}

bool storageService::insertStorage(storageDto p){
    QSqlQuery query;
    query.prepare("INSERT INTO storage (amount) VALUES (:amount)");
    query.bindValue(":amount", p.amount);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertStorage: " << query.lastError().text();
    return false;
}


QList<storageDto> storageService::getAllStorage(){
    QSqlQuery query;
    query.prepare("SELECT * FROM storage");
    if( !query.exec() ){
        qDebug() << "ERROR getAllStorage:" << query.lastError().text();
        return QList<storageDto>();
    }
    QList<storageDto> ret;

    while(query.next()){
        ret.append( storageDto(query.value(0).toInt(), query.value(1).toDouble()) );
    }

    return ret;
}

storageDto storageService::getStorageById(int id){
    QSqlQuery query;
    query.prepare("SELECT * FROM storage WHERE id = :id");
    query.bindValue(":id", id);
    if( !query.exec() ){
        qDebug() << "ERROR getStorageById:" << query.lastError().text();
        return storageDto(-1,-1);
    }

    query.next();
    return storageDto(query.value(0).toInt(), query.value(1).toDouble());
}

bool storageService::updateStorageById( storageDto p){
    QSqlQuery query;
    query.prepare("UPDATE storage SET amount=:amount WHERE id = :id");
    query.bindValue(":id", p.id);
    query.bindValue(":amount", p.amount);
    if( !query.exec() ){
        qDebug() << "ERROR updateStorageById:" << query.lastError().text();
        return false;
    }
    return true;
}
