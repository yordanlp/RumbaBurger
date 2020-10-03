#include "form_ordenes.h"
#include "ui_form_ordenes.h"
#include <Services/orderservice.h>
#include <Services/orderdishservice.h>
#include <QCheckBox>
#include <QMessageBox>
#include <Services/dishversionsservice.h>

form_ordenes::form_ordenes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_ordenes)
{
    ui->setupUi(this);
    ui->de_final->setDate(QDate::currentDate());
    connect(ui->pb_filtrar,SIGNAL(clicked(bool)), this, SLOT(filtrar()));
    connect(ui->tw_platos, SIGNAL(cellClicked(int,int)), this, SLOT(updateIngredients()));
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
        updateOrders(QList<OrderDto>());
        return;
    }

    OrderService orderService;
    auto orders = orderService.getOrderbyDate(ini, fin);

    updateOrders( orders.data );


}

void form_ordenes::updateIngredients(){
    int orderRow = ui->tw_ordenes->currentRow();
    int dishRow = ui->tw_platos->currentRow();
    qDebug() << "ingredientes" << orderRow << dishRow;
    if( orderRow < 0 || dishRow < 0 ){
        ui->tw_ingredientes->clearContents();
        ui->tw_ingredientes->setRowCount(0);;
        ui->tw_ingredientes->setEnabled(false);
        return;
    }
    ui->tw_ingredientes->setEnabled(true);

    OrderService orderService;
    DishVersionsService dishVersionsService;
    IngredientsService ingredientsService;
    OrderDishService orderDishService;
    DishService dishService;
    int orderNumber = ui->tw_ordenes->item(orderRow, 1)->text().toInt();
    QDate orderDate = utiles::stringToDate(ui->tw_ordenes->item(orderRow, 0)->text());
    auto order = orderService.getOrderByOrderNumberAndDate(orderNumber, orderDate);
    QString dishName = ui->tw_platos->item(dishRow,0)->text();
    auto dish = dishVersionsService.getDishByOrderAndName(order.data.id, dishName);
    IngredientsDto idto;
    idto.idDish = dish.data.id;
    auto ingredients = ingredientsService.getIngredientsByDishId(idto);

    ProductService productService;
    ui->tw_ingredientes->setRowCount(ingredients.data.size());
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    int row = 0;
    foreach (auto i, ingredients.data) {
        ProductDto p;
        p.id = i.idProduct;
        QString productName = productService.getProductByID(p).data.productName;
        double amount = i.amount;
        QTableWidgetItem *name = new QTableWidgetItem(productName);
        name->setFlags(flags);
        QTableWidgetItem *cant = new QTableWidgetItem(QString::number(amount));
        cant->setFlags(flags);

        ui->tw_ingredientes->setItem(row, 0, name);
        ui->tw_ingredientes->setItem(row, 1, cant);
        row++;
    }

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
    updatePlatos(-1);
}


void form_ordenes::on_pb_insertarorden_clicked()
{
    formInsertarOrden = new form_insertarorden(this);
    formInsertarOrden->setModal(true);
    formInsertarOrden->show();
    connect(formInsertarOrden, SIGNAL(finished(int)), this, SLOT(filtrar()));
    //filtrar();
}

void form_ordenes::updatePlatos(int row){
    if( row == -1 ){
        ui->tw_platos->setEnabled(false);
        ui->tw_platos->clearContents();
        ui->tw_platos->setRowCount(0);
        updateIngredients();
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
    DishVersionsService dishVersionsService;
    foreach (auto d, od.data) {
        QString nombre = dishVersionsService.getDishById(d.idDish).data.dishname;
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
    updateIngredients();
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

/*void form_ordenes::on_pb_modificarorden_clicked()
{
    int row = ui->tw_ordenes->currentRow();
    if( row < 0 ){
        QMessageBox::information(this, "Información","Debe seleccionar una orden para modificar", QMessageBox::Ok);
        return;
    }

    OrderService orderService;
    int orderNumber = ui->tw_ordenes->item(row, 1)->text().toInt();
    QDate date = utiles::stringToDate( ui->tw_ordenes->item(row, 0)->text() );
    auto order = orderService.getOrderByOrderNumberAndDate(orderNumber, date);

    formModificarOrden = new form_modificarorden(this, order.data.id);
    formModificarOrden->show();
    connect( formModificarOrden, SIGNAL(done()), this, SLOT(filtrar()) );
}*/
