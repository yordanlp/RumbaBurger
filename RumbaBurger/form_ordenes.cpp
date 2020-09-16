#include "form_ordenes.h"
#include "ui_form_ordenes.h"

form_ordenes::form_ordenes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_ordenes)
{
    ui->setupUi(this);
}

form_ordenes::~form_ordenes()
{
    delete ui;
}
