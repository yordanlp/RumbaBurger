#include "centralstorageservice.h"

centralStorageService::centralStorageService()
{

}

bool centralStorageService::insertCentralStorage(centralStorageDto p){
    QSqlQuery query;
    query.prepare("INSERT INTO centralStorage (amount) VALUES (:amount)");
    query.bindValue(":amount", p.amount);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertCentralStorage: " << query.lastError().text();
    return false;
}


QList<centralStorageDto> centralStorageService::getAllCentralStorage(){
    QSqlQuery query;
    query.prepare("SELECT * FROM centralStorage");
    if( !query.exec() ){
        qDebug() << "ERROR getAllCentralStorage:" << query.lastError().text();
        return QList<centralStorageDto>();
    }
    QList<centralStorageDto> ret;

    while(query.next()){
        ret.append( centralStorageDto(query.value(0).toInt(), query.value(1).toDouble()) );
    }

    return ret;
}

centralStorageDto centralStorageService::getCentralStorageById(int id){
    QSqlQuery query;
    query.prepare("SELECT * FROM centralStorage WHERE id = :id");
    query.bindValue(":id", id);
    if( !query.exec() ){
        qDebug() << "ERROR getCentralStorageById:" << query.lastError().text();
        return centralStorageDto(-1,-1);
    }

    query.next();
    return centralStorageDto(query.value(0).toInt(), query.value(1).toDouble());
}

bool centralStorageService::updateCentralStorageById( centralStorageDto p){
    QSqlQuery query;
    query.prepare("UPDATE centralStorage SET amount=:amount WHERE id = :id");
    query.bindValue(":id", p.id);
    query.bindValue(":amount", p.amount);
    if( !query.exec() ){
        qDebug() << "ERROR updateCentralStorageById:" << query.lastError().text();
        return false;
    }
    return true;
}
