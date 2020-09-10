#include "form_extraer.h"
#include "ui_form_extraer.h"

form_extraer::form_extraer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_extraer)
{
    ui->setupUi(this);
}

form_extraer::~form_extraer()
{
    delete ui;
}
