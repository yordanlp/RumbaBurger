#include "form_ordenes.h"
#include "ui_form_ordenes.h"
#include <Services/orderservice.h>
#include <Services/orderdishservice.h>
#include <QCheckBox>
#include <QMessageBox>

form_ordenes::form_ordenes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_ordenes)
{
    ui->setupUi(this);
    ui->de_final->setDate(QDate::currentDate());
    connect(ui->pb_filtrar,SIGNAL(clicked(bool)), this, SLOT(filtrar()));
    filtrar();
}

form_ordenes::~form_ordenes()
{
    delete ui;
}

void form_ordenes::filtrar(){
    QDate ini = ui->de_inicial->date(), fin = ui->de_final->date();
    if( ini > fin ){
        ui->tw_ordenes->setRowCount(0);
        return;
    }

    OrderService orderService;
    auto orders = orderService.getOrderbyDate(ini, fin);

    updateOrders( orders.data );
    updatePlatos(-1);
}

void form_ordenes::updateOrders( QList<OrderDto> orders ){
    qDebug() << "updateOrders" << orders.size();
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    int row = 0;
    ui->tw_ordenes->setRowCount(orders.size());
    foreach (auto o, orders) {
        QTableWidgetItem *fecha = new QTableWidgetItem(o.date.toString(Qt::ISODate));
        fecha->setFlags(flags);
        QTableWidgetItem *norden = new QTableWidgetItem(QString::number(o.orderNumber));
        norden->setFlags(flags);
        QCheckBox *cb = new QCheckBox(this);
        if( o.payed )
            cb->setChecked(true);
        else cb->setChecked(false);
        cb->setEnabled(false);
        //QTableWidgetItem *pagado = new QTableWidgetItem();
        //pagado->setFlags(flags);
        QTableWidgetItem *ingreso = new QTableWidgetItem("$"+QString::number(o.total));
        ingreso->setFlags(flags);

        ui->tw_ordenes->setItem(row,0, fecha);
        ui->tw_ordenes->setItem(row,1,norden);
        ui->tw_ordenes->setCellWidget(row,2, cb);
        //ui->tw_ordenes->setItem(row,2,pagado);
        ui->tw_ordenes->setItem(row,3,ingreso);
        row++;
    }
}


void form_ordenes::on_pb_insertarorden_clicked()
{
    formInsertarOrden = new form_insertarorden(this);
    formInsertarOrden->show();
    connect(formInsertarOrden, SIGNAL(finished(int)), this, SLOT(filtrar()));
    //filtrar();
}

void form_ordenes::updatePlatos(int row){
    if( row == -1 ){
        ui->tw_platos->setEnabled(false);
        ui->tw_platos->clearContents();
        ui->tw_platos->setRowCount(0);
        return;
    }
    ui->tw_platos->setEnabled(true);
    int orderNumber = ui->tw_ordenes->item(row, 1)->text().toInt();
    QString date = ui->tw_ordenes->item(row, 0)->text();
    OrderService orderService;
    OrderDishService orderDishService;
    DishService dishService;
    auto order = orderService.getOrderByOrderNumberAndDate( orderNumber, utiles::stringToDate(date) );
    auto od = orderDishService.getDishesByOrderId(order.data.id);
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    int fila = 0;
    ui->tw_platos->setRowCount(od.data.size());
    foreach (auto d, od.data) {
        QString nombre = dishService.getDishById(DishDto(d.idDish,"","",0)).data.dishname;
        QTableWidgetItem *name = new QTableWidgetItem(nombre);
        name->setFlags(flags);
        QTableWidgetItem *cant = new QTableWidgetItem( QString::number(d.amount) );
        cant->setFlags(flags);
        QTableWidgetItem *precioxunidad = new QTableWidgetItem( QString::number(d.price) );
        precioxunidad->setFlags(flags);
        QTableWidgetItem *preciototal = new QTableWidgetItem( QString::number(d.price * d.amount) );
        preciototal->setFlags(flags);

        ui->tw_platos->setItem(fila, 0, name);
        ui->tw_platos->setItem(fila, 1, cant);
        ui->tw_platos->setItem(fila, 2, precioxunidad);
        ui->tw_platos->setItem(fila, 3, preciototal);
        fila++;
    }
}

void form_ordenes::on_tw_ordenes_clicked(const QModelIndex &index)
{
    updatePlatos(index.row());
}

void form_ordenes::on_pb_eliminarorden_clicked()
{
    int row = ui->tw_ordenes->currentRow();
    if( row < 0 ) {
        QMessageBox::information(this, "Información", "Debe seleccionar una orden para eliminar",QMessageBox::Ok);
        return;
    }

    int orderNumber = ui->tw_ordenes->item(row, 1)->text().toInt();
    QDate date = utiles::stringToDate(ui->tw_ordenes->item(row, 0)->text());

    OrderService orderService;
    auto ord = orderService.getOrderByOrderNumberAndDate(orderNumber, date);
    orderService.deleteOrder( ord.data );
    filtrar();
}
