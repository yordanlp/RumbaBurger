#include "form_eliminaroferta.h"
#include "ui_form_eliminaroferta.h"

form_eliminarOferta::form_eliminarOferta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_eliminarOferta)
{
    ui->setupUi(this);
}

form_eliminarOferta::~form_eliminarOferta()
{
    delete ui;
}
