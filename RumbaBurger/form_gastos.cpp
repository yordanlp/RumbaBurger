#include "form_gastos.h"
#include "ui_form_gastos.h"
#include <QMessageBox>
#include <Services/expensesservice.h>
#include <utiles.h>
#include <Services/userservice.h>

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

    if( UserService::loggedUser == 0 ){
        ui->pb_eliminar->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
    }
    ui->pb_insertar->setEnabled(false);
}

form_gastos::~form_gastos()
{
    delete ui;
}


void form_gastos::filtrar(){
    QDate inicial = ui->de_inicial->date();
    QDate final = ui->de_final->date();
    ui->pb_eliminar->setEnabled(false);
    if( final < inicial ){
        QMessageBox::information(this, "Información", "La fecha inicial es mayor que la final",QMessageBox::Ok);
        ui->tw_gastos->setRowCount(0);
        expenses.clear();
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
    expenses = gastos.data;
    int row = 0;
    foreach (auto g, expenses) {
        QDate fecha = g.date;
        QTableWidgetItem *date = new QTableWidgetItem( fecha.toString(Qt::ISODate) );
        date->setTextAlignment(utiles::TextAlign);
        date->setFlags(flags);
        QString desc = g.description;
        QTableWidgetItem *descripcion = new QTableWidgetItem (desc);
        descripcion->setTextAlignment(utiles::TextAlign);
        descripcion->setFlags(flags);
        QTableWidgetItem *importe = new QTableWidgetItem("$" + QString::number(g.price, 'f', 2));
        importe->setFlags(flags);
        importe->setTextAlignment(utiles::TextAlign);
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
    if( !costo ){
        QMessageBox::information(this, "Información", "El importe no puede ser 0", QMessageBox::Ok);
        return;
    }
    ExpensesService expensesService;
    expensesService.insertExpenses( ExpensesDto(0,descripcion,costo,fecha) );
    ui->le_descripcion->clear();
    ui->de_fecha->setDate(QDate::currentDate());
    ui->sb_importe->setValue(0);
    filtrar();
}

void form_gastos::on_pb_eliminar_clicked()
{
    int row = ui->tw_gastos->currentRow();
    if( row < 0 ){
        QMessageBox::information(this, "Información", "Debe seleccionar un elemento para eliminar", QMessageBox::Ok);
        return;
    }

    auto res = QMessageBox::information(this, "Información", "¿Está seguro que desea eliminar el elemento seleccionado?", QMessageBox::Ok, QMessageBox::Cancel);

    if( res == QMessageBox::Ok ){
        ExpensesService expensesService;
        expensesService.deleteExpenses( expenses.at(row) );
        filtrar();
    }
}

void form_gastos::on_tw_gastos_clicked(const QModelIndex &index)
{
    ui->pb_eliminar->setEnabled(true);
}

void form_gastos::on_sb_importe_valueChanged(double arg1)
{
    ui->pb_insertar->setEnabled(arg1 > 0);
}
