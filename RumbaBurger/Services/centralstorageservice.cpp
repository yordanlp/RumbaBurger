#include "centralstorageservice.h"
#include <Services/storageservice.h>

centralStorageService::centralStorageService()
{

}

Result<bool> centralStorageService::insertCentralStorage(centralStorageDto p){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("INSERT INTO centralStorage (id, amount) VALUES (:id, :amount)");
    query.bindValue(":amount", p.amount);
    query.bindValue(":id",p.id);
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

    if( query.next() ){
        res.res = result::SUCCESS;
        res.data = centralStorageDto(query.value(0).toInt(), query.value(1).toDouble());
        return res;
    }
    res.res = RECORD_NOT_FOUND;
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

Result<bool> centralStorageService::modifyCentralStorage(int id, double cant, bool type, double price, double merma){
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
    st.merma = merma;
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

Result<QList<StorageProductDto> > centralStorageService::getCentralStorageBySearch(QString search)
{
    qDebug() << "search:" << search;
    Result<QList<StorageProductDto>> res;
    QString q = "SELECT * FROM centralStorage INNER JOIN product ON centralStorage.id = product.id WHERE lower(productName) LIKE :search";
    QSqlQuery query;
    query.prepare(q);
    query.bindValue(":search", search);
    if( !query.exec() ){
        res.res = FAIL;
        res.msg = query.lastError().text();
        qDebug() << "Error getCentralStorageBySearch" <<  query.lastError().text();
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

Result<bool> centralStorageService::moveToLocal(int idProduct, double amount)
{
    Result<bool>res;
    storageService StorageService;
    auto prod  = StorageService.getStorageById(idProduct);
    auto centralProd = getCentralStorageById(idProduct);
    if( centralProd.res != SUCCESS ){
        res.res = FAIL;
        return res;
    }

    if( centralProd.data.amount < amount ){
        res.res = INSUFICIENT_AMOUNT;
        return res;
    }

    if( prod.res == RECORD_NOT_FOUND ){
        StorageService.insertStorage(storageDto(idProduct, amount));
        updateCentralStorageById(centralStorageDto(idProduct,centralProd.data.amount - amount));
        res.res = SUCCESS;
        return res;
    }

    if( prod.res == SUCCESS ){
        StorageService.updateStorageById(storageDto(idProduct, prod.data.amount + amount));
        updateCentralStorageById(centralStorageDto(idProduct,centralProd.data.amount - amount));
        res.res = SUCCESS;
        return res;
    }


    res.res = FAIL;
    return res;
}
