#ifndef EXPENSESSERVICE_H
#define EXPENSESSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <expensesdto.h>
#include "result.h"

class ExpensesService
{
public:
    ExpensesService();
    Result<bool> insertExpenses(ExpensesDto);
    Result<bool> deleteExpenses(ExpensesDto);
    Result<QList<ExpensesDto>> getExpensesByDate(QDate start, QDate end);

};

#endif // EXPENSESSERVICE_H
