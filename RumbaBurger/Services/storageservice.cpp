#include "storageservice.h"
#include <QSqlQuery>
#include <Services/centralstorageservice.h>

storageService::storageService()
{

}

Result<bool> storageService::insertStorage(storageDto p){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("INSERT INTO storage (id, amount) VALUES (:id, :amount)");
    query.bindValue(":amount", p.amount);
    query.bindValue(":id", p.id);

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


Result<bool> storageService::modifyStorage( int id, double cant, int type){
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

Result<QList<StorageProductDto> > storageService::getLocalStorageBySearch(QString search)
{
    qDebug() << "search:" << search;
    Result<QList<StorageProductDto>> res;
    QString q = "SELECT * FROM storage INNER JOIN product ON storage.id = product.id WHERE lower(productName) LIKE :search";
    QSqlQuery query;
    query.prepare(q);
    query.bindValue(":search", search);
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = query.lastError().text();
        qDebug() << "Error getLocalStorageBySearch" <<  query.lastError().text();
        qDebug() << query.lastQuery();
        return res;
    }
    qDebug() << "exito";
    res.res = SUCCESS;
    QList<StorageProductDto> L;
    while( query.next() ){
        L << StorageProductDto(query.value(0).toInt(), query.value(3).toString(), query.value(1).toDouble(), query.value(5).toDouble(), query.value(4).toInt());
    }
    res.data = L;
    return res;
}

Result<bool> storageService::moveToCentral(int _id, int _amount)
{
    Result<bool>res;
    centralStorageService CentralStorageService;
    auto prod  = CentralStorageService.getCentralStorageById(_id);
    auto localProd = getStorageById(_id);
    if( localProd.res != SUCCESS ){
        res.res = FAIL;
        return res;
    }

    if( localProd.data.amount < _amount ){
        res.res = INSUFICIENT_AMOUNT;
        return res;
    }

    if( prod.res == RECORD_NOT_FOUND ){
        CentralStorageService.insertCentralStorage(centralStorageDto(_id, _amount));
        updateStorageById(storageDto(_id,localProd.data.amount - _amount));
        res.res = SUCCESS;
        return res;
    }

    if( prod.res == SUCCESS ){
        CentralStorageService.updateCentralStorageById(centralStorageDto(_id, prod.data.amount + _amount));
        updateStorageById(storageDto(_id,localProd.data.amount - _amount));
        res.res = SUCCESS;
        return res;
    }


    res.res = FAIL;
    return res;
}

Result<bool> storageService::updateStorage(int productId, double amount, int type)
{
    Result<bool> res;
    storageDto p = getStorageById(productId).data;
    if(type == 1)
        p.amount += amount;
    else
        p.amount -= amount;

    if(p.amount<0){
        res.res = result::FAIL;
        res.msg = "No hay producto suficiente en el almacen local";
        return res;
    }

    updateStorageById(p);
    res.res = SUCCESS;

    /*storageTransactionDto st;
    st.idProduct = p.id;
    st.type = type;
    st.date = QDate::currentDate();
    st.amount = cant;
    st.idUser = UserService::loggedUser;
    Result<bool> b = storageTransactionServiceObject.insertStorageTransaction(st);
    res.res = result::SUCCESS;
    res.data = b.data;*/
    return res;
}

