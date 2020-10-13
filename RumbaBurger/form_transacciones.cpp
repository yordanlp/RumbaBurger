#include "form_transacciones.h"
#include "ui_form_transacciones.h"
#include <Services/productservice.h>
#include <QCompleter>
#include <QMessageBox>
#include <Services/centralstoragetransactionservice.h>
#include <Services/centralstorageservice.h>
#include <Services/storageservice.h>
#include <Services/transactionservice.h>

form_transacciones::form_transacciones(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_transacciones)
{
    setUnit();
    ui->setupUi(this);
    ui->tabWidget->setTabText(0, "Movimientos");
    ui->tabWidget->setTabText(1, "Compra y extracciones");
    ui->tw_moviemientos->setColumnWidth(5, ui->tw_moviemientos->columnWidth(5) + 60);
    ui->tw_moviemientos->setColumnWidth(6, ui->tw_moviemientos->columnWidth(6) + 60);

    ProductService productService;
    QStringList products = productService.getAllProductsToString().data;
    QCompleter *completerMovimientos = new QCompleter(products);
    QCompleter *completerOperaciones = new QCompleter(products);
    ui->cb_productosCompraExtraccion->addItems(products);
    ui->cb_productosCompraExtraccion->setCompleter(completerOperaciones);

    ui->cb_productosMovimientos->addItems(products);
    ui->cb_productosMovimientos->setCompleter(completerMovimientos);

    ui->de_fechaFinalCompraExtraccion->setDate( QDate::currentDate() );
    ui->de_fechaFinalMovimientos->setDate( QDate::currentDate() );

    connect( ui->pb_filtrarMovimientos, SIGNAL(clicked(bool)), this, SLOT(filtrarMovimientos()) );
    connect( ui->pb_filtrarCompraExtraccion, SIGNAL(clicked(bool)), this, SLOT(filtrarOperaciones()) );
    filtrarMovimientos();
    filtrarOperaciones();
}

void form_transacciones::setUnit(){
    if( utiles::UNIDAD == "Gramos" )
        PESO = G;
    if( utiles::UNIDAD == "KiloGramos" )
        PESO = KG;
    if( utiles::UNIDAD == "Libras" )
        PESO = LB;
}

form_transacciones::~form_transacciones()
{
    delete ui;
}

void form_transacciones::updateUnit(){
    setUnit();
    filtrarMovimientos();
    filtrarOperaciones();
}

void form_transacciones::filtrarMovimientos(){
    QDate fInicial = ui->de_fechaInicialMovimientos->date();
    QDate fFinal = ui->de_fechaFinalMovimientos->date();
    if( fInicial > fFinal ){
        QMessageBox::information(this, "Información", "La fecha inicial no puede ser mayor que la fecha final", QMessageBox::Ok);
        return;
    }
    QString producto = ui->cb_productosMovimientos->currentText();
    int origin = ui->cb_origen->currentIndex();
    if( producto == "Todos" )
        producto = '%';

    origen o;
    if( origin == 0 )
        o = origen::ALL;
    if( origin == 2 )
        o = CENTRAL;
    if( origin == 1 )
        o = LOCAL;

    TransactionService transactionService;
    Movimientos = transactionService.getMovimientos(fInicial, fFinal, producto, o).data;

    int row = 0;
    ui->tw_moviemientos->setRowCount(Movimientos.size());
    foreach (auto m, Movimientos) {
        QTableWidgetItem *fecha = new QTableWidgetItem(m.date.toString(Qt::ISODate));
        fecha->setFlags(flags);

        QString desde, hasta;
        if( m.origin == CENTRAL )
            desde = "Almacén Central", hasta = "Almacén Local";
        if( m.origin == LOCAL )
            desde = "Almacén Local", hasta = "Almacén Central";

        QTableWidgetItem *from = new QTableWidgetItem( desde );
        from->setFlags(flags);

        QTableWidgetItem *to = new QTableWidgetItem( hasta );
        to->setFlags(flags);

        QTableWidgetItem *producto = new QTableWidgetItem( m.productName );
        producto->setFlags(flags);

        QString unit = "";
        if( m.unitType == SOLIDO )
            unit = utiles::unitFromPeso(PESO);
        else
            unit = "u";

        double cant = (unit == "u") ? m.amount : utiles::convertPeso(G, PESO, m.amount);
        QTableWidgetItem *cantidad = new QTableWidgetItem( QString::number(cant) + unit );
        cantidad->setFlags(flags);

        double dc = (unit == "u") ? m.aviable_in_central : utiles::convertPeso(G, PESO, m.aviable_in_central);
        QTableWidgetItem *disponible_central = new QTableWidgetItem( QString::number( dc, 'f', 2 ) + unit);
        disponible_central->setFlags(flags);

        double dl = (unit == "u") ? m.aviable_in_local : utiles::convertPeso(G, PESO, m.aviable_in_local);
        QTableWidgetItem *disponible_local = new QTableWidgetItem( QString::number( dl, 'f', 2 ) + unit);
        disponible_local->setFlags(flags);

        ui->tw_moviemientos->setItem(row, 0, fecha);
        ui->tw_moviemientos->setItem(row, 1, from);
        ui->tw_moviemientos->setItem(row, 2, to);
        ui->tw_moviemientos->setItem(row, 3, producto);
        ui->tw_moviemientos->setItem(row, 4, cantidad);
        ui->tw_moviemientos->setItem(row, 5, disponible_central);
        ui->tw_moviemientos->setItem(row, 6, disponible_local);

        row++;
    }
    //ui->pb_deshacerMovimientos->setEnabled(false);
}

void form_transacciones::filtrarOperaciones(){
    QDate fInicial = ui->de_fechaInicialCompraExtraccion->date();
    QDate fFinal = ui->de_fechaFinalCompraExtraccion->date();
    if( fInicial > fFinal ){
        QMessageBox::information(this, "Información", "La fecha inicial no puede ser mayor que la fecha final", QMessageBox::Ok);
        return;
    }
    QString producto = ui->cb_productosCompraExtraccion->currentText();
    int origin = ui->cb_origenOperaciones->currentIndex();
    if( producto == "Todos" )
        producto = '%';

    origen o;
    if( origin == 0 )
        o = origen::ALL;
    if( origin == 2 )
        o = CENTRAL;
    if( origin == 1 )
        o = LOCAL;

    operaciones op;
    int operations = ui->cb_operaciones->currentIndex();
    if( operations == 0 )
        op = ALL_OPS;
    if( operations == 1 )
        op = COMPRA;
    if( operations == 2 )
        op = EXTRACCION;

    TransactionService transactionService;
    Operaciones = transactionService.getExtraccionesYCompras(fInicial, fFinal, producto, op, o).data;

    int row = 0;
    ui->tw_CompraExtraccion->setRowCount(Operaciones.size());
    foreach (auto m, Operaciones) {
        QTableWidgetItem *fecha = new QTableWidgetItem(m.date.toString(Qt::ISODate));
        fecha->setFlags(flags);

        QString tipo;
        if( m.type == COMPRA )
            tipo = "Compra";
        else
            tipo = "Extracción";

        QTableWidgetItem *type = new QTableWidgetItem( tipo );
        type->setFlags(flags);

        QString origin;
        if( m.origin == CENTRAL )
            origin = "Almacén Central";
        if( m.origin == LOCAL )
            origin = "Almacén Local";

        QString unit = "";
        if( m.unitType == SOLIDO )
            unit = utiles::unitFromPeso(PESO);
        else
            unit = "u";

        QTableWidgetItem *from = new QTableWidgetItem( origin );
        from->setFlags(flags);

        QTableWidgetItem *producto = new QTableWidgetItem( m.productName );
        producto->setFlags(flags);

        double cant = (unit == "u") ? m.amount : utiles::convertPeso(G, PESO, m.amount);
        QTableWidgetItem *cantidad = new QTableWidgetItem( QString::number(cant, 'f', 2) + unit );
        cantidad->setFlags(flags);

        double merm = (unit == "u") ? m.merma : utiles::convertPeso(G, PESO, m.merma);
        QTableWidgetItem *merma = new QTableWidgetItem( QString::number(merm, 'f', 2) + unit);
        merma->setFlags(flags);

        double pr = (unit == "u") ? m.price : utiles::convertPrecio(G, PESO, m.price);
        QTableWidgetItem *precio = new QTableWidgetItem( (m.type == COMPRA) ? ("$" + QString::number( pr, 'f', 2 )) : "-" );
        precio->setFlags(flags);

        double av = (unit == "u") ? m.aviable_in_central : utiles::convertPeso(G, PESO, m.aviable_in_central);
        QTableWidgetItem *disponible = new QTableWidgetItem( QString::number( av, 'f', 2 ) + unit );
        disponible->setFlags(flags);

        ui->tw_CompraExtraccion->setItem(row, 0, fecha);
        ui->tw_CompraExtraccion->setItem(row, 1, type);
        ui->tw_CompraExtraccion->setItem(row, 2, from);
        ui->tw_CompraExtraccion->setItem(row, 3, producto);
        ui->tw_CompraExtraccion->setItem(row, 4, cantidad);
        ui->tw_CompraExtraccion->setItem(row, 5, merma);
        ui->tw_CompraExtraccion->setItem(row, 6, precio);
        ui->tw_CompraExtraccion->setItem(row, 7, disponible);

        row++;
    }
    //ui->pb_deshacerCompraExtraccion->setEnabled(false);
}

void form_transacciones::on_pb_deshacerMovimientos_clicked()
{
    int row = ui->tw_moviemientos->currentRow();
    if( row < 0 ){
        QMessageBox::information(this, "Información", "Debe seleccionar una transacción", QMessageBox::Ok);
        return;
    }

    auto mov = Movimientos.at(row);

    centralStorageService CentralStorageService;
    storageService StorageService;
    if( mov.origin == origen::LOCAL ){
        CentralStorageService.moveToLocal( mov.idProduct, mov.amount );
    }else{
        StorageService.moveToCentral( mov.idProduct, mov.amount );
    }

    TransactionService transactionService;
    transactionService.deleteTransaction(mov.id);
    filtrarMovimientos();

}

void form_transacciones::on_tw_moviemientos_cellClicked(int row, int column)
{
    //ui->pb_deshacerMovimientos->setEnabled(true);
}

void form_transacciones::on_tw_CompraExtraccion_cellClicked(int row, int column)
{
    //ui->pb_deshacerCompraExtraccion->setEnabled(true);
}

void form_transacciones::on_pb_deshacerCompraExtraccion_clicked()
{
    int row = ui->tw_CompraExtraccion->currentRow();
    if( row < 0 ){
        QMessageBox::information(this, "Información", "Debe seleccionar una transacción", QMessageBox::Ok);
        return;
    }

    auto mov = Operaciones.at(row);

    centralStorageService CentralStorageService;
    //storageService StorageService;
    TransactionService transactionService;

    if( mov.type == operaciones::EXTRACCION ){
        if( mov.origin == origen::LOCAL ){
            CentralStorageService.modifyCentralStorage(mov.idProduct, mov.amount, 1, mov.price, mov.merma);
            CentralStorageService.moveToLocal(mov.idProduct, mov.amount);
        }else{
            CentralStorageService.modifyCentralStorage(mov.idProduct, mov.amount, 1, mov.price, mov.merma);
        }
    }else{
        if( mov.origin == origen::CENTRAL ){
            qDebug() << "Deshacer Compra Central " <<  mov.productName << mov.amount;
            CentralStorageService.modifyCentralStorage(mov.idProduct, mov.amount - mov.merma, -1, mov.price, mov.merma );
        }
    }

    transactionService.deleteTransaction( mov.id );
    filtrarOperaciones();

}
