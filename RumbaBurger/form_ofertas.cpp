#include "form_ofertas.h"
#include "ui_form_ofertas.h"
#include <Services/dishservice.h>
#include <Services/ingredientsservice.h>
#include <QMessageBox>
#include <QCompleter>

using namespace std;

form_ofertas::form_ofertas(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_ofertas)
{
    ui->setupUi(this);
    rowSelected = -1;
    connect(this, SIGNAL(rowChanged()), this, SLOT(updateAll()));
    updateAll();
    updateOfertas("");
    ProductService productService;
    QStringList products = productService.getAllProductsToString().data;
    QCompleter *completer = new QCompleter(products,this);
    ui->cb_insProduct->setCompleter(completer);
    ui->cb_insProduct->addItems(products);
    connect(ui->cb_insProduct, SIGNAL(currentTextChanged(QString)), this, SLOT(updateUnit(QString)));
    updateUnit(ui->cb_insProduct->currentText());
    //ui->pb_delOferta->setEnabled(false);

    if( UserService::loggedUser == 0 ){
        ui->le_editaName->setEnabled(false);
        ui->le_insName->setEnabled(false);
        ui->sb_editPrecio->setEnabled(false);
        ui->sb_insCantidad->setEnabled(false);
        ui->sb_insPrice->setEnabled(false);
        ui->pb_addOferta->setEnabled(false);
        ui->pb_delIngrediente->setEnabled(false);
        ui->pb_delOferta->setEnabled(false);
        ui->pb_guardar->setEnabled(false);
        ui->pb_insIngrediente->setEnabled(false);
        ui->te_editDescripcion->setEnabled(false);
    }

    ui->pb_insIngrediente->setEnabled(false);
}

form_ofertas::~form_ofertas()
{
    delete ui;
}

void form_ofertas::updateImpuesto(){
    updateAll();
    updateOfertas(ui->le_search->text(), rowSelected);
}

void form_ofertas::updateGanancia(){
    updateAll();
    updateOfertas(ui->le_search->text(), rowSelected);
}

void form_ofertas::updateUnit(QString product){
    ProductService productService;
    storageService StorageService;
    auto p = productService.getProductByName(ui->cb_insProduct->currentText());
    if( p.res == SUCCESS ){
        if( p.data.unitType == SOLIDO )
            ui->sb_insCantidad->setSuffix("g");
        else
            ui->sb_insCantidad->setSuffix("u");
        auto s = StorageService.getStorageById(p.data.id);
        //ui->sb_insCantidad->setMaximum(s.data.amount);
        ui->pb_insIngrediente->setEnabled(true);
    }else{
        ui->sb_insCantidad->setSuffix("");
        //ui->sb_insCantidad->setMaximum(0);
        ui->pb_insIngrediente->setEnabled(false);
    }
    ui->sb_insCantidad->setValue(0);
}

void form_ofertas::updateIngredientes(int id)
{
    ui->tw_ingredientes->clearContents();
    IngredientsService ingredientsService;
    ProductService productService;
    auto ingredients = ingredientsService.getIngredientsByDishId(IngredientsDto(id,0,0));
    ingredientsModel = ingredients.data;
    ui->tw_ingredientes->setRowCount(ingredients.data.size());
    int row = 0;

    foreach (auto i, ingredientsModel) {
        auto pro = productService.getProductByID(ProductDto(i.idProduct,"",0,0));
        QTableWidgetItem *producto = new QTableWidgetItem(pro.data.productName);
        producto->setFlags(flags);
        producto->setTextAlignment(utiles::TextAlign);
        QString unit;
        if( pro.data.unitType == SOLIDO )
            unit = "g";
        else unit = "u";
        QTableWidgetItem *amount = new QTableWidgetItem( QString::number(i.amount, 'f', 2)  + unit);
        amount->setFlags(flags);
        amount->setTextAlignment(utiles::TextAlign);
        ui->tw_ingredientes->setItem(row, 0,producto);
        ui->tw_ingredientes->setItem(row, 1, amount);
        row++;
    }
}

void form_ofertas::updatePrecio(int id)
{
    DishService dishService;
    auto dish = dishService.getDishById(DishDto(id,"","",0));
    ui->sb_editPrecio->setValue(dish.data.price);
}

void form_ofertas::updatePrecioSugerido(int id)
{
    DishService dishService;
    auto dish = dishService.getPrecioSugerido(id);
    ui->l_precioSugerido->setText( "Precio Sugerido: $" + QString::number(dish.data, 'f', 2) );

}

void form_ofertas::updatePrecioProduccion(int id){
    DishService dishService;
    ui->l_precioProduccion->setText( "Precio de Producción: $" + QString::number(dishService.getPrecioProduccion(id).data, 'f', 2)  );
}

void form_ofertas::updateDescripcion(int id)
{
    DishService dishService;
    auto dish = dishService.getDishById(DishDto(id,"","",0));
    ui->te_editDescripcion->setText(dish.data.description);
}

void form_ofertas::updateNombre(int id){
    DishService dishService;
    auto dish = dishService.getDishById(DishDto(id,"","",0));
    ui->le_editaName->setText(dish.data.dishname);
}

bool form_ofertas::sortByName(const infoOfertas &s1, const infoOfertas &s2){
    return s1.dish < s2.dish;
}

bool form_ofertas::sortByPrice(const infoOfertas &s1, const infoOfertas &s2){
    return s1.price < s2.price;
}

bool form_ofertas::sortByGanancia(const infoOfertas &s1, const infoOfertas &s2){
    return s1.ganancia < s2.ganancia;
}

bool form_ofertas::sortBySalen(const infoOfertas &s1, const infoOfertas &s2){
    return s1.dish < s2.dish;
}

vector<infoOfertas> form_ofertas::getOfertasSorted( QList<DishDto> L ){
    QString sortBy = ui->cb_sortBy->currentText();
    DishService dishService;
    vector<infoOfertas>ret;
    vector<int>r;
    int orden = 1;
    if( sortBy == "Precio" )
        orden = 2;
    else if( sortBy == "Ganancia" )
        orden = 3;
    else if( sortBy == "Salen" )
        orden = 4;

    dishModel.clear();
    foreach (auto i, L) {
        infoOfertas v;
        v.orden = orden;
        v.id = i.id;
        v.dish = i.dishname;
        v.price = i.price;
        v.description = i.description;
        v.precioSugerido = dishService.getPrecioSugerido(i.id).data;
        v.ganancia = dishService.getGanancia(i.id).data;
        v.salen = dishService.getSalen(i.id).data;
        ret.push_back(v);

        //dishModel << DishDto(i.id, i.dishname, i.description, i.price);
    }

    sort(ret.begin(), ret.end());

    for( infoOfertas i : ret ){
        dishModel << DishDto(i.id, i.dish, i.description, i.price);
    }
    qDebug() << "sorting";
    /*if( sortBy == "Precio" )
        sort(ret.begin(), ret.end(), sortByPrice);
    else if( sortBy == "Ganancia" )
        sort(ret.begin(), ret.end(), sortByGanancia);
    else if( sortBy == "Salen" )
        sort(ret.begin(), ret.end(), sortBySalen);
    else
        sort(ret.begin(), ret.end(), sortByName);*/
    return ret;
}

void form_ofertas::updateOfertas(QString search, int rowS)
{
    qDebug() << "update ofertas";
    DishService dishService;
    auto res = dishService.getDishBySearch( utiles::searchToRegExp(search) ).data;
    ui->tw_ofertas->clearContents();
    ui->tw_ofertas->setRowCount(res.size());
    int row = 0;

    vector<infoOfertas>O = getOfertasSorted(res);

    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if( !O.size() ){
        ui->pb_delOferta->setEnabled(false);

    }
    for (auto o : O) {
        QTableWidgetItem *dish = new QTableWidgetItem(o.dish);
        dish->setFlags(flags);
        dish->setTextAlignment(utiles::TextAlign);
        QTableWidgetItem *price = new QTableWidgetItem("$" + QString::number(o.price, 'f', 2));
        price->setTextAlignment(utiles::TextAlign);
        price->setFlags(flags);
        QTableWidgetItem *precioSugerido = new QTableWidgetItem( "$" + QString::number(o.precioSugerido, 'f', 2));
        precioSugerido->setTextAlignment(utiles::TextAlign);
        precioSugerido->setFlags(flags);
        QTableWidgetItem *ganancia = new QTableWidgetItem( "$" +  QString::number(o.ganancia, 'f', 2));
        ganancia->setTextAlignment(utiles::TextAlign);
        ganancia->setFlags(flags);
        QString tSalen = "Sin ingredientes";
        if( o.salen != numeric_limits<int>::max() )
            tSalen = QString::number(o.salen);
        QTableWidgetItem *salen = new QTableWidgetItem( tSalen );
        salen->setFlags(flags);
        salen->setTextAlignment(utiles::TextAlign);
        ui->tw_ofertas->setItem(row, 0, dish);
        ui->tw_ofertas->setItem(row, 1, price);
        ui->tw_ofertas->setItem(row, 2, precioSugerido);
        ui->tw_ofertas->setItem(row, 3, ganancia);
        ui->tw_ofertas->setItem(row, 4, salen);

        row++;
    }

    if( rowS >= res.size() )
        rowS = res.size()-1;

    if( res.size() > 0 )
        rowSelected = rowS;
    else rowSelected = -1;
    emit rowChanged();
}

void form_ofertas::limpiar(){
    ui->le_editaName->clear();
    ui->te_editDescripcion->clear();
    ui->tw_ingredientes->clearContents();
    ui->sb_editPrecio->clear();
    ui->l_precioProduccion->clear();
    ui->l_precioSugerido->clear();
}


void form_ofertas::updateAll()
{
    qDebug() << "update All" << rowSelected;
    if( rowSelected == -1 ){
        ui->gb_detalles->setEnabled(false);
        ui->pb_delOferta->setEnabled(false);
        limpiar();
        return;
    }
    ui->pb_delOferta->setEnabled(true);
    ui->gb_detalles->setEnabled(true);
    DishService dishService;
    QString dishName = ui->tw_ofertas->item(rowSelected,0)->text();
    qDebug() << "Platoooo" << dishName;
    //auto dish = dishService.getDishByName(DishDto(0,dishName,"",0));
    auto dish = dishModel.at( rowSelected );
    qDebug() << "Nombre del plato" + dish.dishname;
    updateNombre(dish.id);
    updateIngredientes(dish.id);
    updateDescripcion(dish.id);
    updatePrecio(dish.id);
    updatePrecioProduccion(dish.id);
    updatePrecioSugerido(dish.id);
}

void form_ofertas::selectOferta(int id){
    /*for( int i = 0; i < ui->tw_ofertas->rowCount(); i++ ){
        if( ui->tw_ofertas->item(i, 0)->text() == name ){
            ui->tw_ofertas->item(i, 0)->setSelected(true);
            ui->tw_ofertas->scrollToItem(ui->tw_ofertas->item(i, 0));
            rowSelected = i;
            emit rowChanged();
            return;
        }
    }*/

    for( int i = 0; i < dishModel.size(); i++ ){
        if( dishModel.at(i).id == id ){
            ui->tw_ofertas->item(i, 0)->setSelected(true);
            ui->tw_ofertas->scrollToItem(ui->tw_ofertas->item(i, 0));
            rowSelected = i;
            emit rowChanged();
            return;
        }
    }
}

void form_ofertas::on_pb_addOferta_clicked()
{
    QString dishName = ui->le_insName->text();
    double price = ui->sb_insPrice->value();

    if( dishName == "" ){
        QMessageBox::information(this, "Información", "Nombre de plato no válido", QMessageBox::Ok);
        return;
    }

    DishService dishService;
    auto res = dishService.getDishByName(DishDto(0,dishName,"",0));
    if( res.res == SUCCESS ){
        QMessageBox::information(this, "Información", "Plato existente", QMessageBox::Ok);
        return;
    }

    ui->le_insName->clear();
    ui->sb_insPrice->setValue(0);
    auto dish = dishService.insertDish(DishDto(-1,dishName,"",price)).data;
    ui->le_search->clear();
    updateOfertas(ui->le_search->text());
    //selectOferta( dishName );
    selectOferta( dish.id );
}

void form_ofertas::on_tw_ofertas_clicked(const QModelIndex &index)
{
    rowSelected = index.row();
    emit rowChanged();
}

void form_ofertas::on_le_search_textChanged(const QString &arg1)
{
    updateOfertas(arg1);
}

void form_ofertas::on_pb_insIngrediente_clicked()
{
    DishService dishService;
    ProductService productService;
    IngredientsService ingredientsService;
    QString product = ui->cb_insProduct->currentText();
    double cantidad = ui->sb_insCantidad->value();
    if( !cantidad ){
        QMessageBox::information(this, "Información", "La cantidad no puede ser 0", QMessageBox::Ok);
        return;
    }
    auto pr = productService.getProductByName(product);
    if( pr.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información", "El producto seleccionado no existe",QMessageBox::Ok);
        return;
    }
    QString dishName = ui->tw_ofertas->item(rowSelected,0)->text();
    //auto dish = dishService.getDishByName(DishDto(0,dishName,"",0));
    //auto dish = dishService.getDishById( dishModel.at(rowSelected) );
    auto dish = dishModel.at(rowSelected);
    if( dishService.hasIngredient(dish.id, pr.data.id).data ){
        QMessageBox::information(this, "Información", "El plato ya contiene el producto seleccionado", QMessageBox::Ok);
        return;
    }

    auto newDish = ingredientsService.insertIngredient(IngredientsDto(dish.id, pr.data.id, cantidad )).data;


    ui->sb_insCantidad->setValue(0);
    updateIngredientes(newDish.id);
    updatePrecioProduccion(newDish.id);
    updatePrecioSugerido(newDish.id);
    updateOfertas(ui->le_search->text(), rowSelected);
}

void form_ofertas::on_pb_delIngrediente_clicked()
{
    ProductService productService;
    IngredientsService ingredientsService;
    DishService dishService;
    //QString dishName = ui->tw_ofertas->item(rowSelected,0)->text();
    //auto dish = dishService.getDishByName(DishDto(0,dishName,"",0));
    auto dish = dishModel.at( rowSelected );
    int row = ui->tw_ingredientes->currentRow();
    if( row == -1 ){
        QMessageBox::information(this,"Información","Debe Seleccionar un ingrediente",QMessageBox::Ok);
        return;
    }
    auto productName = ui->tw_ingredientes->item(row,0)->text();
    auto product = productService.getProductByName(productName);

    auto res = QMessageBox::information(this, "Información", "Está seguro que desea eliminar: " + productName,QMessageBox::Ok,QMessageBox::Cancel);
    if( res == QMessageBox::Ok ){
        //ingredientsService.deleteIngredient(IngredientsDto(dish.data.id,product.data.id,0));
        ingredientsService.deleteIngredient( ingredientsModel.at(row) );
    }
    updateIngredientes(dish.id);
    updatePrecioProduccion(dish.id);
    updatePrecioSugerido(dish.id);
    updateOfertas(ui->le_search->text(), rowSelected);
}

void form_ofertas::on_pb_guardar_clicked()
{
    DishService dishService;
    QString dishName = ui->le_editaName->text();
    QString descripcion = ui->te_editDescripcion->toPlainText();
    double precio = ui->sb_editPrecio->value();
    qDebug() << dishName << descripcion << precio;
    QString name = ui->tw_ofertas->item(rowSelected, 0)->text();
    //auto dish = dishService.getDishByName(DishDto(0,name,"",0));
    auto dish = dishModel.at( rowSelected );
    //qDebug() << dish.data.id;
    auto newDish = dishService.updateDish(DishDto(dish.id, dishName, descripcion, precio)).data;
    updateOfertas(ui->le_search->text(),rowSelected);
    updateAll();
}

void form_ofertas::on_cb_sortBy_currentIndexChanged(const QString &arg1)
{
    updateOfertas(ui->le_search->text());
}

void form_ofertas::on_pb_delOferta_clicked()
{
    if( rowSelected == -1 ){
        QMessageBox::information(this, "Información", "Debe seleccionar una oferta", QMessageBox::Ok);
        return;
    }
    DishService dishService;
    QString dishName = ui->tw_ofertas->item(rowSelected,0)->text();
    //auto dish = dishService.getDishByName(DishDto(0, dishName,"", 0));
    auto dish = dishModel.at( rowSelected );
    auto res = QMessageBox::information(this, "Información", "¿Está seguro que desea eliminar la oferta " + dish.dishname + "?", QMessageBox::Ok, QMessageBox::Cancel);
    if( res == QMessageBox::Ok ){
        dishService.deleteDish(dish);
        updateOfertas(ui->le_search->text(), rowSelected);
        if( rowSelected >= 0 && rowSelected < ui->tw_ofertas->rowCount() ){
            qDebug() << "rowSelected" << rowSelected;
            //selectOferta( ui->tw_ofertas->item(rowSelected, 0)->text() );
            selectOferta( dishModel.at(rowSelected).id );
        }
    }
}


void form_ofertas::on_sb_insCantidad_valueChanged(double arg1)
{
    ui->pb_insIngrediente->setEnabled(arg1 > 0);
}
