#include "form_modificaroferta.h"
#include "ui_form_modificaroferta.h"

form_modificarOferta::form_modificarOferta(QWidget *parent, QString oferta) :
    QDialog(parent),
    ui(new Ui::form_modificarOferta)
{
    ui->setupUi(this);
    this->oferta = oferta;
}

form_modificarOferta::~form_modificarOferta()
{
    delete ui;
}
