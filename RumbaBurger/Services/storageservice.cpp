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

    if(!query.next()){
        res.res = result::RECORD_NOT_FOUND;
        res.msg = "Producto no enconrtado en almacen local";
        return res;
    }

    res.res = result::SUCCESS;
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


Result<bool> storageService::modifyStorage( int id, double cant, bool type){
    Result<bool> res;
    storageDto p = getStorageById(id).data;
    if(type == 1)
        p.amount += cant;
    else
        p.amount -= cant;

    if(p.amount<0){
        res.res = result::FAIL;
        res.msg = "La cantidad a extraer es mayor que la cantidad en almacen local";
        return res;
    }

    updateStorageById(p);

    storageTransactionDto st;
    st.idProduct = p.id;
    st.type = type;
    st.date = QDate::currentDate();
    st.amount = cant;
    st.idUser = UserService::loggedUser;
    Result<bool> b = storageTransactionServiceObject.insertStorageTransaction(st);
    res.res = result::SUCCESS;
    res.data = b.data;
    return res;
}
