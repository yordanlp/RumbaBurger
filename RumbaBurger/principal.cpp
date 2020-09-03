#include "principal.h"
#include "ui_principal.h"
#include "mainwindow.h"

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    mdi = new QMdiArea(this);
    setCentralWidget(mdi);

    MainWindow *mw = new MainWindow();
    mdi->addSubWindow(mw);

}

Principal::~Principal()
{
    delete ui;
}
