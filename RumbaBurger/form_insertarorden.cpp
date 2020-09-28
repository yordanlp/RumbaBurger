#include "form_insertarorden.h"
#include "ui_form_insertarorden.h"

form_insertarorden::form_insertarorden(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_insertarorden)
{
    ui->setupUi(this);
}

form_insertarorden::~form_insertarorden()
{
    delete ui;
}
