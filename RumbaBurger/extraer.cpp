#include "extraer.h"
#include "ui_extraer.h"

Extraer::Extraer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Extraer)
{
    ui->setupUi(this);
}

Extraer::~Extraer()
{
    delete ui;
}
