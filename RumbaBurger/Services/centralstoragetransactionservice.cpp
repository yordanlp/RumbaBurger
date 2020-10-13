#include "centralstoragetransactionservice.h"
#include "utiles.h"

centralStorageTransactionService::centralStorageTransactionService()
{

}

Result<bool> centralStorageTransactionService::insertCentralStorageTransaction(centralStorageTransactionDto p){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("INSERT INTO centralStorageTransaction (type, amount, idProduct, date, idUser, price, merma, aviable_in_local, aviable_in_central) VALUES (:type, :amount, :idProduct, :date, :idUser, :price, :merma, :aviable_in_local, :aviable_in_central)");
    query.bindValue(":type", p.type);
    query.bindValue(":amount", p.amount);
    query.bindValue(":idProduct", p.idProduct);
    query.bindValue(":date", p.date.toString(Qt::ISODate));
    query.bindValue(":idUser", p.idUser);
    query.bindValue(":price", p.price);
    query.bindValue(":merma", p.merma);
    query.bindValue(":aviable_in_local", p.aviable_in_local);
    query.bindValue(":aviable_in_central",p.aviable_in_central);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertCentralStorageTransaction: " + query.lastError().text();
    qDebug() << "ERROR insertCentralStorageTransaction: " << query.lastError().text();
    return res;

}

/*Result<bool> centralStorageTransactionService::updateCentralStorageTransaction(centralStorageTransactionDto p){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("UPDATE centralStorageTransaction SET type=:type, amount=:amount, idProduct=:idProduct, date=:date, idUser=:idUser, price=:price, merma=:merma  WHERE id=:id");

    query.bindValue(":id", p.id);
    query.bindValue(":type", p.type);
    query.bindValue(":amount", p.amount);
    query.bindValue(":idProduct", p.idProduct);
    query.bindValue(":date", p.date.toString(Qt::ISODate));
    query.bindValue(":idUser", p.idUser);
    query.bindValue(":price", p.price);
    query.bindValue(":merma", p.merma);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR updateCentralStorageTransaction: " + query.lastError().text();
    qDebug() << "ERROR updateCentralStorageTransaction: " << query.lastError().text();
    return res;

}*/


/*Result <QList<centralStorageTransactionDto>> centralStorageTransactionService::getCentralStorageTransactionByDate(QDate inicial, QDate final){
    Result <QList<centralStorageTransactionDto>> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM centralStorageTransaction WHERE date BETWEEN :inicial AND :final");
    query.bindValue(":inicial", inicial.toString(Qt::ISODate));
    query.bindValue(":final", final.toString(Qt::ISODate));

    QList<centralStorageTransactionDto> p;
    if( !query.exec() ){
        qDebug() << "ERROR getCentralStorageTransactionByDate: " << query.lastError().text();
        res.res = result::FAIL;
        res.msg = "ERROR getCentralStorageTransactionByDate: " + query.lastError().text();
        return res;
    }

    while(query.next()){
        p.append( centralStorageTransactionDto(query.value(0).toInt(),
                                        query.value(1).toBool(),
                                        query.value(2).toDouble(),
                                        query.value(3).toInt(),
                                        utiles::stringToDate(query.value(4).toString()),
                                        query.value(5).toInt(),
                                        query.value(6).toDouble(),
                                        query.value(7).toDouble()) );
    }

    res.res = result::SUCCESS;
    res.data = p;
    return res;

}*/

Result <QList<centralStorageTransactionDto>> centralStorageTransactionService::getMovimientos(QDate inicial, QDate final, QString producto, int central, int local){
    Result <QList<centralStorageTransactionDto>> res;
    QSqlQuery query;
    query.prepare("SELECT centralStorageTransaction.id, type, amount, idProduct, date, idUser, centralStorageTransaction.price, merma, aviable_in_local, aviable_in_central, productName, unitType FROM centralStorageTransaction INNER JOIN product ON (centralStorageTransaction.idProduct = product.id) WHERE (date BETWEEN :inicial AND :final) AND (type = :central OR type = :local) AND productName LIKE :product ORDERED BY date DESC");
    query.bindValue(":inicial", inicial.toString(Qt::ISODate));
    query.bindValue(":final", final.toString(Qt::ISODate));
    query.bindValue(":central", central);
    query.bindValue(":local", local);
    query.bindValue(":product", producto);

    QList<centralStorageTransactionDto> p;
    if( !query.exec() ){
        qDebug() << "ERROR getCentralStorageTransactionByDate: " << query.lastError().text();
        res.res = result::FAIL;
        res.msg = "ERROR getCentralStorageTransactionByDate: " + query.lastError().text();
        return res;
    }

    while(query.next()){
        p.append( centralStorageTransactionDto(query.value(0).toInt(),
                                        query.value(1).toBool(),
                                        query.value(2).toDouble(),
                                        query.value(3).toInt(),
                                        utiles::stringToDate(query.value(4).toString()),
                                        query.value(5).toInt(),
                                        query.value(6).toDouble(),
                                        query.value(7).toDouble(),
                                        query.value(8).toDouble(),
                                        query.value(9).toDouble(),
                                        query.value(10).toString(),
                                        query.value(11).toInt()) );
    }

    res.res = result::SUCCESS;
    res.data = p;
    return res;

}

Result <QList<centralStorageTransactionDto>> centralStorageTransactionService::getExtraccionesYCompras(QDate inicial, QDate final, QString producto, int extraccion, int compra){
    Result <QList<centralStorageTransactionDto>> res;
    QSqlQuery query;
    query.prepare("SELECT centralStorageTransaction.id, type, amount, idProduct, date, idUser, centralStorageTransaction.price, merma, aviable_in_local, aviable_in_central, productName, unitType FROM centralStorageTransaction INNER JOIN product ON (centralStorageTransaction.idProduct = product.id) WHERE (date BETWEEN :inicial AND :final) AND (type = :extraccion OR type = :compra) AND productName LIKE :product ORDERED BY date DESC");
    query.bindValue(":inicial", inicial.toString(Qt::ISODate));
    query.bindValue(":final", final.toString(Qt::ISODate));
    query.bindValue(":extraccion", extraccion);
    query.bindValue(":compra", compra);
    query.bindValue(":product", producto);

    QList<centralStorageTransactionDto> p;
    if( !query.exec() ){
        qDebug() << "ERROR getCentralStorageTransactionByDate: " << query.lastError().text();
        res.res = result::FAIL;
        res.msg = "ERROR getCentralStorageTransactionByDate: " + query.lastError().text();
        return res;
    }

    while(query.next()){
        p.append( centralStorageTransactionDto(query.value(0).toInt(),
                                        query.value(1).toBool(),
                                        query.value(2).toDouble(),
                                        query.value(3).toInt(),
                                        utiles::stringToDate(query.value(4).toString()),
                                        query.value(5).toInt(),
                                        query.value(6).toDouble(),
                                        query.value(7).toDouble(),
                                        query.value(8).toDouble(),
                                        query.value(9).toDouble(),
                                        query.value(10).toString(),
                                        query.value(11).toInt()) );
    }

    res.res = result::SUCCESS;
    res.data = p;
    return res;

}
