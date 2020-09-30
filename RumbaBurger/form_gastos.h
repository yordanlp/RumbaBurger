#ifndef FORM_GASTOS_H
#define FORM_GASTOS_H

#include <QDialog>

namespace Ui {
class form_gastos;
}

class form_gastos : public QDialog
{
    Q_OBJECT

public:
    explicit form_gastos(QWidget *parent = 0);
    ~form_gastos();

    void updateGastos();

private slots:

    void filtrar();
    void on_pb_insertar_clicked();



private:
    Ui::form_gastos *ui;
};

#endif // FORM_GASTOS_H
