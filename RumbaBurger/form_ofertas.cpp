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
    //connect(ui->cb_product, SIGNAL(currentTextChanged(QString)), this, SLOT(updateUnit(QString)));
}

form_ofertas::~form_ofertas()
{
    delete ui;
}

void form_ofertas::updateIngredientes(int id)
{
    ui->tw_ingredientes->clearContents();
    IngredientsService ingredientsService;
    ProductService productService;
    auto ingredients = ingredientsService.getIngredientsByDishId(IngredientsDto(id,0,0));
    ui->tw_ingredientes->setRowCount(ingredients.data.size());
    int row = 0;
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    foreach (auto i, ingredients.data) {
        auto pro = productService.getProductByID(ProductDto(i.idProduct,"",0,0));
        QTableWidgetItem *producto = new QTableWidgetItem(pro.data.productName);
        producto->setFlags(flags);
        QTableWidgetItem *amount = new QTableWidgetItem( QString::number(i.amount) );
        amount->setFlags(flags);
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
    ui->l_precioSugerido->setText( "Precio Sugerido: " + QString::number(dish.data) );

}

void form_ofertas::updatePrecioProduccion(int id){
    DishService dishService;
    ui->l_precioProduccion->setText( "Precio de Producción: " + QString::number(dishService.getPrecioProduccion(id).data)  );
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

    foreach (auto i, L) {
        infoOfertas v;
        v.orden = orden;
        v.id = i.id;
        v.dish = i.dishname;
        v.price = i.price;
        v.precioSugerido = dishService.getPrecioSugerido(i.id).data;
        v.ganancia = dishService.getGanancia(i.id).data;
        v.salen = dishService.getSalen(i.id).data;
        ret.push_back(v);
    }

    sort(ret.begin(), ret.end());
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
    for (auto o : O) {
        QTableWidgetItem *dish = new QTableWidgetItem(o.dish);
        dish->setFlags(flags);
        QTableWidgetItem *price = new QTableWidgetItem("$" + QString::number(o.price));
        price->setFlags(flags);
        QTableWidgetItem *precioSugerido = new QTableWidgetItem( "$" + QString::number(o.precioSugerido));
        precioSugerido->setFlags(flags);
        QTableWidgetItem *ganancia = new QTableWidgetItem( "$" +  QString::number(o.ganancia));
        ganancia->setFlags(flags);
        QString tSalen = "Sin ingredientes";
        if( o.salen != numeric_limits<int>::max() )
            tSalen = QString::number(o.salen);
        QTableWidgetItem *salen = new QTableWidgetItem( tSalen );
        salen->setFlags(flags);

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
        limpiar();
        return;
    }
    ui->gb_detalles->setEnabled(true);
    DishService dishService;
    QString dishName = ui->tw_ofertas->item(rowSelected,0)->text();
    qDebug() << "Platoooo" << dishName;
    auto dish = dishService.getDishByName(DishDto(0,dishName,"",0));
    qDebug() << "Nombre del plato" + dish.data.dishname;
    updateNombre(dish.data.id);
    updateIngredientes(dish.data.id);
    updateDescripcion(dish.data.id);
    updatePrecio(dish.data.id);
    updatePrecioProduccion(dish.data.id);
    updatePrecioSugerido(dish.data.id);
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

    dishService.insertDish(DishDto(-1,dishName,"",price));
    ui->le_search->setText(dishName);
    updateOfertas(ui->le_search->text());
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
    auto pr = productService.getProductByName(product);
    if( pr.res == RECORD_NOT_FOUND ){
        QMessageBox::information(this,"Información", "El producto seleccionado no existe",QMessageBox::Ok);
        return;
    }
    QString dishName = ui->tw_ofertas->item(rowSelected,0)->text();
    auto dish = dishService.getDishByName(DishDto(0,dishName,"",0));
    if( dishService.hasIngredient(dish.data.id, pr.data.id).data ){
        QMessageBox::information(this, "Información", "El plato ya contiene el producto seleccionado", QMessageBox::Ok);
        return;
    }

    auto newDish = ingredientsService.insertIngredient(IngredientsDto(dish.data.id, pr.data.id, cantidad )).data;


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
    QString dishName = ui->tw_ofertas->item(rowSelected,0)->text();
    auto dish = dishService.getDishByName(DishDto(0,dishName,"",0));
    int row = ui->tw_ingredientes->currentRow();
    if( row == -1 ){
        QMessageBox::information(this,"Información","Debe Seleccionar un ingrediente",QMessageBox::Ok);
        return;
    }
    auto productName = ui->tw_ingredientes->item(row,0)->text();
    auto product = productService.getProductByName(productName);
    auto res = QMessageBox::information(this, "Información", "Está seguro que desea eliminar: " + productName,QMessageBox::Ok,QMessageBox::Cancel);
    if( res == QMessageBox::Ok ){
        ingredientsService.deleteIngredient(IngredientsDto(dish.data.id,product.data.id,0));
    }
    updateIngredientes(dish.data.id);
    updatePrecioProduccion(dish.data.id);
    updatePrecioSugerido(dish.data.id);
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
    auto dish = dishService.getDishByName(DishDto(0,name,"",0));
    qDebug() << dish.data.id;
    auto newDish = dishService.updateDish(DishDto(dish.data.id, dishName, descripcion, precio)).data;
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
    auto dish = dishService.getDishByName(DishDto(0, dishName,"", 0));
    dishService.deleteDish(dish.data);
    updateOfertas(ui->le_search->text(), rowSelected);
}
