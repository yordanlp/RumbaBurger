#include "principal.h"
#include "ui_principal.h"
#include <QDebug>
#include <QLabel>

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    mdi = new QMdiArea(this);
    setCentralWidget(mdi);
    QLabel *label = new QLabel("Status Bar", this);
    ui->statusbar->addWidget(label);

}

Principal::~Principal()
{
    delete ui;
}

//insertar producto
void Principal::on_actionInsertar_Producto_triggered()
{
    /*form_Product = new form_product(this);
    form_Product->setModal(true);
    form_Product->show();*/

}

void Principal::on_actionAlmacenes_triggered()
{
    mdi->closeAllSubWindows();
    form_Almacenes = new form_almacenes(this);
    mdi->addSubWindow(form_Almacenes);
    qDebug() << "here";
    form_Almacenes->showMaximized();
}

void Principal::on_actionOfertas_triggered()
{
    formOfertas = new form_ofertas(this);
    mdi->closeAllSubWindows();
    mdi->addSubWindow(formOfertas);
    formOfertas->showMaximized();
}

void Principal::on_actionInsertar_orden_triggered()
{
    formInsOrden = new form_insertarorden(this);
    formInsOrden->show();
}

void Principal::on_actionMostrarOrden_triggered()
{
    qDebug() << "mostrar ordenes";
    mdi->closeAllSubWindows();
    formOrdenes = new form_ordenes(this);
    mdi->addSubWindow(formOrdenes);
    formOrdenes->showMaximized();
}

void Principal::on_actionOrdenes_triggered()
{
    on_actionMostrarOrden_triggered();

}

void Principal::on_actionGastos_triggered()
{
    qDebug() << "mostrar gastos";
    mdi->closeAllSubWindows();
    formGastos = new form_gastos(this);
    mdi->addSubWindow(formGastos);
    formGastos->showMaximized();
}

void Principal::on_actionEstadisticas_triggered()
{
    qDebug() << "mostrar reportes";
    mdi->closeAllSubWindows();
    formReportes = new form_reportes(this);
    mdi->addSubWindow(formReportes);
    formReportes->showMaximized();
}

void Principal::on_actionTransacciones_triggered()
{

}
