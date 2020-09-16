#include "form_almacenes.h"
#include "ui_form_almacenes.h"
#include "Services/centralstorageservice.h"
#include <Services/storageservice.h>

form_almacenes::form_almacenes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_almacenes)
{
    ui->setupUi(this);
    updateCentralTable("");
    updateLocalTable("");
}

form_almacenes::~form_almacenes()
{
    delete ui;
}

void form_almacenes::on_pb_newProduct_clicked()
{
    ui->mdiCentral->closeAllSubWindows();
    formProduct = new form_product(this);
    connect(formProduct,SIGNAL(done()),this,SLOT(clearCentralMdi()));
    ui->mdiCentral->addSubWindow(formProduct);
    formProduct->show();
    updateCentralTable(ui->le_Centralsearch->text());
}

void form_almacenes::updateCentralTable(QString search){
    qDebug() << "update central";
    centralStorageService CentralStorageService;
    auto res = CentralStorageService.getCentralStorageBySearch( utiles::searchToRegExp(search) ).data;
    ui->centralTable->clearContents();
    ui->centralTable->setRowCount(res.size());
    int row = 0;
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    foreach (auto i, res) {
        QTableWidgetItem *producto = new QTableWidgetItem(i.name);
        producto->setFlags(flags);
        QTableWidgetItem *price = new QTableWidgetItem("$" + QString::number(i.price));
        price->setFlags(flags);
        QTableWidgetItem *amount = new QTableWidgetItem(QString::number(i.amount) + utiles::unitFromNumber(i.unitType));
        amount->setFlags(flags);
        ui->centralTable->setItem(row, 0, producto);
        ui->centralTable->setItem(row, 1, amount);
        ui->centralTable->setItem(row, 2, price);
        row++;
    }
}

void form_almacenes::updateLocalTable(QString search){
    qDebug() << "update central";
    storageService LocalStorageService;
    auto res = LocalStorageService.getLocalStorageBySearch( utiles::searchToRegExp(search) ).data;
    ui->localTable->clearContents();
    ui->localTable->setRowCount(res.size());
    int row = 0;
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    foreach (auto i, res) {
        QTableWidgetItem *producto = new QTableWidgetItem(i.name);
        QTableWidgetItem *price = new QTableWidgetItem("$" + QString::number(i.price));
        QTableWidgetItem *amount = new QTableWidgetItem(QString::number(i.amount) + utiles::unitFromNumber(i.unitType));
        producto->setFlags(flags);
        amount->setFlags(flags);
        price->setFlags(flags);
        ui->localTable->setItem(row, 0, producto);
        ui->localTable->setItem(row, 1, amount);
        ui->localTable->setItem(row, 2, price);
        row++;
    }
}


void form_almacenes::on_le_Centralsearch_textChanged(const QString &search)
{
    updateCentralTable(search);
}

void form_almacenes::on_le_localSearch_textChanged(const QString &arg1)
{
    updateLocalTable(arg1);
}

void form_almacenes::on_pb_compra_clicked()
{
    ui->mdiCentral->closeAllSubWindows();
    formCompra = new form_compra(this);
    ui->mdiCentral->addSubWindow(formCompra);
    connect(formCompra,SIGNAL(done()),this,SLOT(clearCentralMdi()));
    formCompra->show();
    updateCentralTable(ui->le_localSearch->text());
}

void form_almacenes::clearCentralMdi()
{
    ui->mdiCentral->closeAllSubWindows();
    updateCentralTable(ui->le_Centralsearch->text());
    updateLocalTable(ui->le_localSearch->text());
}

void form_almacenes::on_pb_moveToLocal_clicked()
{
    ui->mdiCentral->closeAllSubWindows();
    formMover = new form_mover(this);
    ui->mdiCentral->addSubWindow(formMover);
    connect(formMover,SIGNAL(done()), this, SLOT(clearCentralMdi()));
    formMover->show();
    updateCentralTable(ui->le_localSearch->text());
}
