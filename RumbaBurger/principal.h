#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QMdiArea>
#include <form_product.h>
#include <form_almacenes.h>
#include <form_ofertas.h>
#include <form_insertarorden.h>
#include <form_ordenes.h>

namespace Ui {
class Principal;
}


class Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();
    QMdiArea *mdi;
    form_product *form_Product;
    form_almacenes *form_Almacenes;
    form_ofertas *formOfertas;
    form_insertarorden *formInsOrden;
    form_ordenes *formOrdenes;

private slots:
    void on_actionInsertar_Producto_triggered();

    void on_actionAlmacenes_triggered();

    void on_actionOfertas_triggered();

    void on_actionInsertar_orden_triggered();

    void on_actionMostrarOrden_triggered();

    void on_actionOrdenes_triggered();

    void on_actionGastos_triggered();

private:
    Ui::Principal *ui;
};

#endif // PRINCIPAL_H
