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

Result<bool> centralStorageService::modifyCentralStorage(int id, double cant, bool type, double price){
    Result<bool> res;
    centralStorageDto p = getCentralStorageById(id).data;
    if(type == 1)
        p.amount += cant;
    else
        p.amount -= cant;

    if(p.amount<0){
        res.res = result::FAIL;
        res.msg = "La cantidad a extraer es mayor que la cantidad en almacen central";
        return res;
    }
    ProductDto prod;
    prod.id = id;
    prod = ProductServiceObject.getProductByID(prod).data;
    double newprice = prod.price;


    if(type == 1){ /// Actualizar el nuevo precio de adquisicion del producto
        double oldtotal = getCentralStorageById(id).data.amount;

        auto r = storageServiceObject.getStorageById(id);

        if(r.res==result::SUCCESS)
            oldtotal+= r.data.amount;

        double oldcost = oldtotal * prod.price;
        double total = oldtotal + cant;
        double cost = oldcost + cant*price;
        if(cost<0)
             newprice = 0;
        else
             newprice = cost/total;
        prod.price = newprice;
        ProductServiceObject.updateProduct(prod);
    }

    updateCentralStorageById(p);

    centralStorageTransactionDto st;
    st.idProduct = p.id;
    st.type = type;
    st.date = QDate::currentDate();
    st.amount = cant;
    st.idUser = UserService::loggedUser;
    st.price = price;
    Result<bool> b = centralStorageTransactionServiceObject.insertCentralStorageTransaction(st);
    res.res = result::SUCCESS;
    res.data = b.data;
    return res;
}
