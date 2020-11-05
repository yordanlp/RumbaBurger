#include "form_almacenes.h"
#include "ui_form_almacenes.h"
#include "Services/centralstorageservice.h"
#include <Services/storageservice.h>
#include <QCompleter>
#include <QMessageBox>
#include <Services/transactionservice.h>
#include <Services/expensesservice.h>

/********************************
 * Cosas a Revisar
 * - Cuando el producto a comprar, extraer o mover sea por unidades castear los valores de los spin box a enteros, excepto el precio
 * ******************************/

form_almacenes::form_almacenes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_almacenes)
{
    qDebug() << "USUARIO" << UserService::loggedUser;

    setUnit();


    ui->setupUi(this);

    updateCentralTable("");
    updateLocalTable("");

    ui->pb_eliminarProduct->setEnabled(false);

    /******************************
     * Mover al almacen central
     * ***************************/

    ProductService productService;
    QStringList products = productService.getAllProductsToString().data;

    connect(ui->cb_mcProduct, SIGNAL(currentTextChanged(QString)), this, SLOT(updateMCRadioButtons(QString)));
    connect(ui->rb_mcGramos,SIGNAL(clicked(bool)),this,SLOT(updateMCExistente()));
    //connect(ui->rb_mcLibras,SIGNAL(clicked(bool)),this,SLOT(updateMCExistente()));
    connect(ui->rb_mcKilogramos,SIGNAL(clicked(bool)),this,SLOT(updateMCExistente()));

    QCompleter *completermc = new QCompleter(products,this);
    ui->cb_mcProduct->setCompleter(completermc);
    ui->cb_mcProduct->addItems(products);
    ui->rb_mcGramos->setChecked(true);
    ui->rb_mcGramos->setVisible(false);
    ui->rb_mcLibras->setVisible(false);
    ui->rb_mcKilogramos->setVisible(false);
    if( products.size() )
        updateMCRadioButtons(ui->cb_mcProduct->currentText());


    /******************************************
     Insertar Compra
     *****************************************/

    QCompleter *completercompra = new QCompleter(products,this);

    //ui->sb_precioCompra->setPrefix("$");
    connect(ui->rb_gramosCompra, SIGNAL(clicked(bool)), this, SLOT(updateSuffixCompra()));
    connect(ui->rb_kilogramosCompra, SIGNAL(clicked(bool)), this, SLOT(updateSuffixCompra()));
    connect(ui->rb_librasCompra, SIGNAL(clicked(bool)), this, SLOT(updateSuffixCompra()));
    connect(ui->cb_productCompra, SIGNAL(currentTextChanged(QString)), this, SLOT(updateRadioButtonsCompra(QString)));
    ui->cb_productCompra->setCompleter(completercompra);
    ui->sb_mermaCompra->setEnabled(false);
    ui->cb_productCompra->addItems(products);
    ui->rb_gramosCompra->setChecked(true);
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

    QCompleter *completerml = new QCompleter(products,this);
    connect(ui->cb_productMoverAlLocal, SIGNAL(currentTextChanged(QString)), this, SLOT(updateRadioButtonsMoverAlLocal(QString)));
    connect(ui->rb_gramosMoverAlLocal,SIGNAL(clicked(bool)),this,SLOT(updateExistenteMoverAlLocal()));
    connect(ui->rb_librasMoverAlLocal,SIGNAL(clicked(bool)),this,SLOT(updateExistenteMoverAlLocal()));
    connect(ui->rb_kilogramosMoverAlLocal,SIGNAL(clicked(bool)),this,SLOT(updateExistenteMoverAlLocal()));
    ui->cb_productMoverAlLocal->setCompleter(completerml);
    ui->cb_productMoverAlLocal->addItems(products);
    ui->rb_gramosMoverAlLocal->setChecked(true);
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
    //connect(ui->rb_librasExtraer,SIGNAL(clicked(bool)),this,SLOT(updateExistenteExtraer()));
    connect(ui->rb_kilogramosExtraer,SIGNAL(clicked(bool)),this,SLOT(updateExistenteExtraer()));

    QCompleter *completerextraer = new QCompleter(products,this);
    ui->cb_productoExtraer->setCompleter(completerextraer);
    ui->cb_productoExtraer->addItems(products);
    ui->rb_kilogramosExtraer->setChecked(true);
    ui->rb_gramosExtraer->setVisible(false);
    ui->rb_librasExtraer->setVisible(false);
    ui->rb_kilogramosExtraer->setVisible(false);
    if( products.size() ){
        updateRadioButtonsExtraer(ui->cb_productoExtraer->currentText());
    }

    /****************************
     * Fin Extraer
     * ************************/


    /************************
     * Extraer Local
     * *********************/

    connect(ui->cb_productoExtraerLocal, SIGNAL(currentTextChanged(QString)), this, SLOT(updateRadioButtonsExtraerLocal(QString)));
    connect(ui->rb_gramosExtraerLocal,SIGNAL(clicked(bool)),this,SLOT(updateExistenteExtraerLocal()));
    //connect(ui->rb_librasExtraerLocal,SIGNAL(clicked(bool)),this,SLOT(updateExistenteExtraerLocal()));
    connect(ui->rb_kilogramosExtraerLocal,SIGNAL(clicked(bool)),this,SLOT(updateExistenteExtraerLocal()));

    QCompleter *completerextraerlocal = new QCompleter(products,this);
    ui->cb_productoExtraerLocal->setCompleter(completerextraerlocal);
    ui->cb_productoExtraerLocal->addItems(products);
    ui->rb_kilogramosExtraerLocal->setChecked(true);
    ui->rb_gramosExtraerLocal->setVisible(false);
    ui->rb_librasExtraerLocal->setVisible(false);
    ui->rb_kilogramosExtraerLocal->setVisible(false);
    if( products.size() ){
        updateRadioButtonsExtraerLocal(ui->cb_productoExtraerLocal->currentText());
    }

    /************************
     * Fin Extraer Local
     * *********************/

    if( UserService::loggedUser == 0 ){
        ui->pb_eliminarProduct->setEnabled(false);
        ui->groupBox->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
        ui->groupBox_3->setEnabled(false);
        ui->groupBox_4->setEnabled(false);
        ui->groupBox_5->setEnabled(false);
        ui->groupBox_6->setEnabled(false);
        ui->groupBox_7->setEnabled(false);
        ui->gb_compra->setEnabled(false);
        ui->gb_extraer->setEnabled(false);
        ui->gb_extraer_2->setEnabled(false);
        ui->gb_insertarProducto->setEnabled(false);
    }

    ui->pb_aceptarExtraer->setEnabled(false);
    ui->pb_aceptarExtraerLocal->setEnabled(false);
    ui->pb_insertarCompra->setEnabled(false);
    ui->pb_mcAccept->setEnabled(false);
    ui->pb_MoverAlLocal->setEnabled(false);

}

void form_almacenes::setUnit(){
    qDebug() << "Update Unit";
    if( utiles::UNIDAD == "Gramos" )
        PESO = G;
    if( utiles::UNIDAD == "Kilogramos" )
        PESO = KG;
    if( utiles::UNIDAD == "Libras" )
        PESO = LB;
}

void form_almacenes::updateRadioButtonsExtraerLocal(QString product){
    ProductService productService;
    auto pr = productService.getProductByName(product);
    ui->sb_cantidadExtraerLocal->setValue(0);
    emit ui->sb_cantidadExtraerLocal->valueChanged(0);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == SOLIDO ){
            ui->rb_gramosExtraerLocal->setVisible(true);
            //ui->rb_librasExtraerLocal->setVisible(true);
            ui->rb_kilogramosExtraerLocal->setVisible(true);
            ui->rb_kilogramosExtraerLocal->setChecked(true);
            ui->sb_cantidadExtraerLocal->setSuffix(" kg");
        }else{
            ui->rb_gramosExtraerLocal->setVisible(false);
            //ui->rb_librasExtraerLocal->setVisible(false);
            ui->rb_kilogramosExtraerLocal->setVisible(false);
            ui->sb_cantidadExtraerLocal->setSuffix(" u");
        }
    }else{
        ui->rb_gramosExtraerLocal->setVisible(false);
        //ui->rb_librasExtraerLocal->setVisible(false);
        ui->rb_kilogramosExtraerLocal->setVisible(false);
        ui->pb_aceptarExtraerLocal->setEnabled(false);
    }
    //updateExistentes();
    updateExistenteExtraerLocal();
}

void form_almacenes::updateSuffixCompra(){
    if( ui->rb_gramosCompra->isChecked() )
        ui->sb_cantidadCompra->setSuffix(" g"), ui->sb_mermaCompra->setSuffix(" g");
    if( ui->rb_kilogramosCompra->isChecked() )
        ui->sb_cantidadCompra->setSuffix(" kg"), ui->sb_mermaCompra->setSuffix(" kg");
    if( ui->rb_librasCompra->isChecked() )
        ui->sb_cantidadCompra->setSuffix(" lb"), ui->sb_mermaCompra->setSuffix(" lb");

}

void form_almacenes::updateExistenteExtraerLocal(){
    ProductService productService;
    storageService StorageService;

    QString productName = ui->cb_productoExtraerLocal->currentText();
    auto res = productService.getProductByName(productName);
    if( res.res != SUCCESS ){
        ui->l_existenteExtraerLocal->setText("El producto " + productName + " no existe en el almacén");
        return;
    }
    auto cs = StorageService.getStorageById(res.data.id);
    double cantidad = 0;
    if( cs.res == SUCCESS )
        cantidad = cs.data.amount;
    if( res.data.unitType == UNIDAD ){
        ui->l_existenteExtraerLocal->setText( "En el almacén existen " + QString::number(cantidad) + " unidad(es) de " + productName );
        ui->sb_cantidadExtraerLocal->setSuffix(" u");
    }else{
        weigth to = G;
        QString unit = " g";
        if( ui->rb_gramosExtraerLocal->isChecked() )
            to = G, unit = " g";
        if( ui->rb_kilogramosExtraerLocal->isChecked() )
            to = KG, unit = " kg";
        //if( ui->rb_librasExtraerLocal->isChecked() )
        //    to = LB, unit = " lb";
        cantidad = utiles::convertPeso(G, to, cantidad);
        ui->l_existenteExtraerLocal->setText("En el almacén existen " + utiles::truncS(cantidad, 1) + unit + " de " + productName);
        ui->sb_cantidadExtraerLocal->setSuffix(unit);
    }

    ui->sb_cantidadExtraerLocal->setValue(0);
    ui->sb_cantidadExtraerLocal->setMaximum(utiles::trunc(cantidad, 1));
}

void form_almacenes::updateProducts(){

    ProductService productService;
    QStringList products = productService.getAllProductsToString().data;

    QCompleter *completermc = new QCompleter(products,this);
    ui->cb_mcProduct->clear();
    ui->cb_mcProduct->setCompleter(completermc);
    ui->cb_mcProduct->addItems(products);


    QCompleter *completercompra = new QCompleter(products,this);
    ui->cb_productCompra->clear();
    ui->cb_productCompra->setCompleter(completercompra);
    ui->cb_productCompra->addItems(products);

    QCompleter *completerml = new QCompleter(products,this);
    ui->cb_productMoverAlLocal->clear();
    ui->cb_productMoverAlLocal->setCompleter(completerml);
    ui->cb_productMoverAlLocal->addItems(products);

    QCompleter *completerextraer = new QCompleter(products,this);
    ui->cb_productoExtraer->clear();
    ui->cb_productoExtraer->setCompleter(completerextraer);
    ui->cb_productoExtraer->addItems(products);

    QCompleter *completerel = new QCompleter(products,this);
    ui->cb_productoExtraerLocal->clear();
    ui->cb_productoExtraerLocal->setCompleter(completerel);
    ui->cb_productoExtraerLocal->addItems(products);


    if( products.size() ){
        updateMCRadioButtons(ui->cb_mcProduct->currentText());
        updateRadioButtonsCompra(ui->cb_productCompra->currentText());
        updateRadioButtonsMoverAlLocal(ui->cb_productMoverAlLocal->currentText());
        updateRadioButtonsExtraer(ui->cb_productoExtraer->currentText());
        updateRadioButtonsExtraerLocal(ui->cb_productoExtraerLocal->currentText());
    }
}

form_almacenes::~form_almacenes()
{
    delete ui;
}

void form_almacenes::updateRadioButtonsExtraer(QString product){

    ProductService productService;
    auto pr = productService.getProductByName(product);
    ui->sb_cantidadExtraer->setValue(0);
    emit ui->sb_cantidadExtraer->valueChanged(0);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == SOLIDO ){
            ui->rb_gramosExtraer->setVisible(true);
            //ui->rb_librasExtraer->setVisible(true);
            ui->rb_kilogramosExtraer->setVisible(true);
            ui->rb_kilogramosExtraer->setChecked(true);
            ui->sb_cantidadExtraer->setSuffix(" kg");
        }else{
            ui->rb_gramosExtraer->setVisible(false);
            //ui->rb_librasExtraer->setVisible(false);
            ui->rb_kilogramosExtraer->setVisible(false);
            ui->sb_cantidadExtraer->setSuffix(" u");
        }
    }else{
        ui->rb_gramosExtraer->setVisible(false);
        //ui->rb_librasExtraer->setVisible(false);
        ui->rb_kilogramosExtraer->setVisible(false);
        ui->pb_aceptarExtraer->setEnabled(false);
    }
    //updateExistentes();
    updateExistenteExtraer();
}

void form_almacenes::updateExistenteExtraer(){
    ProductService productService;
    centralStorageService CentralStorageService;

    QString productName = ui->cb_productoExtraer->currentText();
    auto res = productService.getProductByName(productName);
    if( res.res != SUCCESS ){
        ui->l_existenteExtraer->setText("El producto " + productName + " no existe en el almacén");
        return;
    }
    auto cs = CentralStorageService.getCentralStorageById(res.data.id);
    double cantidad = 0;
    if( cs.res == SUCCESS )
        cantidad = cs.data.amount;
    if( res.data.unitType == UNIDAD ){
        ui->l_existenteExtraer->setText( "En el almacén existen " + QString::number(cantidad) + " unidad(es) de " + productName );
        ui->sb_cantidadExtraer->setSuffix(" u");
    }else{
        weigth to = G;
        QString unit = " g";
        if( ui->rb_gramosExtraer->isChecked() )
            to = G, unit = " g";
        if( ui->rb_kilogramosExtraer->isChecked() )
            to = KG, unit = " kg";
        //if( ui->rb_librasExtraer->isChecked() )
        //    to = LB, unit = " lb";
        cantidad = utiles::convertPeso(G, to, cantidad);
        ui->l_existenteExtraer->setText("En el almacén existen " + utiles::truncS(cantidad,  1) + unit + " de " + productName);
        ui->sb_cantidadExtraer->setSuffix(unit);
    }
    ui->sb_cantidadExtraer->setValue(0);
    ui->sb_cantidadExtraer->setMaximum( utiles::trunc(cantidad,  1) );
}

void form_almacenes::updateUnit(){
    setUnit();
    updateCentralTable(ui->le_Centralsearch->text());
    updateLocalTable(ui->le_localSearch->text());
}


void form_almacenes::updateCentralTable(QString search){

    centralStorageService CentralStorageService;
    centralModel = CentralStorageService.getCentralStorageBySearch( utiles::searchToRegExp(search) ).data;
    ui->centralTable->clearContents();
    ui->centralTable->setRowCount(centralModel.size());
    int row = 0;
    foreach (auto &i, centralModel) {
        QTableWidgetItem *producto = new QTableWidgetItem(i.name);
        producto->setFlags(flags);
        producto->setTextAlignment(utiles::TextAlign);

        QString unit = "";
        if( i.unitType == SOLIDO )
            unit = " " + utiles::unitFromPeso(PESO);
        else
            unit = " u";

        double precio = (i.unitType == UNIDAD) ? i.price : utiles::convertPrecio(G, PESO, i.price);
        QTableWidgetItem *price = new QTableWidgetItem( QString::number(precio, 'f', 2) + " CUP");
        price->setFlags(flags);
        price->setTextAlignment(utiles::TextAlign);



        double cantidad = (i.unitType == UNIDAD) ? i.amount : utiles::convertPeso(G, PESO, i.amount);
        QTableWidgetItem *amount = new QTableWidgetItem( utiles::truncS(cantidad, 1) + unit);
        amount->setFlags(flags);
        amount->setTextAlignment(utiles::TextAlign);
        ui->centralTable->setItem(row, 0, producto);
        ui->centralTable->setItem(row, 1, amount);
        ui->centralTable->setItem(row, 2, price);
        row++;
    }
}

void form_almacenes::updateLocalTable(QString search){

    storageService LocalStorageService;
    localModel = LocalStorageService.getLocalStorageBySearch( utiles::searchToRegExp(search) ).data;
    ui->localTable->clearContents();
    ui->localTable->setRowCount(localModel.size());
    int row = 0;
    foreach (auto i, localModel) {
        QTableWidgetItem *producto = new QTableWidgetItem(i.name);
        producto->setTextAlignment(utiles::TextAlign);
        QString unit;
        if( i.unitType == SOLIDO )
            unit = " " + utiles::unitFromPeso(PESO);
        else
            unit = " u";

        double precio = (i.unitType == UNIDAD) ? i.price : utiles::convertPrecio(G, PESO, i.price);
        QTableWidgetItem *price = new QTableWidgetItem( QString::number(precio, 'f', 2) + " CUP");
        price->setTextAlignment(utiles::TextAlign);
        double cant = (i.unitType == UNIDAD) ? i.amount : utiles::convertPeso(G, PESO, i.amount);
        QTableWidgetItem *amount = new QTableWidgetItem(utiles::truncS(cant, 1) + unit);
        amount->setTextAlignment(utiles::TextAlign);

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

    QString productName = ui->cb_mcProduct->currentText();
    auto res = productService.getProductByName(productName);
    if( res.res != SUCCESS ){
        ui->l_mcExistente->setText("El producto " + productName + " no existe en el almacén");
        return;
    }

    auto cs = StorageService.getStorageById(res.data.id);
    double cantidad = 0;
    if( cs.res == SUCCESS )
        cantidad = cs.data.amount;
    if( res.data.unitType == UNIDAD ){
        ui->l_mcExistente->setText( "En el almacén existen " + QString::number(cantidad) + " unidad(es) de " + productName );
        ui->sb_mcCantidad->setSuffix(" u");
    }else{
        weigth to = G;
        QString unit = " g";
        if( ui->rb_mcGramos->isChecked() )
            to = G, unit = " g";
        if( ui->rb_mcKilogramos->isChecked() )
            to = KG, unit = " kg";
        //if( ui->rb_mcLibras->isChecked() )
        //    to = LB, unit = " lb";
        cantidad = utiles::convertPeso(G, to, cantidad);
        ui->l_mcExistente->setText("En el almacén existen " + utiles::truncS(cantidad, 1) + unit + " de " + productName);
        ui->sb_mcCantidad->setSuffix(unit);
    }
    ui->sb_mcCantidad->setValue(0);
    ui->sb_mcCantidad->setMaximum(utiles::trunc(cantidad, 1));
}

void form_almacenes::updateMCRadioButtons( QString product )
{
    ProductService productService;
    auto pr = productService.getProductByName(product);
    ui->sb_mcCantidad->setValue(0);
    emit ui->sb_mcCantidad->valueChanged(0);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == SOLIDO ){
            ui->rb_mcGramos->setVisible(true);
            //ui->rb_mcLibras->setVisible(true);
            ui->rb_mcKilogramos->setVisible(true);
            ui->rb_mcGramos->setChecked(true);
            ui->sb_mcCantidad->setSuffix( " g" );
        }else{
            ui->rb_mcGramos->setVisible(false);
            //ui->rb_mcLibras->setVisible(false);
            ui->rb_mcKilogramos->setVisible(false);
            ui->sb_mcCantidad->setSuffix(" u");
        }
    }else{
        ui->rb_mcGramos->setVisible(false);
        //ui->rb_mcLibras->setVisible(false);
        ui->rb_mcKilogramos->setVisible(false);
        ui->pb_mcAccept->setEnabled(false);
    }
    //updateExistentes();
    updateMCExistente();
}


void form_almacenes::on_pb_mcAccept_clicked()
{
    ProductService productService;
    storageService StorageService;
    QString productName = ui->cb_mcProduct->currentText();
    auto prod = productService.getProductByName(productName);
    if( prod.res == RECORD_NOT_FOUND ){
        QMessageBox::critical(this,"Información", "El Producto <strong>" + productName + "</strong> no existe en el almacén",QMessageBox::Ok);
        return;
    }
    auto storeProduct = StorageService.getStorageById(prod.data.id);
    double cantidad = ui->sb_mcCantidad->value();
    double realcant = cantidad;
    weigth from = G;
    QString unit = " u";
    if( prod.data.unitType == SOLIDO ){
        if( ui->rb_mcGramos->isChecked() )
            from = G, unit = " g";
        if( ui->rb_mcKilogramos->isChecked() )
            from = KG, unit = " kg";
        //if( ui->rb_mcLibras->isChecked() )
        //    from = LB, unit = " lb";
    }

    cantidad = utiles::convertPeso(from, G, cantidad);
    if( cantidad > storeProduct.data.amount ){
        QMessageBox::critical(this,"Información", "La cantidad seleccionada excede a la existente en el almacén",QMessageBox::Ok);
        return;
    }


    auto r = QMessageBox::information(this,"Información", "Usted va a mover <strong>" + utiles::truncS(realcant, 1) + unit + "</strong> de <strong>" + productName + "</strong>", QMessageBox::Ok | QMessageBox::Cancel );

    if( r == QMessageBox::Ok ){
        StorageService.moveToCentral(prod.data.id, cantidad);
        centralStorageService CentralStorageService;

        auto cs =  CentralStorageService.getCentralStorageById(prod.data.id);
        auto s = StorageService.getStorageById(prod.data.id);
        TransactionService transactionService;

        QString suffix = unit;
        transactionService.insertTransaction( TransactionDto(0, MOVIMIENTO, LOCAL, realcant, prod.data.id, QDate::currentDate(), UserService::loggedUser, prod.data.price, 0, s.data.amount, cs.data.amount, prod.data.productName, prod.data.unitType, suffix) );

        ui->sb_mcCantidad->setValue(0);
        emit ui->sb_mcCantidad->valueChanged(0);

        updateCentralTable(ui->le_localSearch->text());
        updateLocalTable(ui->le_Centralsearch->text());
        updateExistentes();
    }

}

void form_almacenes::updateExistentes(){
    updateMCExistente();
    updateExistenteExtraer();
    updateExistenteExtraerLocal();
    updateExistenteMoverAlLocal();
}

void form_almacenes::updateRadioButtonsCompra(QString product){

    ProductService productService;
    auto pr = productService.getProductByName(product);
    ui->sb_cantidadCompra->setValue(0);
    emit ui->sb_cantidadCompra->valueChanged(0);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == SOLIDO ){
            ui->rb_gramosCompra->setVisible(true);
            ui->rb_librasCompra->setVisible(true);
            ui->rb_kilogramosCompra->setVisible(true);
            ui->rb_librasCompra->setChecked(true);
            ui->sb_cantidadCompra->setSuffix( " lb" );
            ui->sb_mermaCompra->setSuffix(" lb");
        }else{
            ui->rb_gramosCompra->setVisible(false);
            ui->rb_librasCompra->setVisible(false);
            ui->rb_kilogramosCompra->setVisible(false);
            ui->sb_cantidadCompra->setSuffix(" u");
            ui->sb_mermaCompra->setSuffix(" u");
        }
    }else{
        ui->rb_gramosCompra->setVisible(false);
        ui->rb_librasCompra->setVisible(false);
        ui->rb_kilogramosCompra->setVisible(false);
        ui->pb_insertarCompra->setEnabled(false);
    }
    ui->cb_mermaCompra->setChecked(false);
    ui->sb_mermaCompra->setEnabled(false);
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
        QMessageBox::critical(this,"Información","El producto <strong>" + productName + "</strong> no existe",QMessageBox::Ok);
        return;
    }

    if( CentralStorageService.getCentralStorageById(product.data.id).res == RECORD_NOT_FOUND ){
        CentralStorageService.insertCentralStorage( centralStorageDto(product.data.id,0) );
    }

    double cant = ui->sb_cantidadCompra->value();
    if( cant == 0 ){
        QMessageBox::information(this, "Información", "La cantidad de producto no puede ser 0", QMessageBox::Ok);
        return;
    }
    double merma = 0;
    if( ui->cb_mermaCompra->isChecked() )
        merma = ui->sb_mermaCompra->value();
    if( merma > cant ){
        QMessageBox::critical(this,"Error", "La merma es mayor que la cantidad", QMessageBox::Ok);
        return;
    }

    double mermaInicial = merma;
    double realCant = cant - merma;
    double cantidadInicial = cant;
    double pricePerUnit = ui->sb_precioCompra->value();
    double precioInicial = pricePerUnit;
    double precioTotal = pricePerUnit * cant;

    weigth from = G;
    if( product.data.unitType == SOLIDO ){
        if( ui->rb_gramosCompra->isChecked() ) from = G;
        if( ui->rb_kilogramosCompra->isChecked() ) from = KG;
        if( ui->rb_librasCompra->isChecked() ) from = LB;
    }

    pricePerUnit = 0;
    if( realCant > 0 )
        pricePerUnit = precioTotal / realCant;

    cant = utiles::convertPeso(from, G, cant);
    realCant = utiles::convertPeso(from, G, realCant);
    merma = utiles::convertPeso(from, G, merma);
    pricePerUnit = utiles::convertPrecio(from, G, pricePerUnit);

    QString unit = " " + utiles::unitFromPeso(from);
    if( product.data.unitType == UNIDAD )
        unit = " u";

    auto res = QMessageBox::information(this, "Información", "¿Está seguro que desea insertar la compra de <strong>" + utiles::truncS(cantidadInicial, 1) + unit + "</strong>" + " de <strong>" + productName + "</strong>" + " al precio de <strong>$" + utiles::truncS(precioInicial, 2) + "</strong>?", QMessageBox::Ok, QMessageBox::Cancel );

    if( res == QMessageBox::Ok ){
        CentralStorageService.modifyCentralStorage(product.data.id, realCant, 1, pricePerUnit, merma);

        auto cs = CentralStorageService.getCentralStorageById(product.data.id);

        storageService StorageService;
        auto s = StorageService.getStorageById(product.data.id);

        TransactionService transactionService;

        QString suffix = unit;

        transactionService.insertTransaction( TransactionDto(0,COMPRA,CENTRAL,cantidadInicial,product.data.id,QDate::currentDate(),UserService::loggedUser,precioInicial, mermaInicial, s.data.amount, cs.data.amount, product.data.productName, product.data.unitType,suffix) );

        updateCentralTable( ui->le_Centralsearch->text() );
        updateLocalTable( ui->le_localSearch->text() );
        ui->sb_cantidadCompra->setValue(0);
        emit ui->sb_cantidadCompra->valueChanged(0);
        ui->sb_mermaCompra->setValue(0);
        ui->sb_precioCompra->setValue(0);
        updateExistentes();
    }
}

void form_almacenes::on_pb_acceptInsertar_clicked()
{
    if( ui->le_productInsertar->text() == "" ){
        QMessageBox::information(this,"Información","Debe escribir el nombre del producto",QMessageBox::Ok);
        return;
    }
    centralStorageService CentralStorgeService;
    storageService StorageService;
    QString productName = ui->le_productInsertar->text();
    auto res = QMessageBox::warning(this,"Información","Está seguro que desea insertar el producto: <strong>" + productName + "</strong>",QMessageBox::Ok, QMessageBox::Cancel);
    if( res == QMessageBox::Ok ){
        ProductService productService;
        int unitType = SOLIDO;
        if( ui->rb_solidoInsertar->isChecked() )
            unitType = SOLIDO;
        else
            unitType = UNIDAD;
        auto ret = productService.getProductByName(productName);
        if( ret.res == SUCCESS ){
            QMessageBox::information(this, "Información", "El producto <strong>" + productName + "</strong> ya existe",QMessageBox::Ok);
            return;
        }
        if( ret.res == RECORD_NOT_FOUND ){
            auto res = productService.insertProduct(ProductDto(0,productName,unitType,0));
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
    updateLocalTable(ui->le_localSearch->text());
    updateExistentes();
}

void form_almacenes::updateRadioButtonsMoverAlLocal(QString product){

    ProductService productService;
    auto pr = productService.getProductByName(product);
    ui->sb_cantidadMoverAlLocal->setValue(0);
    emit ui->sb_cantidadMoverAlLocal->valueChanged(0);
    if( pr.res == SUCCESS ){
        if( pr.data.unitType == SOLIDO ){
            ui->rb_gramosMoverAlLocal->setVisible(true);
            //ui->rb_librasMoverAlLocal->setVisible(true);
            ui->rb_kilogramosMoverAlLocal->setVisible(true);
            ui->rb_gramosMoverAlLocal->setChecked(true);
            ui->sb_cantidadMoverAlLocal->setSuffix(" g");
        }else{
            ui->rb_gramosMoverAlLocal->setVisible(false);
            //ui->rb_librasMoverAlLocal->setVisible(false);
            ui->rb_kilogramosMoverAlLocal->setVisible(false);
            ui->sb_cantidadMoverAlLocal->setSuffix(" u");
        }
    }else{
        ui->rb_gramosMoverAlLocal->setVisible(false);
        //ui->rb_librasMoverAlLocal->setVisible(false);
        ui->rb_kilogramosMoverAlLocal->setVisible(false);
        ui->pb_MoverAlLocal->setEnabled(false);
    }
    updateExistenteMoverAlLocal();
    //updateExistentes();
}

void form_almacenes::updateExistenteMoverAlLocal(){
    ProductService productService;
    centralStorageService CentralStorageService;

    QString productName = ui->cb_productMoverAlLocal->currentText();
    auto res = productService.getProductByName(productName);
    if( res.res != SUCCESS ){
        ui->l_existenteMoverAlLocal->setText("El producto " + productName + " no existe en el almacén");
        return;
    }
    auto cs = CentralStorageService.getCentralStorageById(res.data.id);
    double cantidad = 0;
    if( cs.res == SUCCESS )
        cantidad = cs.data.amount;
    if( res.data.unitType == UNIDAD ){
        ui->l_existenteMoverAlLocal->setText( "En el almacén existen " + QString::number(cantidad) + " unidad(es) de " + productName );
        ui->sb_cantidadMoverAlLocal->setSuffix(" u");
    }else{
        weigth to = G;
        QString unit = " g";
        if( ui->rb_gramosMoverAlLocal->isChecked() )
            to = G, unit = " g";
        if( ui->rb_kilogramosMoverAlLocal->isChecked() )
            to = KG, unit = " kg";
        //if( ui->rb_librasMoverAlLocal->isChecked() )
        //    to = LB, unit = " lb";
        cantidad = utiles::convertPeso(G, to, cantidad);
        ui->l_existenteMoverAlLocal->setText("En el almacén existen " + utiles::truncS(cantidad, 1) + unit + " de " + productName);
        ui->sb_cantidadMoverAlLocal->setSuffix(unit);
    }
    ui->sb_cantidadMoverAlLocal->setValue(0);
    ui->sb_cantidadMoverAlLocal->setMaximum( utiles::trunc(cantidad, 1) );
}

void form_almacenes::on_pb_MoverAlLocal_clicked()
{
    ProductService productService;
    centralStorageService CentralStorageService;
    QString productName = ui->cb_productMoverAlLocal->currentText();
    auto prod = productService.getProductByName(productName);
    if( prod.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información", "El Producto <strong>" + productName + "</strong> no existe en el almacén",QMessageBox::Ok);
        return;
    }
    auto storeProduct = CentralStorageService.getCentralStorageById(prod.data.id);
    double cantidad = ui->sb_cantidadMoverAlLocal->value();
    qDebug() << "Cantidad" << cantidad;
    double realcant = cantidad;
    qDebug() << "RealCant" << realcant;
    if( cantidad == 0 ){
        QMessageBox::information(this, "Información", "La cantidad de producto a mover no puede ser 0", QMessageBox::Ok);
        return;
    }
    weigth from = G;
    QString unit = " u";
    if( prod.data.unitType == SOLIDO ){
        if( ui->rb_gramosMoverAlLocal->isChecked() )
            from = G, unit = " g";
        if( ui->rb_kilogramosMoverAlLocal->isChecked() )
            from = KG, unit = " kg";
        //if( ui->rb_librasMoverAlLocal->isChecked() )
        //    from = LB, unit = " lb";
    }
    cantidad = utiles::convertPeso(from, G, cantidad);
    if( cantidad > storeProduct.data.amount ){
        QMessageBox::information(this,"Información", "La cantidad seleccionada excede a la existente en el almacén",QMessageBox::Ok);
        return;
    }

    qDebug() << "RealCant" << utiles::truncS(realcant, 1);
    auto res = QMessageBox::information(this,"Información", "Usted va a mover <strong>" + utiles::truncS(realcant, 1) + unit + "</strong> de <strong>" + productName + "</strong>", QMessageBox::Ok | QMessageBox::Cancel );

    if( res == QMessageBox::Ok ){
        CentralStorageService.moveToLocal(prod.data.id, cantidad);
        storageService StorageService;

        auto cs = CentralStorageService.getCentralStorageById(prod.data.id);
        auto s = StorageService.getStorageById(prod.data.id);
        TransactionService transactionService;
        QString suffix = unit;
        transactionService.insertTransaction( TransactionDto(0,MOVIMIENTO,CENTRAL,realcant,prod.data.id, QDate::currentDate(), UserService::loggedUser, prod.data.price, 0, s.data.amount, cs.data.amount, prod.data.productName, prod.data.unitType, suffix) );

        ui->sb_cantidadMoverAlLocal->setValue(0);
        emit ui->sb_cantidadMoverAlLocal->valueChanged(0);
        updateCentralTable( ui->le_localSearch->text() );
        updateLocalTable( ui->le_localSearch->text() );
        updateExistentes();
    }
}

void form_almacenes::on_pb_aceptarExtraer_clicked()
{
    ProductService productService;
    centralStorageService CentralStorageService;
    QString productName = ui->cb_productoExtraer->currentText();
    auto prod = productService.getProductByName(productName);
    if( prod.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información", "El Producto <strong>" + ui->cb_productoExtraer->currentText() + "</strong> no existe en el almacén",QMessageBox::Ok);
        return;
    }
    auto storeProduct = CentralStorageService.getCentralStorageById(prod.data.id);
    double cantidad = ui->sb_cantidadExtraer->value();
    double realcant = cantidad;
    if( !cantidad ){
        QMessageBox::information(this, "Información", "La cantidad de producto a extraer no puede ser 0", QMessageBox::Ok);
        return;
    }
    weigth from = G;
    QString unit = " u";
    if( prod.data.unitType == SOLIDO ){
        if( ui->rb_gramosExtraer->isChecked() )
            from = G, unit = " g";
        if( ui->rb_kilogramosExtraer->isChecked() )
            from = KG, unit = " kg";
        //if( ui->rb_librasExtraer->isChecked() )
        //    from = LB, unit = " lb";
    }

    cantidad = utiles::convertPeso(from, G, cantidad);
    if( cantidad > storeProduct.data.amount ){
        QMessageBox::information(this,"Información", "La cantidad seleccionada excede a la existente en el almacén",QMessageBox::Ok);
        return;
    }

    auto res = QMessageBox::information(this, "Información", "¿Está seguro que desea extraer <strong>" + utiles::truncS(realcant, 1) + unit + "</strong>" + " de <strong>" + productName + "</strong>?", QMessageBox::Ok, QMessageBox::Cancel );

    if( res == QMessageBox::Ok ){
        TransactionService transactionService;
        storageService StorageService;
        CentralStorageService.extract(prod.data.id, cantidad);
        auto cs = CentralStorageService.getCentralStorageById(prod.data.id);
        auto s = StorageService.getStorageById(prod.data.id);

        QString suffix = unit;
        transactionService.insertTransaction( TransactionDto(0,EXTRACCION,CENTRAL,realcant,prod.data.id, QDate::currentDate(), UserService::loggedUser,prod.data.price,0,s.data.amount,cs.data.amount, prod.data.productName, prod.data.unitType, suffix) );

        ExpensesService expensesService;
        expensesService.insertExpenses(ExpensesDto(0,"Extracción de " + QString::number(realcant, 'f', 2) + suffix + " de " + productName, prod.data.price * cantidad, QDate::currentDate()));

        ui->sb_cantidadExtraer->setValue(0);
        emit ui->sb_cantidadExtraer->valueChanged(0);

        updateCentralTable(ui->le_Centralsearch->text());
        updateLocalTable(ui->le_localSearch->text());
        updateExistentes();
    }
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
    auto product = productService.getProductByID( ProductDto(centralModel.at(row).id,"",0,0) );
    auto list = productService.isUsed(product.data.id).data;
    if( list.isEmpty() ){
        auto res = QMessageBox::warning(this, "Información", "¿Está seguro que desea eliminar el producto <strong>" + product.data.productName + "</strong>?", QMessageBox::Ok, QMessageBox::Cancel);
        if( res == QMessageBox::Ok ){
            productService.deleteProduct(product.data);
            CentralStorageService.deleteCentralStorage( product.data.id );
            StorageService.deleteStorage( product.data.id );
        }
    }else{
        auto res = QMessageBox::critical(this, "Información", "El producto <strong>" + product.data.productName + "</strong> ha sido utilizado en varias órdenes. Su eliminación puede causar errores en la información mostrada. <strong>Le recomendamos no hacerlo</strong>. ¿Está seguro que desea eliminarlo?", QMessageBox::Ok | QMessageBox::Cancel );
        if( res == QMessageBox::Ok ){
            productService.deleteProduct(product.data);
            CentralStorageService.deleteCentralStorage( product.data.id );
            StorageService.deleteStorage( product.data.id );
        }
    }

    updateCentralTable(ui->le_Centralsearch->text());
    updateLocalTable(ui->le_localSearch->text());
    updateExistentes();
    updateProducts();
}


void form_almacenes::on_centralTable_cellClicked(int row, int column)
{

    if( row < 0 ) return;
    if( UserService::loggedUser != 0 )
        ui->pb_eliminarProduct->setEnabled(true);
    int index = ui->cb_productCompra->findText( ui->centralTable->item(row, 0)->text() );
    ui->cb_productCompra->setCurrentIndex(index);
    ui->cb_productMoverAlLocal->setCurrentIndex(index);
    ui->cb_productoExtraer->setCurrentIndex(index);

    ui->sb_cantidadCompra->setValue(0);
    ui->pb_insertarCompra->setEnabled(false);

    ui->sb_cantidadExtraer->setValue(0);
    ui->pb_aceptarExtraer->setEnabled(false);


    qDebug() << "click " << centralModel.at(row).amount << utiles::truncS(centralModel.at(row).amount,2);
    ui->sb_cantidadMoverAlLocal->setMaximum( utiles::trunc(centralModel.at(row).amount,1) );
    ui->sb_cantidadMoverAlLocal->setValue( utiles::trunc(centralModel.at(row).amount,1) );
    ui->rb_gramosMoverAlLocal->setChecked(true);
    QString unit = "";
    if( centralModel.at(row).unitType == UNIDAD )
        unit = " u";
    else
        unit = " g";
    ui->sb_cantidadMoverAlLocal->setSuffix(unit);
    //ui->pb_MoverAlLocal->setEnabled(true);
    qDebug() << "Despues";
    //emit ui->sb_cantidadMoverAlLocal->valueChanged( utiles::trunc(centralModel.at(row).amount,2) );

}

void form_almacenes::on_pb_aceptarExtraerLocal_clicked()
{
    ProductService productService;
    storageService StorageService;
    QString productName = ui->cb_productoExtraerLocal->currentText();
    auto prod = productService.getProductByName(productName);
    if( prod.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información", "El Producto <strong>" + productName + "</strong> no existe en el almacén",QMessageBox::Ok);
        return;
    }
    auto storeProduct = StorageService.getStorageById(prod.data.id);
    double cantidad = ui->sb_cantidadExtraerLocal->value();
    double realcant = cantidad;
    QString unit = " u";
    weigth from = G;
    if( prod.data.unitType == SOLIDO ){
        if( ui->rb_gramosExtraerLocal->isChecked() )
            from = G, unit = " g";
        if( ui->rb_kilogramosExtraerLocal->isChecked() )
            from = KG, unit = " kg";
        //if( ui->rb_librasExtraerLocal->isChecked() )
        //    from = LB, unit = " lb";
    }
    cantidad = utiles::convertPeso(from, G, cantidad);
    if( cantidad > storeProduct.data.amount ){
        QMessageBox::information(this,"Información", "La cantidad seleccionada excede a la existente en el almacén",QMessageBox::Ok);
        return;
    }

    auto res = QMessageBox::information(this, "Información", "¿Está seguro que desea extraer <strong>" + utiles::truncS(realcant, 1) + unit + "</strong> de <strong>" + productName + "<strong>?", QMessageBox::Ok, QMessageBox::Cancel);
    if( res == QMessageBox::Ok ){
        centralStorageService CentralStorageService;
        StorageService.extract(prod.data.id, cantidad);

        auto cs = CentralStorageService.getCentralStorageById(prod.data.id);
        auto s = StorageService.getStorageById(prod.data.id);

        TransactionService transactionService;
        QString suffix = unit;
        transactionService.insertTransaction(TransactionDto(0, EXTRACCION,LOCAL,realcant,prod.data.id, QDate::currentDate(), UserService::loggedUser, prod.data.price, 0, s.data.amount, cs.data.amount, prod.data.productName, prod.data.unitType, suffix));

        ExpensesService expensesService;
        expensesService.insertExpenses(ExpensesDto(0,"Extracción de " + QString::number(realcant, 'f', 2) + suffix + " de " + productName, prod.data.price * cantidad, QDate::currentDate()));

        ui->sb_cantidadExtraerLocal->setValue(0);
        emit ui->sb_cantidadExtraerLocal->valueChanged(0);

        updateLocalTable(ui->le_localSearch->text());
        updateCentralTable(ui->le_Centralsearch->text());
        updateExistentes();
    }
}

void form_almacenes::on_localTable_cellClicked(int row, int column)
{
    if( row < 0 ) return;
    int index = ui->cb_mcProduct->findText( ui->localTable->item(row, 0)->text() );
    ui->cb_mcProduct->setCurrentIndex(index);
    ui->cb_productoExtraerLocal->setCurrentIndex(index);

    ui->sb_mcCantidad->setMaximum( utiles::trunc(localModel.at(row).amount,1) );
    ui->sb_mcCantidad->setValue( utiles::trunc(localModel.at(row).amount,1) );
    ui->rb_mcGramos->setChecked(true);

    QString unit = "";
    if( localModel.at(row).unitType == UNIDAD )
        unit = " u";
    else
        unit = " g";

    ui->sb_mcCantidad->setSuffix(unit);
    //emit ui->sb_mcCantidad->valueChanged( utiles::trunc(localModel.at(row).amount,2) );

    ui->sb_cantidadExtraerLocal->setValue(0);
    ui->pb_aceptarExtraerLocal->setEnabled(false);
}


void form_almacenes::on_sb_cantidadMoverAlLocal_valueChanged(double arg1)
{
    qDebug() << "Señal" << arg1;
    ProductService productService;
    QString productName = ui->cb_productMoverAlLocal->currentText();
    auto pr = productService.getProductByName(productName);
    ui->pb_MoverAlLocal->setEnabled(arg1 > 0 && pr.res == SUCCESS);
}

void form_almacenes::on_sb_cantidadExtraer_valueChanged(double arg1)
{
    ProductService productService;
    QString productName = ui->cb_productoExtraer->currentText();
    auto pr = productService.getProductByName(productName);

    ui->pb_aceptarExtraer->setEnabled(arg1 > 0 && pr.res == SUCCESS);
}

void form_almacenes::on_sb_mcCantidad_valueChanged(double arg1)
{
    ProductService productService;
    QString productName = ui->cb_mcProduct->currentText();
    auto pr = productService.getProductByName(productName);

    ui->pb_mcAccept->setEnabled(arg1 > 0 && pr.res == SUCCESS);
}

void form_almacenes::on_sb_cantidadExtraerLocal_valueChanged(double arg1)
{
    ProductService productService;
    QString productName = ui->cb_productoExtraerLocal->currentText();
    auto pr = productService.getProductByName(productName);

    ui->pb_aceptarExtraerLocal->setEnabled(arg1 > 0 && pr.res == SUCCESS);
}


void form_almacenes::on_sb_cantidadCompra_valueChanged(double arg1)
{
    ProductService productService;
    QString productName = ui->cb_productCompra->currentText();
    auto pr = productService.getProductByName(productName);

    ui->pb_insertarCompra->setEnabled(arg1 > 0 && pr.res == SUCCESS);
}
