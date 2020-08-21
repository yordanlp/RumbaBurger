#include "expensesservice.h"

ExpensesService::ExpensesService()
{

}

Result<bool> ExpensesService::insertExpenses(ExpensesDto e){
    Result<bool>res;
    QSqlQuery query;
    query.prepare("INSERT INTO 'expenses' (description, price) VALUES (:description, :price)");
    query.bindValue(":description", e.description);
    query.bindValue(":price", e.price);

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
