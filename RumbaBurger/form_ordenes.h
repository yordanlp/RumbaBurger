#ifndef FORM_ORDENES_H
#define FORM_ORDENES_H

#include <QDialog>
#include <Dto/orderdto.h>
#include <form_insertarorden.h>

namespace Ui {
class form_ordenes;
}

class form_ordenes : public QDialog
{
    Q_OBJECT

public:
    form_insertarorden *formInsertarOrden;
    explicit form_ordenes(QWidget *parent = 0);
    ~form_ordenes();
    void updateOrders(QList<OrderDto> orders);
    void updatePlatos( int row );


private slots:
    void filtrar();
    void updateIngredients();

    void on_pb_insertarorden_clicked();

    void on_tw_ordenes_clicked(const QModelIndex &index);

    void on_pb_eliminarorden_clicked();

private:
    Ui::form_ordenes *ui;
};

#endif // FORM_ORDENES_H
