#include "centralstoragetransactionservice.h"
#include "utiles.h"

centralStorageTransactionService::centralStorageTransactionService()
{

}

bool centralStorageTransactionService::insertCentralStorageTransaction(centralStorageTransactionDto p){
    QSqlQuery query;
    query.prepare("INSERT INTO centralStorageTransaction (type, amount, idProduct, date, idUser, price) VALUES (:type, :amount, :idProduct, :date, :idUser, :price)");
    query.bindValue(":type", p.type);
    query.bindValue(":amount", p.amount);
    query.bindValue(":idProduct", p.idProduct);
    query.bindValue(":date", p.date.toString(Qt::ISODate));
    query.bindValue(":idUser", p.idUser);
    query.bindValue(":price", p.price);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertCentralStorageTransaction: " << query.lastError().text();
    return false;

}

bool centralStorageTransactionService::updateCentralStorageTransaction(centralStorageTransactionDto p){
    QSqlQuery query;
    query.prepare("UPDATE centralStorageTransaction SET type=:type, amount=:amount, idProduct=:idProduct, date=:date, idUser=:idUser, price=:price  WHERE id=:id");

    query.bindValue(":id", p.id);
    query.bindValue(":type", p.type);
    query.bindValue(":amount", p.amount);
    query.bindValue(":idProduct", p.idProduct);
    query.bindValue(":date", p.date.toString(Qt::ISODate));
    query.bindValue(":idUser", p.idUser);
    query.bindValue(":price", p.price);

    if( query.exec() ) return true;
    qDebug() << "ERROR updateCentralStorageTransaction: " << query.lastError().text();
    return false;

}


QList<centralStorageTransactionDto> centralStorageTransactionService::getCentralStorageTransactionByDate(QDate inicial, QDate final){
    QSqlQuery query;
    query.prepare("SELECT * FROM centralStorageTransaction WHERE date BETWEEN :inicial AND :final");
    query.bindValue(":inicial", inicial.toString(Qt::ISODate));
    query.bindValue(":final", final.toString(Qt::ISODate));

    QList<centralStorageTransactionDto> p;
    if( !query.exec() ){
        qDebug() << "ERROR getCentralStorageTransactionByDate: " << query.lastError().text();
        return p;
    }

    while(query.next()){
        p.append( centralStorageTransactionDto(query.value(0).toInt(),
                                        query.value(1).toBool(),
                                        query.value(2).toDouble(),
                                        query.value(3).toInt(),
                                        utiles::stringToDate(query.value(4).toString()),
                                        query.value(5).toInt(),
                                        query.value(6).toDouble()) );
    }

    return p;

}
