#include "form_reportes.h"
#include "ui_form_reportes.h"
#include <QMessageBox>
#include <Services/orderdishservice.h>
#include <Services/expensesservice.h>
#include <QCheckBox>

form_reportes::form_reportes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_reportes)
{
    ui->setupUi(this);
    ui->de_final->setMaximumDate(QDate::currentDate());
    ui->de_final->setDate( QDate::currentDate() );
    connect(ui->pb_filtrar, SIGNAL(clicked(bool)), this, SLOT(filtrar()));
    filtrar();

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
        ui->l_importeeventos->setText("Importe");
        ui->l_ingresos->setText("Ingresos: 0 CUP");
        ui->l_inversion->setText("Inversión: 0 CUP");
        ui->l_onat->setText("ONAT: 0 CUP");
        ui->l_toralordenes->setText("Total: 0");
        ui->l_totaleventos->setText("Total: 0");
        return;
    }
    updateOrdenes();
    updateGastos();
    updateTotal();
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

        QCheckBox *pagado = new QCheckBox(this);
        if( o.payed )
           pagado->setChecked( o.payed );
        pagado->setEnabled(false);
        ui->tw_ordenes->setCellWidget(row, 2,pagado);

        QTableWidgetItem *inversion = new QTableWidgetItem( utiles::truncS( orderService.getInversion(o.id).data, 2 ) + " CUP" );
        inversion->setTextAlignment(utiles::TextAlign);
        inversion->setFlags(flags);

        QTableWidgetItem *ingresos = new QTableWidgetItem( utiles::truncS(o.total, 2) + " CUP" );
        ingresos->setTextAlignment(utiles::TextAlign);
        ingresos->setFlags(flags);

        QTableWidgetItem *ganancia = new QTableWidgetItem( utiles::truncS(o.profit, 2) + " CUP" );
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
    ui->l_inversion->setText("Inversión: " + utiles::truncS(Tinversion, 2) + " CUP");
    ui->l_ingresos->setText("Ingresos: " + utiles::truncS(Tingresos,  2) + " CUP");
    ui->l_ganancia->setText("Ganancia: " + utiles::truncS(Tganancia, 2) + " CUP");
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

        QTableWidgetItem *importe = new QTableWidgetItem( utiles::truncS(e.price, 2) + " CUP" );
        importe->setTextAlignment(utiles::TextAlign);
        importe->setFlags(flags);

        ui->tw_gastos->setItem(row, 0, fecha);
        ui->tw_gastos->setItem(row, 1, descripcion);
        ui->tw_gastos->setItem(row, 2, importe);
        Tgastos += e.price;
        row++;
    }
    ui->l_importeeventos->setText("Importe: " + utiles::truncS(Tgastos, 2) + " CUP");
    ui->l_totaleventos->setText("Total: " + QString::number( ex.data.size() ));
}

void form_reportes::updateTotal(){
    ui->l_onat->setText("Impuesto de la ONAT: " + utiles::truncS( utiles::IMPUESTO * Tingresos, 2) + " CUP");
    ui->l_ganancianeta->setText("Ganancia Neta: " + utiles::truncS( Tganancia - Tgastos, 2 ) + " CUP");
}
