#include "principal.h"
#include "ui_principal.h"
#include <QDebug>

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    mdi = new QMdiArea(this);
    setCentralWidget(mdi);

}

Principal::~Principal()
{
    delete ui;
}

//insertar producto
void Principal::on_actionInsertar_Producto_triggered()
{
    form_Product = new form_product(this);
    form_Product->setModal(true);
    form_Product->show();

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

}
