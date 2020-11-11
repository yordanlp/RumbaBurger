#include "form_reportes.h"
#include "ui_form_reportes.h"
#include <QMessageBox>
#include <Services/orderdishservice.h>
#include <Services/expensesservice.h>
#include <Services/dishversionsservice.h>
#include <QCheckBox>

form_reportes::form_reportes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_reportes)
{
    ui->setupUi(this);
    ui->de_final->setMaximumDate(QDate::currentDate());
    ui->de_final->setDate( QDate::currentDate() );
    connect(ui->pb_filtrar, SIGNAL(clicked(bool)), this, SLOT(filtrar()));
    connect(ui->cb_orden, SIGNAL(currentIndexChanged(int)), this, SLOT(updateVentasBySort()));
    filtrar();
    ui->tw_gastos->setColumnWidth(1, 300);
    ui->tw_ventas->setColumnWidth(0, ui->tw_ventas->columnWidth(0) + 100);

}

form_reportes::~form_reportes()
{
    delete ui;
}

void form_reportes::updateImpuesto(){
    updateTotal();
}

void form_reportes::filtrar(){
    QDate inicial = ui->de_inicial->date();
    QDate final = ui->de_final->date();
    if( inicial > final ){
        QMessageBox::information(this, "Información", "La fecha final no puede ser menor que la inicial", QMessageBox::Ok);
        ui->tw_gastos->clearContents();
        ui->tw_gastos->setRowCount(0);
        ui->tw_ordenes->clearContents();
        ui->tw_ordenes->setRowCount(0);
        ui->l_ganancia->setText("Ganancia: 0 CUP");
        ui->l_ganancianeta->setText("Ganancia Neta: 0 CUP");
        ui->l_importeeventos->setText("Total Eventos: 0 CUP");
        ui->l_ingresos->setText("Ingresos: 0 CUP");
        ui->l_inversion->setText("Inversión: 0 CUP");
        ui->l_onat->setText("ONAT: 0 CUP");
        ui->l_toralordenes->setText("Total: 0");
        //ui->l_totaleventos->setText("Total: 0");
        return;
    }
    updateOrdenes();
    updateGastos();
    updateTotal();
    updateVentas();
}

void form_reportes::updateOrdenes(){

    OrderService orderService;
    QDate start = ui->de_inicial->date(), end = ui->de_final->date();
    auto orders = orderService.getOrderbyDate(start, end);
    int row = 0;
    ui->tw_ordenes->setRowCount(orders.data.size());
    Tinversion = 0, Tingresos = 0, Tganancia = 0;

    foreach (auto o, orders.data) {
        QDate date = o.date;
        QTableWidgetItem *fecha = new QTableWidgetItem( date.toString(Qt::ISODate) );
        fecha->setTextAlignment(utiles::TextAlign);
        fecha->setFlags(flags);

        QTableWidgetItem *numorden = new QTableWidgetItem( QString::number(o.orderNumber) );
        numorden->setTextAlignment(utiles::TextAlign);
        numorden->setFlags(flags);

        QString pagado = "";
        if( o.payed )
           pagado = "SI";
        else pagado = "NO";
        QTableWidgetItem *payed = new QTableWidgetItem( pagado );
        payed->setFlags(flags);
        payed->setTextAlignment(utiles::TextAlign);
        ui->tw_ordenes->setItem(row, 2, payed);
        QTableWidgetItem *inversion = new QTableWidgetItem( QString::number( orderService.getInversion(o.id).data, 'f', 2 ) + " CUP" );
        inversion->setTextAlignment(utiles::TextAlign);
        inversion->setFlags(flags);

        QTableWidgetItem *ingresos = new QTableWidgetItem( QString::number(o.total, 'f', 2) + " CUP" );
        ingresos->setTextAlignment(utiles::TextAlign);
        ingresos->setFlags(flags);


        QTableWidgetItem *ganancia = new QTableWidgetItem( QString::number(o.profit, 'f', 2) + " CUP" );
        if( o.profit < 0 )
            ganancia->setTextColor(QColor("red"));

        ganancia->setTextAlignment(utiles::TextAlign);
        ganancia->setFlags(flags);

        ui->tw_ordenes->setItem(row, 0, fecha);
        ui->tw_ordenes->setItem(row, 1, numorden);
        ui->tw_ordenes->setItem(row, 3, inversion);
        ui->tw_ordenes->setItem(row, 4, ingresos);
        ui->tw_ordenes->setItem(row, 5, ganancia);
        row++;

        Tinversion += orderService.getInversion( o.id ).data;
        Tingresos += o.total;
        Tganancia += orderService.getGanancia(o.id).data;


    }

    ui->l_toralordenes->setText("Ordenes: " + QString::number(orders.data.size()));
    ui->l_inversion->setText("Inversión: " + QString::number(Tinversion, 'f', 2) + " CUP");
    ui->l_ingresos->setText("Ingresos: " + QString::number(Tingresos,  'f', 2) + " CUP");
    ui->l_ganancia->setText(QString::number(Tganancia, 'f', 2) + " CUP");
    if( Tganancia < 0 )
        ui->l_ganancia->setStyleSheet("QLabel { color : red; }");
}

void form_reportes::updateGastos(){
    ExpensesService expensesService;
    QDate start = ui->de_inicial->date(), end = ui->de_final->date();
    auto ex = expensesService.getExpensesByDate(start, end);
    int row = 0;
    ui->tw_gastos->setRowCount(ex.data.size());
    Tgastos = 0;
    foreach (auto e, ex.data) {
        QDate date = e.date;
        QTableWidgetItem *fecha = new QTableWidgetItem( date.toString(Qt::ISODate) );
        fecha->setTextAlignment(utiles::TextAlign);
        fecha->setFlags(flags);

        QTableWidgetItem *descripcion = new QTableWidgetItem( e.description );
        descripcion->setTextAlignment(utiles::TextAlign);
        descripcion->setFlags(flags);

        QTableWidgetItem *importe = new QTableWidgetItem( QString::number(e.price, 'f', 2) + " CUP" );
        importe->setTextAlignment(utiles::TextAlign);
        importe->setFlags(flags);

        ui->tw_gastos->setItem(row, 0, fecha);
        ui->tw_gastos->setItem(row, 1, descripcion);
        ui->tw_gastos->setItem(row, 2, importe);
        Tgastos += e.price;
        row++;
    }
    ui->l_importeeventos->setText("Total Eventos: " + QString::number(Tgastos, 'f', 2) + " CUP");
    //ui->l_totaleventos->setText("Total: " + QString::number( ex.data.size() ));
}

void form_reportes::updateTotal(){
    ui->l_onat->setText("Impuesto de la ONAT: " + QString::number( utiles::IMPUESTO * Tingresos, 'f', 2) + " CUP");
    ui->l_ganancianeta->setText(QString::number( Tganancia - Tgastos, 'f', 2 ) + " CUP");
    double neta = Tganancia - Tgastos;
    if( neta < 0 )
        ui->l_ganancianeta->setStyleSheet("QLabel { color : red; }");
}

QVector<VentasModel> form_reportes::getVentasModel(QDate ini, QDate fin){
    int days = ini.daysTo(fin) + 1;
    QVector<VentasModel> ret;
    QMap<QString, VentasModel>modelMap;

    OrderService orderService;
    OrderDishService orderDishService;
    DishVersionsService dishVersionsService;
    DishService dishService;
    VentasModel current;
    auto orders = orderService.getOrderbyDate(ini, fin);
    qDebug() << "num orders" << orders.data.size();
    foreach (auto order, orders.data) {
        auto dishes = orderDishService.getDishesByOrderId( order.id );
        foreach (auto d, dishes.data) {
            auto dish = dishVersionsService.getDishById(d.idDish);
            qDebug() << "dishname" << dish.data.dishname;
            if( !modelMap.count(dish.data.dishname) ){
                current = VentasModel();
                current.dishName = dish.data.dishname;
                current.ventas = d.amount;
                current.inversion = dishService.productionCost(dish.data.id).data * d.amount;
                current.ingresos = (order.payed) ? d.price * d.amount : 0;
                current.maxId = d.idDish;
                modelMap[dish.data.dishname] = current;
            }
            else{
                current = modelMap[dish.data.dishname];
                current.ventas += d.amount;
                current.inversion += dishService.productionCost(dish.data.id).data * d.amount;
                current.ingresos += (order.payed) ? d.price * d.amount : 0;
                current.maxId = max(current.maxId, d.idDish);
                modelMap[dish.data.dishname] = current;
            }
        }
    }
    qDebug() << "mapa size" << modelMap.size();
    foreach (auto i, modelMap.values()) {
        current = i;
        current.ganancia = current.ingresos - current.inversion;
        current.promedioVentas = current.ventas / (double)days;
        //current.orderBy = ui->cb_orden->currentIndex();
        ret.push_back(current);
        //current.cobertura = dishService.getCobertura( current.maxId ).data;
    }

    return ret;
}

void form_reportes::sortVentasModel(QVector<VentasModel> &v){
    for(auto &i : v){
        i.orderBy = ui->cb_orden->currentIndex();;
    }
    sort(v.begin(), v.end());
}

void form_reportes::updateVentasBySort(){
    sortVentasModel(ventasModel);
    fillVentasTable();
}

void form_reportes::fillVentasTable(){
    ui->tw_ventas->clearContents();
    ui->tw_ventas->setRowCount(ventasModel.size());
    qDebug() << "ventas Model" << ventasModel.size();
    int row = 0;
    foreach (VentasModel i, ventasModel) {
        QTableWidgetItem *oferta = new QTableWidgetItem( i.dishName );
        oferta->setFlags(flags);
        oferta->setTextAlignment(utiles::TextAlign);

        QTableWidgetItem *ventas = new QTableWidgetItem( QString::number(i.ventas) );
        ventas->setFlags(flags);
        ventas->setTextAlignment(utiles::TextAlign);

        QTableWidgetItem *inversion = new QTableWidgetItem( QString::number(i.inversion, 'f', 2) + " CUP");
        inversion->setFlags(flags);
        inversion->setTextAlignment(utiles::TextAlign);

        QTableWidgetItem *ingresos = new QTableWidgetItem( QString::number(i.ingresos, 'f', 2) + " CUP");
        ingresos->setFlags(flags);
        ingresos->setTextAlignment(utiles::TextAlign);

        QTableWidgetItem *ganancia = new QTableWidgetItem( QString::number(i.ganancia, 'f', 2) + " CUP");
        ganancia->setFlags(flags);
        ganancia->setTextAlignment(utiles::TextAlign);

        QTableWidgetItem *promedio = new QTableWidgetItem( QString::number(i.promedioVentas, 'f', 2) );
        promedio->setFlags(flags);
        promedio->setTextAlignment(utiles::TextAlign);

        QTableWidgetItem *cobertura = new QTableWidgetItem( i.cobertura );
        cobertura->setFlags(flags);
        cobertura->setTextAlignment(utiles::TextAlign);

        ui->tw_ventas->setItem(row, 0, oferta);
        ui->tw_ventas->setItem(row, 1, ventas);
        ui->tw_ventas->setItem(row, 2, inversion);
        ui->tw_ventas->setItem(row, 3, ingresos);
        ui->tw_ventas->setItem(row, 4, ganancia);
        ui->tw_ventas->setItem(row, 5, promedio);
        ui->tw_ventas->setItem(row, 6, cobertura);
        row++;
    }
}

void form_reportes::updateVentas(){
    QDate ini = ui->de_inicial->date(), fin = ui->de_final->date();
    int days = ini.daysTo(fin) + 1;
    ui->l_cantidaddedias->setText("Cantidad de días:" + QString::number(days));
    ventasModel = getVentasModel(ini, fin);
    sortVentasModel( ventasModel );
    fillVentasTable();
}
