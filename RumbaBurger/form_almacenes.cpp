#include "form_almacenes.h"
#include "ui_form_almacenes.h"
#include "Services/centralstorageservice.h"
#include <Services/storageservice.h>
#include <QCompleter>
#include <QMessageBox>

form_almacenes::form_almacenes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_almacenes)
{
    ui->setupUi(this);
    updateCentralTable("");
    updateLocalTable("");
    ui->pb_eliminarProduct->setEnabled(false);
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

    /******************************************
     Insertar Compra
     *****************************************/

    connect(ui->cb_productCompra, SIGNAL(currentTextChanged(QString)), this, SLOT(updateRadioButtonsCompra(QString)));
    ui->cb_productCompra->setCompleter(completer);
    ui->sb_mermaCompra->setEnabled(false);
    ui->cb_productCompra->addItems(products);
    ui->rb_librasCompra->setChecked(true);
    ui->rb_gramosCompra->setVisible(false);
    ui->rb_librasCompra->setVisible(false);
    ui->rb_kilogramosCompra->setVisible(false);
    if( products.size() ){
        updateRadioButtonsCompra(ui->cb_productCompra->currentText());
    }

    /******************************************
     Final Compra
     *****************************************/

    /**************************
     * Insertar Producto
     *************************/
    ui->rb_solidoInsertar->setChecked(true);
    /***************************
     * Final Insertar Producto
     * *************************/


    /***********************
     * Mover al Local
     ***********************/
    connect(ui->cb_productMoverAlLocal, SIGNAL(currentTextChanged(QString)), this, SLOT(updateRadioButtonsMoverAlLocal(QString)));
    connect(ui->rb_gramosMoverAlLocal,SIGNAL(clicked(bool)),this,SLOT(updateExistenteMoverAlLocal()));
    connect(ui->rb_librasMoverAlLocal,SIGNAL(clicked(bool)),this,SLOT(updateExistenteMoverAlLocal()));
    connect(ui->rb_kilogramosMoverAlLocal,SIGNAL(clicked(bool)),this,SLOT(updateExistenteMoverAlLocal()));
    ui->cb_productMoverAlLocal->setCompleter(completer);
    ui->cb_productMoverAlLocal->addItems(products);
    ui->rb_librasMoverAlLocal->setChecked(true);
    ui->rb_gramosMoverAlLocal->setVisible(false);
    ui->rb_librasMoverAlLocal->setVisible(false);
    ui->rb_kilogramosMoverAlLocal->setVisible(false);
    if( products.size() ){
        updateRadioButtonsMoverAlLocal(ui->cb_productMoverAlLocal->currentText());
    }
    /***********************
     * Final Mover al Local
     ***********************/



    /*****************************
     * Extraer
     * ***************************/

    connect(ui->cb_productoExtraer, SIGNAL(currentTextChanged(QString)), this, SLOT(updateRadioButtonsExtraer(QString)));
    connect(ui->rb_gramosExtraer,SIGNAL(clicked(bool)),this,SLOT(updateExistenteExtraer()));
    connect(ui->rb_librasExtraer,SIGNAL(clicked(bool)),this,SLOT(updateExistenteExtraer()));
    connect(ui->rb_kilogramosExtraer,SIGNAL(clicked(bool)),this,SLOT(updateExistenteExtraer()));

    ui->cb_productoExtraer->setCompleter(completer);
    ui->cb_productoExtraer->addItems(products);
    ui->rb_librasExtraer->setChecked(true);
    ui->rb_gramosExtraer->setVisible(false);
    ui->rb_librasExtraer->setVisible(false);
    ui->rb_kilogramosExtraer->setVisible(false);
    if( products.size() ){
        updateRadioButtonsExtraer(ui->cb_productoExtraer->currentText());
    }

    /****************************
     * Fin Extraer
     * ************************/
}

void form_almacenes::updateProducts(){
    ProductService productService;
    QStringList products = productService.getAllProductsToString().data;

    QCompleter *completer = new QCompleter(products,this);
    ui->cb_mcProduct->clear();
    ui->cb_mcProduct->setCompleter(completer);
    ui->cb_mcProduct->addItems(products);

    ui->cb_productCompra->clear();
    ui->cb_productCompra->setCompleter(completer);
    ui->cb_productCompra->addItems(products);

    ui->cb_productMoverAlLocal->clear();
    ui->cb_productMoverAlLocal->setCompleter(completer);
    ui->cb_productMoverAlLocal->addItems(products);

    ui->cb_productoExtraer->clear();
    ui->cb_productoExtraer->setCompleter(completer);
    ui->cb_productoExtraer->addItems(products);

    //ui->rb_mcKilogramos->setVisible(false);
    if( products.size() ){
        updateMCRadioButtons(ui->cb_mcProduct->currentText());
        updateRadioButtonsCompra(ui->cb_productCompra->currentText());
        updateRadioButtonsMoverAlLocal(ui->cb_productMoverAlLocal->currentText());
        updateRadioButtonsExtraer(ui->cb_productoExtraer->currentText());
    }
}

form_almacenes::~form_almacenes()
{
    delete ui;
}

void form_almacenes::updateRadioButtonsExtraer(QString product){
    qDebug() << "updateRadioButtons" << product;
    ProductService productService;
    auto pr = productService.getProductByName(product);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == 1 ){
            ui->rb_gramosExtraer->setVisible(true);
            ui->rb_librasExtraer->setVisible(true);
            ui->rb_kilogramosExtraer->setVisible(true);
            ui->rb_librasExtraer->setChecked(true);
        }else{
            ui->rb_gramosExtraer->setVisible(false);
            ui->rb_librasExtraer->setVisible(false);
            ui->rb_kilogramosExtraer->setVisible(false);
        }
    }else{
        ui->rb_gramosExtraer->setVisible(false);
        ui->rb_librasExtraer->setVisible(false);
        ui->rb_kilogramosExtraer->setVisible(false);
    }
    updateExistenteExtraer();
}

void form_almacenes::updateExistenteExtraer(){
    ProductService productService;
    centralStorageService CentralStorageService;

    auto res = productService.getProductByName(ui->cb_productoExtraer->currentText());
    if( res.res != SUCCESS ){
        ui->l_existenteExtraer->setText("El producto " + ui->cb_productoExtraer->currentText() + " no existe en el almacén");
        return;
    }
    auto cs = CentralStorageService.getCentralStorageById(res.data.id);
    double cantidad = 0;
    if( cs.res == SUCCESS )
        cantidad = cs.data.amount;
    if( !ui->rb_librasExtraer->isVisible() ){
        ui->l_existenteExtraer->setText( "En el almacén existen " + QString::number(cantidad) + " unidades de " + ui->cb_productoExtraer->currentText() );
    }else{
        weigth to = G;
        QString unit = "g";
        if( ui->rb_gramosExtraer->isChecked() )
            to = G, unit = "g";
        if( ui->rb_kilogramosExtraer->isChecked() )
            to = KG, unit = "kg";
        if( ui->rb_librasExtraer->isChecked() )
            to = LB, unit = "lb";
        cantidad = utiles::convertPeso(G, to, cantidad);
        ui->l_existenteExtraer->setText("En el almacén existen " + QString::number(cantidad) + unit + " de " + ui->cb_productoExtraer->currentText());
    }
    ui->sb_cantidadExtraer->setMaximum(cantidad);
}


void form_almacenes::updateCentralTable(QString search){
    qDebug() << "update central";
    centralStorageService CentralStorageService;
    auto res = CentralStorageService.getCentralStorageBySearch( utiles::searchToRegExp(search) ).data;
    ui->centralTable->clearContents();
    ui->centralTable->setRowCount(res.size());
    int row = 0;
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
        ui->sb_mcCantidad->setSuffix(" unidades");
    }else{
        weigth to = G;
        QString unit = "g";
        if( ui->rb_mcGramos->isChecked() )
            to = G, unit = "g", ui->sb_mcCantidad->setSuffix(" g");
        if( ui->rb_mcKilogramos->isChecked() )
            to = KG, unit = "kg", ui->sb_mcCantidad->setSuffix(" kg");
        if( ui->rb_mcLibras->isChecked() )
            to = LB, unit = "lb", ui->sb_mcCantidad->setSuffix(" lb");
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
            ui->sb_mcCantidad->setSuffix( " lb" );
        }else{
            ui->rb_mcGramos->setVisible(false);
            ui->rb_mcLibras->setVisible(false);
            ui->rb_mcKilogramos->setVisible(false);
            ui->sb_mcCantidad->setSuffix(" unidades");
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

    ui->sb_mcCantidad->setValue(0);
    updateCentralTable(ui->le_localSearch->text());
    updateLocalTable(ui->le_Centralsearch->text());

}

void form_almacenes::updateRadioButtonsCompra(QString product){
    qDebug() << "updateRadioButtons" << product;
    ProductService productService;
    auto pr = productService.getProductByName(product);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == 1 ){
            ui->rb_gramosCompra->setVisible(true);
            ui->rb_librasCompra->setVisible(true);
            ui->rb_kilogramosCompra->setVisible(true);
            ui->rb_librasCompra->setChecked(true);
        }else{
            ui->rb_gramosCompra->setVisible(false);
            ui->rb_librasCompra->setVisible(false);
            ui->rb_kilogramosCompra->setVisible(false);
        }
    }else{
        ui->rb_gramosCompra->setVisible(false);
        ui->rb_librasCompra->setVisible(false);
        ui->rb_kilogramosCompra->setVisible(false);
    }
}

void form_almacenes::on_cb_mermaCompra_clicked()
{
    ui->sb_mermaCompra->setEnabled(ui->cb_mermaCompra->isChecked());
}

void form_almacenes::on_pb_insertarCompra_clicked()
{
    centralStorageService CentralStorageService;
    ProductService productService;
    QString productName = ui->cb_productCompra->currentText();
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

    double cant = ui->sb_cantidadCompra->value();
    double merma = 0;
    if( ui->cb_mermaCompra->isChecked() )
        merma = ui->sb_mermaCompra->value();
    if( merma > cant ){
        QMessageBox::critical(this,"Error", "La merma es mayor que la cantidad", QMessageBox::Ok);
        return;
    }

    double realCant = cant - merma;
    double precioTotal = ui->sb_precioCompra->value();

    weigth from = G;
    if( product.data.unitType == 1 ){
        if( ui->rb_gramosCompra->isChecked() ) from = G;
        if( ui->rb_kilogramosCompra->isChecked() ) from = KG;
        if( ui->rb_librasCompra->isChecked() ) from = LB;
    }

    double pricePerUnit = 0;
    if( realCant > 0 )
        pricePerUnit = precioTotal / realCant;

    realCant = utiles::convertPeso(from, G, realCant);
    merma = utiles::convertPeso(from, G, merma);
    pricePerUnit = utiles::convertPrecio(from, G, pricePerUnit);


    CentralStorageService.modifyCentralStorage(product.data.id, realCant, 1, pricePerUnit, merma);
    updateCentralTable( ui->le_Centralsearch->text() );
    ui->sb_cantidadCompra->setValue(0);
    ui->sb_mermaCompra->setValue(0);
    ui->sb_precioCompra->setValue(0);
}

void form_almacenes::on_pb_acceptInsertar_clicked()
{
    if( ui->le_productInsertar->text() == "" ){
        QMessageBox::information(this,"Información","Debe escribir el nombre del producto",QMessageBox::Ok);
        return;
    }
    centralStorageService CentralStorgeService;
    storageService StorageService;
    auto res = QMessageBox::information(this,"Información","Está seguro que desea insertar el producto: " + ui->le_productInsertar->text(),QMessageBox::Ok, QMessageBox::Cancel);
    if( res == QMessageBox::Ok ){
        ProductService productService;
        int unitType = 1;
        if( ui->rb_solidoInsertar->isChecked() )
            unitType = 1;
        else
            unitType = 2;
        auto ret = productService.getProductByName(ui->le_productInsertar->text());
        if( ret.res == SUCCESS ){
            QMessageBox::information(this, "Información", "El producto " + ui->le_productInsertar->text() + " ya existe",QMessageBox::Ok);
            return;
        }
        if( ret.res == RECORD_NOT_FOUND ){
            auto res = productService.insertProduct(ProductDto(0,ui->le_productInsertar->text(),unitType,0));
            if( res.res != SUCCESS )
                qDebug() << res.msg;
            else{
                qDebug() << "Insertado Producto" << ui->le_productInsertar->text();
                auto r = CentralStorgeService.insertCentralStorage(centralStorageDto(res.data,0));
                         StorageService.insertStorage(storageDto(res.data, 0));
                if( r.res != SUCCESS )
                    qDebug() << r.msg;
            }


        }
    }

    updateProducts();
    updateCentralTable(ui->le_Centralsearch->text());
}

void form_almacenes::updateRadioButtonsMoverAlLocal(QString product){
    qDebug() << "updateRadioButtons" << product;
    ProductService productService;
    auto pr = productService.getProductByName(product);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == SOLIDO ){
            ui->rb_gramosMoverAlLocal->setVisible(true);
            ui->rb_librasMoverAlLocal->setVisible(true);
            ui->rb_kilogramosMoverAlLocal->setVisible(true);
            ui->rb_librasMoverAlLocal->setChecked(true);
        }else{
            ui->rb_gramosMoverAlLocal->setVisible(false);
            ui->rb_librasMoverAlLocal->setVisible(false);
            ui->rb_kilogramosMoverAlLocal->setVisible(false);
        }
    }else{
        ui->rb_gramosMoverAlLocal->setVisible(false);
        ui->rb_librasMoverAlLocal->setVisible(false);
        ui->rb_kilogramosMoverAlLocal->setVisible(false);
    }
    updateExistenteMoverAlLocal();
}

void form_almacenes::updateExistenteMoverAlLocal(){
    ProductService productService;
    centralStorageService CentralStorageService;

    qDebug() << "UpdateExistenteMoverAlLocal";
    auto res = productService.getProductByName(ui->cb_productMoverAlLocal->currentText());
    if( res.res != SUCCESS ){
        ui->l_existenteMoverAlLocal->setText("El producto " + ui->cb_productMoverAlLocal->currentText() + " no existe en el almacén");
        return;
    }
    auto cs = CentralStorageService.getCentralStorageById(res.data.id);
    double cantidad = 0;
    if( cs.res == SUCCESS )
        cantidad = cs.data.amount;
    if( !ui->rb_librasMoverAlLocal->isVisible() ){
        ui->l_existenteMoverAlLocal->setText( "En el almacén existen " + QString::number(cantidad) + " unidades de " + ui->cb_productMoverAlLocal->currentText() );
    }else{
        weigth to = G;
        QString unit = "g";
        if( ui->rb_gramosMoverAlLocal->isChecked() )
            to = G, unit = "g";
        if( ui->rb_kilogramosMoverAlLocal->isChecked() )
            to = KG, unit = "kg";
        if( ui->rb_librasMoverAlLocal->isChecked() )
            to = LB, unit = "lb";
        cantidad = utiles::convertPeso(G, to, cantidad);
        ui->l_existenteMoverAlLocal->setText("En el almacén existen " + QString::number(cantidad) + unit + " de " + ui->cb_productMoverAlLocal->currentText());
    }
    ui->sb_cantidadMoverAlLocal->setMaximum(cantidad);
}


void form_almacenes::on_pb_MoverAlLocal_clicked()
{
    ProductService productService;
    centralStorageService CentralStorageService;
    auto prod = productService.getProductByName(ui->cb_productMoverAlLocal->currentText());
    if( prod.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información", "El Producto " + ui->cb_productMoverAlLocal->currentText() + " no existe en el almacén",QMessageBox::Ok);
        return;
    }
    auto storeProduct = CentralStorageService.getCentralStorageById(prod.data.id);
    double cantidad = ui->sb_cantidadMoverAlLocal->value();
    weigth from = G;
    if( prod.data.unitType == SOLIDO ){
        if( ui->rb_gramosMoverAlLocal->isChecked() )
            from = G;
        if( ui->rb_kilogramosMoverAlLocal->isChecked() )
            from = KG;
        if( ui->rb_librasMoverAlLocal->isChecked() )
            from = LB;
    }
    cantidad = utiles::convertPeso(from, G, cantidad);
    if( cantidad > storeProduct.data.amount ){
        QMessageBox::information(this,"Información", "La cantidad seleccionada excede a la existente en el almacén",QMessageBox::Ok);
        return;
    }
    CentralStorageService.moveToLocal(prod.data.id, cantidad);
    ui->sb_cantidadMoverAlLocal->setValue(0);
    updateCentralTable( ui->le_localSearch->text() );
    updateLocalTable( ui->le_localSearch->text() );
}

void form_almacenes::on_pb_aceptarExtraer_clicked()
{
    ProductService productService;
    centralStorageService CentralStorageService;
    auto prod = productService.getProductByName(ui->cb_productoExtraer->currentText());
    if( prod.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información", "El Producto " + ui->cb_productoExtraer->currentText() + " no existe en el almacén",QMessageBox::Ok);
        return;
    }
    auto storeProduct = CentralStorageService.getCentralStorageById(prod.data.id);
    double cantidad = ui->sb_cantidadExtraer->value();
    weigth from = G;
    if( prod.data.unitType == SOLIDO ){
        if( ui->rb_gramosExtraer->isChecked() )
            from = G;
        if( ui->rb_kilogramosExtraer->isChecked() )
            from = KG;
        if( ui->rb_librasExtraer->isChecked() )
            from = LB;
    }
    cantidad = utiles::convertPeso(from, G, cantidad);
    if( cantidad > storeProduct.data.amount ){
        QMessageBox::information(this,"Información", "La cantidad seleccionada excede a la existente en el almacén",QMessageBox::Ok);
        return;
    }

    ui->sb_cantidadExtraer->setValue(0);
    CentralStorageService.extract(prod.data.id, cantidad);
    updateCentralTable(ui->le_localSearch->text());
}

void form_almacenes::on_pb_eliminarProduct_clicked()
{
    int row = ui->centralTable->currentRow();
    if( row < 0 ){
        QMessageBox::information(this, "Información", "Debe seleccionar un producto para eliminar", QMessageBox::Ok);
        ui->pb_eliminarProduct->setEnabled(false);
        return;
    }

    centralStorageService CentralStorageService;
    storageService StorageService;

    ProductService productService;
    auto product = productService.getProductByName(ui->centralTable->item(row, 0)->text());
    auto list = productService.isUsed(product.data.id).data;
    if( list.isEmpty() ){
        productService.deleteProduct(product.data);
        CentralStorageService.deleteCentralStorage( product.data.id );
        StorageService.deleteStorage( product.data.id );
    }else{
        auto res = QMessageBox::information( this, "Información", "El producto " + product.data.productName + " ha sido utilizado en varias órdenes. Su eliminación puede causar errores en la información mostrada. ¿Está seguro que desea eliminarlo?", QMessageBox::Ok | QMessageBox::Cancel );
        if( res == QMessageBox::Ok ){
            productService.deleteProduct(product.data);
            CentralStorageService.deleteCentralStorage( product.data.id );
            StorageService.deleteStorage( product.data.id );
        }
    }

    updateCentralTable(ui->le_Centralsearch->text());
    updateLocalTable(ui->le_localSearch->text());

}


void form_almacenes::on_centralTable_cellClicked(int row, int column)
{
    ui->pb_eliminarProduct->setEnabled(true);
}
