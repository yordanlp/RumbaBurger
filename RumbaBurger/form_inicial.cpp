#include "form_inicial.h"
#include "ui_form_inicial.h"
#include <QtCore>
#include <QtWidgets>

form_inicial::form_inicial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_inicial)
{
    ui->setupUi(this);
}


form_inicial::~form_inicial()
{
    delete ui;
}
