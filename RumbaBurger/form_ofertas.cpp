#include "form_ofertas.h"
#include "ui_form_ofertas.h"

form_ofertas::form_ofertas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_ofertas)
{
    ui->setupUi(this);
}

form_ofertas::~form_ofertas()
{
    delete ui;
}
