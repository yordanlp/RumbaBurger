#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->user->setText("William");
    ui->pass->setText("Hola");
}

Login::~Login()
{
    delete ui;
}

void Login::on_ok_clicked()
{
    hide();
    MainWindow *w = new MainWindow(this);
    w->show();
}
