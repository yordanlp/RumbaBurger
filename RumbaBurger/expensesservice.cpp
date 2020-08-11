#include "expensesservice.h"

ExpensesService::ExpensesService()
{

}

bool ExpensesService::insertExpenses(ExpensesDto e){
    QSqlQuery query;
    query.prepare("INSERT INTO 'expenses' (description, price) VALUES (:description, :price)");
    query.bindValue(":description", e.description);
    query.bindValue(":price", e.price);

    if( query.exec() ) return true;
    qDebug() << "ERROR insertExpenses: " << query.lastError().text();
    return false;
}

bool ExpensesService::deleteExpenses(ExpensesDto e){
    QSqlQuery query;
    query.prepare("DELETE FROM expenses WHERE id = :id");
    query.bindValue(":id", e.id);
    if( query.exec() ) return true;
    qDebug() << "ERROR deleteExpenses: " << query.lastError().text();
    return false;
}
