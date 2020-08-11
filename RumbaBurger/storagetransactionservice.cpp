#include "storagetransactionservice.h"
#include "utiles.h"

storageTransactionService::storageTransactionService()
{

}

bool storageTransactionService::insertStorageTransaction(storageTransactionDto p){
    QSqlQuery query;
    query.prepare("INSERT INTO storageTransaction (type, amount, idProduct, date, idUser, price) VALUES (:type, :amount, :idProduct, :date, :idUser, :price)");
    query.bindValue(":type", p.type);
    query.bindValue(":amount", p.amount);
    query.bindValue(":idProduct", p.idProduct);
    query.bindValue(":date", p.date.toString(Qt::ISODate));
    query.bindValue(":idUser", p.idUser);
    query.bindValue(":price", p.price);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertStorageTransaction: " << query.lastError().text();
    return false;

}

bool storageTransactionService::updateStorageTransaction(storageTransactionDto p){
    QSqlQuery query;
    query.prepare("UPDATE storageTransaction SET type=:type, amount=:amount, idProduct=:idProduct, date=:date, idUser=:idUser, price=:price  WHERE id=:id");

    query.bindValue(":id", p.id);
    query.bindValue(":type", p.type);
    query.bindValue(":amount", p.amount);
    query.bindValue(":idProduct", p.idProduct);
    query.bindValue(":date", p.date.toString(Qt::ISODate));
    query.bindValue(":idUser", p.idUser);
    query.bindValue(":price", p.price);

    if( query.exec() ) return true;
    qDebug() << "ERROR updateStorageTransaction: " << query.lastError().text();
    return false;

}


QList<storageTransactionDto> storageTransactionService::getStorageTransactionByDate(QDate inicial, QDate final){
    QSqlQuery query;
    query.prepare("SELECT * FROM storageTransaction WHERE date BETWEEN :inicial AND :final");
    query.bindValue(":inicial", inicial.toString(Qt::ISODate));
    query.bindValue(":final", final.toString(Qt::ISODate));

    QList<storageTransactionDto> p;
    if( !query.exec() ){
        qDebug() << "ERROR getStorageTransactionByDate: " << query.lastError().text();
        return p;
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

    return p;

}
