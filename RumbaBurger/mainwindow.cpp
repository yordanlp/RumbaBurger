#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    d = new Dialog(this);
    d->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
