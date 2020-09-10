#include "form_getoferta.h"
#include "ui_form_getoferta.h"

form_getOferta::form_getOferta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_getOferta)
{
    ui->setupUi(this);
}

form_getOferta::~form_getOferta()
{
    delete ui;
}

void form_getOferta::on_pb_accept_clicked()
{
    QString oferta = "";
    emit ofertName(oferta);
}
