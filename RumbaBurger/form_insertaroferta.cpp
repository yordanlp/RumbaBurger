#include "form_insertaroferta.h"
#include "ui_form_insertaroferta.h"

form_insertarOferta::form_insertarOferta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_insertarOferta)
{
    ui->setupUi(this);
}

form_insertarOferta::~form_insertarOferta()
{
    delete ui;
}
