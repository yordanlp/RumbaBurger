#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QMdiArea>
//#include <form_product.h>
#include <form_almacenes.h>
#include <form_ofertas.h>
#include <form_insertarorden.h>
#include <form_ordenes.h>
#include <form_gastos.h>
#include <form_reportes.h>
#include <form_transacciones.h>
#include <form_inicial.h>
#include <form_newuser.h>
#include <form_user.h>
#include <form_cambiarpassword.h>

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
    //form_product *form_Product;
    form_almacenes *form_Almacenes;
    form_ofertas *formOfertas;
    form_insertarorden *formInsOrden;
    form_ordenes *formOrdenes;
    form_gastos *formGastos;
    form_reportes *formReportes;
    form_transacciones *formTransacciones;
    form_inicial *formInicial;
    form_user *formUser;
    form_cambiarpassword *formCambiarPassword;

private slots:
    void on_actionInsertar_Producto_triggered();

    void on_actionAlmacenes_triggered();

    void on_actionOfertas_triggered();

    void on_actionInsertar_orden_triggered();

    void on_actionMostrarOrden_triggered();

    void on_actionOrdenes_triggered();

    void on_actionGastos_triggered();

    void on_actionEstadisticas_triggered();

    void on_actionTransacciones_triggered();

    void on_actionImpuesto_triggered();

    void on_actionGanancia_triggered();

    void on_actionUnidad_triggered();

    void on_actionMoneda_triggered();

    void on_actionNuevo_usuario_triggered();

    void on_actionAdministrar_triggered();

    void on_actionCerrar_Sesi_n_triggered();

signals:
    void done();
    void ImpuestoChanged();
    void GananciaChnged();
    void UnitChanged();
    void MonedaChanged();

private:
    Ui::Principal *ui;
};

#endif // PRINCIPAL_H
