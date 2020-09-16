#include "form_mover.h"
#include "ui_form_mover.h"
#include <Services/productservice.h>
#include <Services/centralstorageservice.h>
#include <QtCore>
#include <QtWidgets>

form_mover::form_mover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_mover)
{
    ui->setupUi(this);
    adjustSize();
    ProductService productService;
    QStringList products = productService.getAllProductsToString().data;
    connect(ui->cb_product, SIGNAL(currentTextChanged(QString)), this, SLOT(updateRadioButtons(QString)));
    connect(ui->rb_gramos,SIGNAL(clicked(bool)),this,SLOT(updateExistente()));
    connect(ui->rb_libras,SIGNAL(clicked(bool)),this,SLOT(updateExistente()));
    connect(ui->rb_kilogramos,SIGNAL(clicked(bool)),this,SLOT(updateExistente()));
    //connect(ui->cb_product,SIGNAL(currentIndexChanged(QString)), this, SLOT(updateRadioButtons(QString)));
    QCompleter *completer = new QCompleter(products,this);
    ui->cb_product->setCompleter(completer);
    ui->cb_product->addItems(products);
    ui->rb_libras->setChecked(true);
    ui->rb_gramos->setVisible(false);
    ui->rb_libras->setVisible(false);
    ui->rb_kilogramos->setVisible(false);
    if( products.size() ){
        updateRadioButtons(ui->cb_product->currentText());
    }
}

form_mover::~form_mover()
{
    delete ui;
}

void form_mover::updateRadioButtons(QString product){
    qDebug() << "updateRadioButtons" << product;
    ProductService productService;
    auto pr = productService.getProductByName(product);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == SOLIDO ){
            ui->rb_gramos->setVisible(true);
            ui->rb_libras->setVisible(true);
            ui->rb_kilogramos->setVisible(true);
            ui->rb_libras->setChecked(true);
        }else{
            ui->rb_gramos->setVisible(false);
            ui->rb_libras->setVisible(false);
            ui->rb_kilogramos->setVisible(false);
        }
    }else{
        ui->rb_gramos->setVisible(false);
        ui->rb_libras->setVisible(false);
        ui->rb_kilogramos->setVisible(false);
    }
    updateExistente();
}

void form_mover::updateExistente(){
    ProductService productService;
    centralStorageService CentralStorageService;

    auto res = productService.getProductByName(ui->cb_product->currentText());
    if( res.res != SUCCESS ){
        ui->l_existente->setText("El producto " + ui->cb_product->currentText() + " no existe en el almacén");
        return;
    }
    auto cs = CentralStorageService.getCentralStorageById(res.data.id);
    double cantidad = 0;
    if( cs.res == SUCCESS )
        cantidad = cs.data.amount;
    if( !ui->rb_libras->isVisible() ){
        ui->l_existente->setText( "En el almacén existen " + QString::number(cantidad) + " unidades de " + ui->cb_product->currentText() );
    }else{
        weigth to = G;
        QString unit = "g";
        if( ui->rb_gramos->isChecked() )
            to = G, unit = "g";
        if( ui->rb_kilogramos->isChecked() )
            to = KG, unit = "kg";
        if( ui->rb_libras->isChecked() )
            to = LB, unit = "lb";
        cantidad = utiles::convertPeso(G, to, cantidad);
        ui->l_existente->setText("En el almacén existen " + QString::number(cantidad) + unit + " de " + ui->cb_product->currentText());
    }
    ui->sb_cantidad->setMaximum(cantidad);
}

void form_mover::on_pb_accept_clicked()
{
    ProductService productService;
    centralStorageService CentralStorageService;
    auto prod = productService.getProductByName(ui->cb_product->currentText());
    if( prod.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información", "El Producto " + ui->cb_product->currentText() + " no existe en el almacén",QMessageBox::Ok);
        return;
    }
    auto storeProduct = CentralStorageService.getCentralStorageById(prod.data.id);
    double cantidad = ui->sb_cantidad->value();
    weigth from = G;
    if( prod.data.unitType == SOLIDO ){
        if( ui->rb_gramos->isChecked() )
            from = G;
        if( ui->rb_kilogramos->isChecked() )
            from = KG;
        if( ui->rb_libras->isChecked() )
            from = LB;
    }
    cantidad = utiles::convertPeso(from, G, cantidad);
    if( cantidad > storeProduct.data.amount ){
        QMessageBox::information(this,"Información", "La cantidad seleccionada excede a la existente en el almacén",QMessageBox::Ok);
        return;
    }
    CentralStorageService.moveToLocal(prod.data.id, cantidad);
    emit done();
}

void form_mover::on_pb_cancel_clicked()
{
    emit done();
}
