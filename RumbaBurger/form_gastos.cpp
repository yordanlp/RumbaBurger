#include "form_gastos.h"
#include "ui_form_gastos.h"

form_gastos::form_gastos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_gastos)
{
    ui->setupUi(this);
}

form_gastos::~form_gastos()
{
    delete ui;
}
