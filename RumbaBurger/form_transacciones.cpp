#include "form_transacciones.h"
#include "ui_form_transacciones.h"

form_transacciones::form_transacciones(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_transacciones)
{
    ui->setupUi(this);
}

form_transacciones::~form_transacciones()
{
    delete ui;
}
