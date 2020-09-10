#include "form_compra.h"
#include "ui_form_compra.h"
#include <Services/productservice.h>
#include <Services/centralstorageservice.h>


form_compra::form_compra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_compra)
{
    ui->setupUi(this);

    ProductService productService;
    QStringList products = productService.getAllProductsToString().data;
    QCompleter *completer = new QCompleter(products,this);
    ui->cb_product->setCompleter(completer);
    ui->sb_merma->setEnabled(false);
    ui->cb_product->addItems(products);
}

form_compra::~form_compra()
{
    delete ui;
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

    double realCant = cant - merma;
    double price = ui->sb_precio->value();
    double pricePerUnit = 0;
    if( realCant > 0 )
         pricePerUnit = price / realCant;
    CentralStorageService.modifyCentralStorage(product.data.id, realCant, 1, pricePerUnit, merma);
    emit done();
}
