#include "storagetransactionservice.h"
#include "utiles.h"

storageTransactionService::storageTransactionService()
{

}

Result<bool> storageTransactionService::insertStorageTransaction(storageTransactionDto p){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("INSERT INTO storageTransaction (type, amount, idProduct, date, idUser, price) VALUES (:type, :amount, :idProduct, :date, :idUser, :price)");
    query.bindValue(":type", p.type);
    query.bindValue(":amount", p.amount);
    query.bindValue(":idProduct", p.idProduct);
    query.bindValue(":date", p.date.toString(Qt::ISODate));
    query.bindValue(":idUser", p.idUser);
    query.bindValue(":price", p.price);

    if( query.exec() ){
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertStorageTransaction: " + query.lastError().text();
    qDebug() << "ERROR insertStorageTransaction: " << query.lastError().text();
    return res;

}

Result<bool> storageTransactionService::updateStorageTransaction(storageTransactionDto p){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("UPDATE storageTransaction SET type=:type, amount=:amount, idProduct=:idProduct, date=:date, idUser=:idUser, price=:price  WHERE id=:id");

    query.bindValue(":id", p.id);
    query.bindValue(":type", p.type);
    query.bindValue(":amount", p.amount);
    query.bindValue(":idProduct", p.idProduct);
    query.bindValue(":date", p.date.toString(Qt::ISODate));
    query.bindValue(":idUser", p.idUser);
    query.bindValue(":price", p.price);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR updateStorageTransaction: " + query.lastError().text();
    qDebug() << "ERROR updateStorageTransaction: " << query.lastError().text();
    return res;

}


Result<QList<storageTransactionDto>> storageTransactionService::getStorageTransactionByDate(QDate inicial, QDate final){
    Result<QList<storageTransactionDto>>res;
    QSqlQuery query;
    query.prepare("SELECT * FROM storageTransaction WHERE date BETWEEN :inicial AND :final");
    query.bindValue(":inicial", inicial.toString(Qt::ISODate));
    query.bindValue(":final", final.toString(Qt::ISODate));

    QList<storageTransactionDto> p;
    if( !query.exec() ){
        res.res = result::FAIL;
        res.msg = "ERROR getStorageTransactionByDate: " + query.lastError().text();
        qDebug() << "ERROR getStorageTransactionByDate: " << query.lastError().text();
        return res;
    }

    while(query.next()){
        p.append( storageTransactionDto(query.value(0).toInt(),
                                        query.value(1).toBool(),
                                        query.value(2).toDouble(),
                                        query.value(3).toInt(),
                                        utiles::stringToDate(query.value(4).toString()),
                                        query.value(5).toInt(),
                                        query.value(6).toDouble()) );
    }

    res.res = result::SUCCESS;
    res.data = p;

    return res;

}
