#include "form_gastos.h"
#include "ui_form_gastos.h"
#include <QMessageBox>
#include <Services/expensesservice.h>

form_gastos::form_gastos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_gastos)
{
    ui->setupUi(this);
    ui->de_final->setDate(QDate::currentDate());
    ui->de_fecha->setDate(QDate::currentDate());
    ui->de_final->setMaximumDate(QDate::currentDate());
    ui->de_fecha->setMaximumDate(QDate::currentDate());
    filtrar();
    connect(ui->pb_filtrar, SIGNAL(clicked(bool)), this, SLOT(filtrar()));
}

form_gastos::~form_gastos()
{
    delete ui;
}


void form_gastos::filtrar(){
    QDate inicial = ui->de_inicial->date();
    QDate final = ui->de_final->date();
    if( final < inicial ){
        QMessageBox::information(this, "Información", "La fecha inicial es mayor que la final",QMessageBox::Ok);
        ui->tw_gastos->setRowCount(0);
        return;
    }
    updateGastos();
}

void form_gastos::updateGastos(){
    ExpensesService expensesService;
    QDate inicial = ui->de_inicial->date();
    QDate final = ui->de_final->date();
    auto gastos = expensesService.getExpensesByDate(inicial, final);
    ui->tw_gastos->setRowCount(gastos.data.size());
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    int row = 0;
    foreach (auto g, gastos.data) {
        QDate fecha = g.date;
        QTableWidgetItem *date = new QTableWidgetItem( fecha.toString(Qt::ISODate) );
        date->setFlags(flags);
        QString desc = g.description;
        QTableWidgetItem *descripcion = new QTableWidgetItem (desc);
        descripcion->setFlags(flags);
        QTableWidgetItem *importe = new QTableWidgetItem(QString::number(g.price));
        importe->setFlags(flags);

        ui->tw_gastos->setItem(row, 0, date);
        ui->tw_gastos->setItem(row, 1, descripcion);
        ui->tw_gastos->setItem(row, 2, importe);
        row++;
    }
}


void form_gastos::on_pb_insertar_clicked()
{
    QString descripcion = ui->le_descripcion->text();
    QDate fecha = ui->de_fecha->date();
    double costo = ui->sb_importe->value();
    ExpensesService expensesService;
    expensesService.insertExpenses( ExpensesDto(0,descripcion,costo,fecha) );
    ui->le_descripcion->clear();
    ui->de_fecha->setDate(QDate::currentDate());
    ui->sb_importe->setValue(0);
    filtrar();
}
