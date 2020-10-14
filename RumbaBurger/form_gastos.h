#ifndef FORM_GASTOS_H
#define FORM_GASTOS_H

#include <QDialog>
#include <Dto/expensesdto.h>

namespace Ui {
class form_gastos;
}

class form_gastos : public QDialog
{
    Q_OBJECT

public:
    explicit form_gastos(QWidget *parent = 0);
    ~form_gastos();
    QList<ExpensesDto> expenses;

    void updateGastos();


private slots:

    void filtrar();
    void on_pb_insertar_clicked();



    void on_pb_eliminar_clicked();

    void on_tw_gastos_clicked(const QModelIndex &index);

    void on_sb_importe_valueChanged(double arg1);

private:
    Ui::form_gastos *ui;
};

#endif // FORM_GASTOS_H
