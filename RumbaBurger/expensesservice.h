#ifndef EXPENSESSERVICE_H
#define EXPENSESSERVICE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <expensesdto.h>


class ExpensesService
{
public:
    ExpensesService();
    bool insertExpenses(ExpensesDto);
    bool deleteExpenses(ExpensesDto);
    QList<ExpensesDto> getExpensesByDate(QDate start, QDate end);

};

#endif // EXPENSESSERVICE_H
