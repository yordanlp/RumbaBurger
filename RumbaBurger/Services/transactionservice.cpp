#include "transactionservice.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <utiles.h>
#include <QDate>

TransactionService::TransactionService()
{

}

Result<bool> TransactionService::insertTransaction(TransactionDto t)
{
    Result<bool>res;
    QSqlQuery query;
    query.prepare("INSERT INTO transactions (type, origin, amount, idProduct, date, idUser, price, merma, aviable_in_local, aviable_in_central, productName, unitType) VALUES (:type, :origin, :amount, :idProduct, :date, :idUser, :price, :merma, :aviable_in_local, :aviable_in_central, :productName, :unitType)");
    query.bindValue(":type", t.type);
    query.bindValue(":origin", t.origin);
    query.bindValue(":amount", t.amount);
    query.bindValue(":idProduct", t.idProduct);
    query.bindValue(":date", t.date.toString(Qt::ISODate));
    query.bindValue(":idUser", t.idUser);
    query.bindValue(":price", t.price);
    query.bindValue(":merma", t.merma);
    query.bindValue(":aviable_in_local", t.aviable_in_local);
    query.bindValue(":aviable_in_central", t.aviable_in_central);
    query.bindValue(":unitType", t.unitType);
    query.bindValue(":productName", t.productName);
    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertCentralStorageTransaction: " + query.lastError().text();
    qDebug() << "ERROR insertCentralStorageTransaction: " << query.lastError().text();
    return res;
}

Result<bool> TransactionService::deleteTransaction(int id)
{
    Result<bool>res;
    QSqlQuery query;
    query.prepare("DELETE FROM transactions WHERE id = :id");
    query.bindValue(":id", id);

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertCentralStorageTransaction: " + query.lastError().text();
    qDebug() << "ERROR insertCentralStorageTransaction: " << query.lastError().text();
    return res;
}

Result<QList<TransactionDto> > TransactionService::getMovimientos(QDate inicial, QDate final, QString producto, origen origin)
{
    Result <QList<TransactionDto>> res;
    QSqlQuery query;
    origen central, local;
    if( origin == origen::ALL )
        central = CENTRAL, local = LOCAL;
    else
        central = origin, local = origin;
    query.prepare("SELECT id, type, origin, amount, idProduct, date, \
                    idUser, price, merma, aviable_in_local, \
                    aviable_in_central, productName, unitType FROM transactions \
                    WHERE (date BETWEEN :inicial AND :final) AND (origin = :central \
                    OR origin = :local) AND type = :type AND productName LIKE \
                    :product ORDER BY date DESC");

    query.bindValue(":inicial", inicial.toString(Qt::ISODate));
    query.bindValue(":final", final.toString(Qt::ISODate));
    query.bindValue(":type", MOVIMIENTO);
    query.bindValue(":central", central);
    query.bindValue(":local", local);
    query.bindValue(":product", producto);

    QList<TransactionDto> p;
    if( !query.exec() ){
        qDebug() << "ERROR getMovimientos: " << query.lastError().text();
        res.res = result::FAIL;
        res.msg = "ERROR getMovimientos: " + query.lastError().text();
        return res;
    }

    while(query.next()){
        p.append(   TransactionDto(query.value(0).toInt(),
                    operaciones(query.value(1).toInt()),
                    origen(query.value(2).toInt()),
                    query.value(3).toDouble(),
                    query.value(4).toInt(),
                    utiles::stringToDate(query.value(5).toString()),
                    query.value(6).toInt(),
                    query.value(7).toDouble(),
                    query.value(8).toDouble(),
                    query.value(9).toDouble(),
                    query.value(10).toDouble(),
                    query.value(11).toString(),
                    query.value(12).toInt()) );
    }

    res.res = result::SUCCESS;
    res.data = p;
    return res;

}

Result<QList<TransactionDto> > TransactionService::getExtraccionesYCompras(QDate inicial, QDate final, QString producto, operaciones operacion, origen origin)
{
    Result <QList<TransactionDto>> res;
    QSqlQuery query;
    origen central, local;
    if( origin == ALL )
        central = CENTRAL, local = LOCAL;
    else
        central = origin, local = origin;

    operaciones extraccion, compra;
    if( operacion == ALL_OPS )
        extraccion = EXTRACCION, compra = COMPRA;
    else
        extraccion = operacion, compra = operacion;

    query.prepare("SELECT id, type, origin, amount, idProduct, date, idUser, price, merma, aviable_in_local, aviable_in_central, productName, unitType FROM transactions WHERE (date BETWEEN :inicial AND :final) AND (origin = :central OR origin = :local) AND (type = :extraccion OR type = :compra) AND productName LIKE :product ORDER BY date DESC");
    query.bindValue(":inicial", inicial.toString(Qt::ISODate));
    query.bindValue(":final", final.toString(Qt::ISODate));
    query.bindValue(":extraccion", extraccion);
    query.bindValue(":compra", compra);
    query.bindValue(":central", central);
    query.bindValue(":local", local);
    query.bindValue(":product", producto);

    QList<TransactionDto> p;
    if( !query.exec() ){
        qDebug() << "ERROR getCentralStorageTransactionByDate: " << query.lastError().text();
        res.res = result::FAIL;
        res.msg = "ERROR getCentralStorageTransactionByDate: " + query.lastError().text();
        return res;
    }

    while(query.next()){
        p.append(   TransactionDto(query.value(0).toInt(),
                    operaciones(query.value(1).toInt()),
                    origen(query.value(2).toInt()),
                    query.value(3).toDouble(),
                    query.value(4).toInt(),
                    utiles::stringToDate(query.value(5).toString()),
                    query.value(6).toInt(),
                    query.value(7).toDouble(),
                    query.value(8).toDouble(),
                    query.value(9).toDouble(),
                    query.value(10).toDouble(),
                    query.value(11).toString(),
                    query.value(12).toInt()) );
    }

    res.res = result::SUCCESS;
    res.data = p;
    return res;
}
