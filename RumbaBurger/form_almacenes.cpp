#include "form_almacenes.h"
#include "ui_form_almacenes.h"
#include "Services/centralstorageservice.h"
#include <Services/storageservice.h>
#include <QCompleter>

form_almacenes::form_almacenes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_almacenes)
{
    ui->setupUi(this);
    updateCentralTable("");
    updateLocalTable("");
    ProductService productService;
    QStringList products = productService.getAllProductsToString().data;
    connect(ui->cb_mcProduct, SIGNAL(currentTextChanged(QString)), this, SLOT(updateMCRadioButtons(QString)));
    connect(ui->rb_mcGramos,SIGNAL(clicked(bool)),this,SLOT(updateMCExistente()));
    connect(ui->rb_mcLibras,SIGNAL(clicked(bool)),this,SLOT(updateMCExistente()));
    connect(ui->rb_mcKilogramos,SIGNAL(clicked(bool)),this,SLOT(updateMCExistente()));
    //connect(ui->cb_product,SIGNAL(currentIndexChanged(QString)), this, SLOT(updateRadioButtons(QString)));
    QCompleter *completer = new QCompleter(products,this);
    ui->cb_mcProduct->setCompleter(completer);
    ui->cb_mcProduct->addItems(products);
    ui->rb_mcLibras->setChecked(true);
    ui->rb_mcGramos->setVisible(false);
    ui->rb_mcLibras->setVisible(false);
    ui->rb_mcKilogramos->setVisible(false);
    if( products.size() ){
        updateMCRadioButtons(ui->cb_mcProduct->currentText());
    }
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

void form_almacenes::on_pb_extraer_clicked()
{
    ui->mdiCentral->closeAllSubWindows();
    formExtraerCentral = new form_extraerCentral(this);
    ui->mdiCentral->addSubWindow(formExtraerCentral);
    connect(formExtraerCentral,SIGNAL(done()), this, SLOT(clearCentralMdi()));
    formExtraerCentral->show();
    updateCentralTable(ui->le_localSearch->text());
}

void form_almacenes::on_pb_moveToCentral_clicked()
{
    ui->mdiCentral->closeAllSubWindows();
    formMover = new form_mover(this);
    ui->mdiCentral->addSubWindow(formMover);
    connect(formMover,SIGNAL(done()), this, SLOT(clearCentralMdi()));
    formMover->show();
    updateCentralTable(ui->le_localSearch->text());
}

void form_almacenes::updateMCExistente()
{
    ProductService productService;
    storageService StorageService;

    auto res = productService.getProductByName(ui->cb_mcProduct->currentText());
    if( res.res != SUCCESS ){
        ui->l_mcExistente->setText("El producto " + ui->cb_mcProduct->currentText() + " no existe en el almacén");
        return;
    }

    auto cs = StorageService.getStorageById(res.data.id);
    double cantidad = 0;
    if( cs.res == SUCCESS )
        cantidad = cs.data.amount;
    if( !ui->rb_mcLibras->isVisible() ){
        ui->l_mcExistente->setText( "En el almacén existen " + QString::number(cantidad) + " unidades de " + ui->cb_mcProduct->currentText() );
    }else{
        weigth to = G;
        QString unit = "g";
        if( ui->rb_mcGramos->isChecked() )
            to = G, unit = "g";
        if( ui->rb_mcKilogramos->isChecked() )
            to = KG, unit = "kg";
        if( ui->rb_mcLibras->isChecked() )
            to = LB, unit = "lb";
        cantidad = utiles::convertPeso(G, to, cantidad);
        ui->l_mcExistente->setText("En el almacén existen " + QString::number(cantidad) + unit + " de " + ui->cb_mcProduct->currentText());
    }
    ui->sb_mcCantidad->setMaximum(cantidad);
}

void form_almacenes::updateMCRadioButtons( QString product )
{
    qDebug() << "updateRadioButtons" << product;
    ProductService productService;
    auto pr = productService.getProductByName(product);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == 1 ){
            ui->rb_mcGramos->setVisible(true);
            ui->rb_mcLibras->setVisible(true);
            ui->rb_mcKilogramos->setVisible(true);
            ui->rb_mcLibras->setChecked(true);
        }else{
            ui->rb_mcGramos->setVisible(false);
            ui->rb_mcLibras->setVisible(false);
            ui->rb_mcKilogramos->setVisible(false);
        }
    }else{
        ui->rb_mcGramos->setVisible(false);
        ui->rb_mcLibras->setVisible(false);
        ui->rb_mcKilogramos->setVisible(false);
    }
    updateMCExistente();
}


void form_almacenes::on_pb_mcAccept_clicked()
{
    ProductService productService;
    storageService StorageService;
    auto prod = productService.getProductByName(ui->cb_mcProduct->currentText());
    if( prod.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información", "El Producto " + ui->cb_mcProduct->currentText() + " no existe en el almacén",QMessageBox::Ok);
        return;
    }
    auto storeProduct = StorageService.getStorageById(prod.data.id);
    double cantidad = ui->sb_mcCantidad->value();
    weigth from = G;
    QString unit = " unidad(es)";
    if( prod.data.unitType == SOLIDO ){
        if( ui->rb_mcGramos->isChecked() )
            from = G, unit = " g";
        if( ui->rb_mcKilogramos->isChecked() )
            from = KG, unit = " kg";
        if( ui->rb_mcLibras->isChecked() )
            from = LB, unit = " lb";
    }
    cantidad = utiles::convertPeso(from, G, cantidad);
    if( cantidad > storeProduct.data.amount ){
        QMessageBox::information(this,"Información", "La cantidad seleccionada excede a la existente en el almacén",QMessageBox::Ok);
        return;
    }
    auto r = QMessageBox::information(this,"Información", "Usted va a mover " + QString::number(ui->sb_mcCantidad->value()) + unit + " de " + ui->cb_mcProduct->currentText(), QMessageBox::Ok | QMessageBox::Cancel );

    if( r == QMessageBox::Ok )
        StorageService.moveToCentral(prod.data.id, cantidad);

    updateCentralTable(ui->le_localSearch->text());
    updateLocalTable(ui->le_Centralsearch->text());

}
