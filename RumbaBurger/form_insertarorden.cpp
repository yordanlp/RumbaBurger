#include "form_insertarorden.h"
#include "ui_form_insertarorden.h"
#include <Services/dishservice.h>
#include <QCompleter>
#include <QMessageBox>
#include <Services/orderservice.h>
#include <Services/orderdishservice.h>
#include <Dto/orderdto.h>
#include <Dto/dishamountdto.h>

form_insertarorden::form_insertarorden(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_insertarorden)
{
    ui->setupUi(this);
    DishService dishService;

    QRegExp expNumber ("[0-9]+");
    valNumber = new QRegExpValidator(expNumber,this);
    ui->le_norder->setValidator(valNumber);

    QStringList dishes = dishService.getAllDishToString().data;
    qDebug() << dishes;
    QCompleter *completer = new QCompleter(dishes,this);
    ui->cb_plato->setCompleter(completer);
    ui->cb_plato->addItems(dishes);
    updateCosto();
    ui->de_fecha->setDate(QDate::currentDate());

}

form_insertarorden::~form_insertarorden()
{
    delete ui;
}

void form_insertarorden::on_pb_add_clicked()
{
    //ui->tw_platos->insertRow(ui->tw_platos->rowCount());
    qDebug() << "ins Orden";
    QString dishName = ui->cb_plato->currentText();
    qDebug() << dishName;
    int ok = 1;
    for( int i = 0; i < ui->tw_platos->rowCount(); i++ ){
        if( ui->tw_platos->item(i, 0)->text() == dishName ){
            ok = 0;
            break;
        }
    }
    if( !ok ){
        QMessageBox::information(this,"Información","El plato " + dishName + " ya existe en la orden",QMessageBox::Ok);
        return;
    }

    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    ui->tw_platos->insertRow(ui->tw_platos->rowCount());
    int row = ui->tw_platos->rowCount()-1;
    int cantidad = ui->sb_cantidad->value();
    DishService dishService;
    auto dish = dishService.getDishByName(DishDto(0,dishName,"",0));
    double precio = dish.data.price;

    QTableWidgetItem *nombre = new QTableWidgetItem(dishName);
    nombre->setFlags(flags);
    QTableWidgetItem *cant = new QTableWidgetItem( QString::number(cantidad) );
    cant->setFlags(flags);
    QTableWidgetItem *precioxunidad = new QTableWidgetItem( "$" + QString::number(precio, 'f', 2) );
    precioxunidad->setFlags(flags);
    QTableWidgetItem *preciototal = new QTableWidgetItem( "$" + QString::number( precio * cantidad, 'f', 2 ) );
    preciototal->setFlags(flags);

    ui->tw_platos->setItem(row, 0, nombre);
    ui->tw_platos->setItem(row, 1, cant);
    ui->tw_platos->setItem(row, 2, precioxunidad);
    ui->tw_platos->setItem(row, 3, preciototal);

    ui->sb_cantidad->setValue(0);
    updateCosto();
}

void form_insertarorden::on_pb_del_clicked()
{
    int rowSelected = ui->tw_platos->currentRow();
    qDebug() << rowSelected;

    if( rowSelected >= 0 && rowSelected < ui->tw_platos->rowCount() ){
        ui->tw_platos->removeRow(rowSelected);
    }
    updateCosto();
}

double form_insertarorden::getCosto(){
    double total = 0;
    for( int i = 0; i < ui->tw_platos->rowCount(); i++ ){
        total += ui->tw_platos->item(i, 3)->text().remove(0,1).toDouble();
    }
    return total;
}

void form_insertarorden::updateCosto(){
    double total = 0;
    qDebug() << "Update Costo";
    total = getCosto();
    ui->l_costo->setText( "El costo total de la orden es: $" + QString::number(total, 'f', 2) );
}

double form_insertarorden::getProfit(){
    double total = 0;
    DishService dishService;
    for( int i = 0; i < ui->tw_platos->rowCount(); i++ ){
        QString dishName = ui->tw_platos->item(i, 0)->text();
        int cantidad = ui->tw_platos->item(i,1)->text().toDouble();
        auto dish = dishService.getDishByName(DishDto(0, dishName,"",0));
        double precio = dish.data.price;
        double precioProduction = dishService.getPrecioProduccion(dish.data.id).data;
        total += (cantidad * precio - cantidad * precioProduction);
    }
    return total;
}

void form_insertarorden::on_pb_accep_clicked()
{

    QString num = ui->le_norder->text();
    int pos = 0;
    if( valNumber->validate(num,pos) != QValidator::Acceptable ){
        QMessageBox::information(this,"Información", "El número de orden no es válido",QMessageBox::Ok);
        return;
    }
    int orderNumber = ui->le_norder->text().toInt();
    qDebug() << "orderNumber" << orderNumber;
    QDate today = ui->de_fecha->date();
    OrderService orderService;
    OrderDishService orderDishService;
    DishService dishService;
    if( orderService.existOrderNumber(orderNumber, today).data ){
        QMessageBox::information(this, "Información", "La orden " + QString::number(orderNumber) + " ya existe",QMessageBox::Ok);
        return;
    }

    double costo = getCosto();
    double profit = getProfit();
    bool payed = !ui->cb_excento->isChecked();

    QList<DishAmountDto> L;
    for( int i = 0; i < ui->tw_platos->rowCount(); i++ ){
        QString dishName = ui->tw_platos->item(i,0)->text();
        int cantidad = ui->tw_platos->item(i,1)->text().toInt();
        auto d = dishService.getDishByName(DishDto(0,dishName,"",0));
        DishAmountDto da(d.data.id, cantidad);
        L << da;
    }

    auto val = orderService.validateDishes(L);
    if( val.res == INSUFICIENT_AMOUNT ){
        QString msg;
        msg = "Cantidad insuficiente de productos:\n ";
        foreach (auto i, val.data) {
            msg += i + "\n";
        }
        QMessageBox::information(this, "Información", msg, QMessageBox::Ok);
        return;
    }


    OrderDto order(0,today,costo,profit,payed,orderNumber, 0);
    auto o = orderService.insertOrder(order);

    orderDishService.insertOrderDishes(o.data,L);

    double inversion = orderService.calcularInversion(o.data).data;

    order.id = o.data;
    order.inversion = inversion;
    orderService.updateOrder(order);

    close();
}

void form_insertarorden::on_pb_cancel_clicked()
{
    close();
}
