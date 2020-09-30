#include "expensesservice.h"
#include <utiles.h>

ExpensesService::ExpensesService()
{

}

Result<bool> ExpensesService::insertExpenses(ExpensesDto e){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("INSERT INTO 'expenses' (description, price, date) VALUES (:description, :price, :date)");
    query.bindValue(":description", e.description);
    query.bindValue(":price", e.price);
    query.bindValue(":date", e.date.toString(Qt::ISODate));

    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR insertExpenses: " + query.lastError().text();
    qDebug() << "ERROR insertExpenses: " << query.lastError().text();
    return res;
}

Result<bool> ExpensesService::deleteExpenses(ExpensesDto e){
    Result<bool> res;
    QSqlQuery query;
    query.prepare("DELETE FROM expenses WHERE id = :id");
    query.bindValue(":id", e.id);
    if( query.exec() ) {
        res.res = result::SUCCESS;
        return res;
    }
    res.res = result::FAIL;
    res.msg = "ERROR deleteExpenses: " + query.lastError().text();
    qDebug() << "ERROR deleteExpenses: " << query.lastError().text();
    return res;
}

Result<QList<ExpensesDto> > ExpensesService::getExpensesByDate(QDate start, QDate end)
{
    Result<QList<ExpensesDto>> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM expenses WHERE date BETWEEN :inicial AND :final ORDER BY date DESC");
    query.bindValue(":inicial", start.toString(Qt::ISODate));
    query.bindValue(":final", end.toString(Qt::ISODate));
    if( !query.exec() ) {
        res.res = result::FAIL;
        return res;
        res.msg = "ERROR getExpensesByDate: " + query.lastError().text();
        qDebug() << "ERROR getExpensesByDate: " << query.lastError().text();
    }
    res.res = SUCCESS;
    while (query.next()) {
        res.data << ExpensesDto(query.value(0).toInt(), query.value(1).toString(), query.value(2).toDouble(), query.value(3).toDate() );
    }
    return res;
}
