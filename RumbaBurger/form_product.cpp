#include "form_product.h"
#include "ui_form_product.h"
#include <QtCore>
#include <QtWidgets>
#include <Services/productservice.h>
#include <Services/centralstorageservice.h>
#include <Dto/centralstoragedto.h>

form_product::form_product(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_product)
{
    ui->setupUi(this);
    ui->rb_solido->setChecked(true);
    setMaximumSize(width(),height());
    setMinimumSize(width(),height());

    /*QStringList s;
    s << "bbabc" << "bbabc" << "bbxbc";
    QCompleter *c = new QCompleter(s,this);
    ui->comboBox->setCompleter(c);
    ui->comboBox->addItem("bbabc");
    ui->comboBox->addItem("bbabc");
    ui->comboBox->addItem("bbxbc");
    ui->comboBox->addItem("bbaba");
    ui->comboBox->addItem("bbabb");*/


}

form_product::~form_product()
{
    delete ui;
}


void form_product::on_pb_accept_clicked()
{
    if( ui->le_product->text() == "" ){
        QMessageBox::information(this,"Información","Debe escribir el nombre del producto",QMessageBox::Ok);
        return;
    }
    centralStorageService CentralStorgeService;
    auto res = QMessageBox::information(this,"Información","Está seguro que desea insertar el producto: " + ui->le_product->text(),QMessageBox::Ok, QMessageBox::Cancel);
    if( res == QMessageBox::Ok ){
        ProductService productService;
        int unitType = 1;
        if( ui->rb_solido->isChecked() )
            unitType = 1;
        else
            unitType = 2;
        auto ret = productService.getProductByName(ui->le_product->text());
        if( ret.res == SUCCESS ){
            QMessageBox::information(this, "Información", "El producto " + ui->le_product->text() + " ya existe",QMessageBox::Ok);
            return;
        }
        if( ret.res == RECORD_NOT_FOUND ){
            auto res = productService.insertProduct(ProductDto(0,ui->le_product->text(),unitType,0));
            if( res.res != SUCCESS )
                qDebug() << res.msg;
            else{
                qDebug() << "Insertado Producto" << ui->le_product->text();
                auto r = CentralStorgeService.insertCentralStorage(centralStorageDto(res.data,0));
                if( r.res != SUCCESS )
                    qDebug() << r.msg;
            }


        }
        emit done();
    }else{
        qDebug() << "Cancelado";
        emit done();
    }

}

void form_product::on_pb_cancel_clicked()
{
    emit done();
}
