#include "form_mover.h"
#include "ui_form_mover.h"

form_mover::form_mover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_mover)
{
    ui->setupUi(this);
}

form_mover::~form_mover()
{
    delete ui;
}
