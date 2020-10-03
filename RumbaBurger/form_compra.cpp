#include "form_compra.h"
#include "ui_form_compra.h"
#include <Services/productservice.h>
#include <Services/centralstorageservice.h>
#include <utiles.h>

form_compra::form_compra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_compra)
{
    ui->setupUi(this);
    adjustSize();
    ProductService productService;
    QStringList products = productService.getAllProductsToString().data;
    connect(ui->cb_product, SIGNAL(currentTextChanged(QString)), this, SLOT(updateRadioButtons(QString)));
    QCompleter *completer = new QCompleter(products,this);
    ui->cb_product->setCompleter(completer);
    ui->sb_merma->setEnabled(false);
    ui->cb_product->addItems(products);
    ui->rb_libras->setChecked(true);
    ui->rb_gramos->setVisible(false);
    ui->rb_libras->setVisible(false);
    ui->rb_kilogramos->setVisible(false);
    if( products.size() ){
        //auto pr = productService.getProductByName(products.value(0)).data;
        updateRadioButtons(ui->cb_product->currentText());
    }
}

form_compra::~form_compra()
{
    delete ui;
}

void form_compra::updateRadioButtons(QString product){
    qDebug() << "updateRadioButtons" << product;
    ProductService productService;
    auto pr = productService.getProductByName(product);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == 1 ){
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
}

void form_compra::on_cb_merma_clicked()
{
    ui->sb_merma->setEnabled(ui->cb_merma->isChecked());
}

void form_compra::on_pb_cancelar_clicked()
{

    emit done();
}

void form_compra::on_pb_aceptar_clicked()
{
    centralStorageService CentralStorageService;
    ProductService productService;
    QString productName = ui->cb_product->currentText();
    auto product = productService.getProductByName(productName);
    if( product.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información","El producto " + productName + " no existe",QMessageBox::Ok);
        return;
    }

    //el producto no existe en el almacen
    qDebug() << "ID: " << product.data.id;
    if( CentralStorageService.getCentralStorageById(product.data.id).res == RECORD_NOT_FOUND ){
        CentralStorageService.insertCentralStorage( centralStorageDto(product.data.id,0) );
    }

    double cant = ui->sb_cantidad->value();
    double merma = 0;
    if( ui->cb_merma->isChecked() )
        merma = ui->sb_merma->value();
    if( merma > cant ){
        QMessageBox::critical(this,"Error", "La merma es mayor que la cantidad", QMessageBox::Ok);
        return;
    }

    //QMessageBox::information(this, "Información", "")`


    double realCant = cant - merma;
    double precioTotal = ui->sb_precio->value();

    weigth from = G;
    if( product.data.unitType == 1 ){
        if( ui->rb_gramos->isChecked() ) from = G;
        if( ui->rb_kilogramos->isChecked() ) from = KG;
        if( ui->rb_libras->isChecked() ) from = LB;
    }

    double pricePerUnit = 0;
    if( realCant > 0 )
        pricePerUnit = precioTotal / realCant;

    realCant = utiles::convertPeso(from, G, realCant);
    merma = utiles::convertPeso(from, G, merma);
    pricePerUnit = utiles::convertPrecio(from, G, pricePerUnit);


    CentralStorageService.modifyCentralStorage(product.data.id, realCant, 1, pricePerUnit, merma);
    emit done();
}
