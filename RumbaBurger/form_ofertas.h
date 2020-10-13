#ifndef FORM_OFERTAS_H
#define FORM_OFERTAS_H

#include <QMainWindow>
#include <Dto/dishdto.h>
#include <bits/stdc++.h>
#include <Dto/ingredientsdto.h>
#include <Dto/dishdto.h>
using namespace std;


namespace Ui {
class form_ofertas;
}

struct infoOfertas{
    int id;
    QString dish;
    double price;
    double precioSugerido;
    double ganancia;
    int salen;
    int orden;
    bool operator<( const infoOfertas &o )const{
        if( orden == 2 )
            return price < o.price;
        if( orden == 3 )
            return ganancia < o.ganancia;
        if( orden == 4 )
            return salen < o.salen;
        return dish.toLower() < o.dish.toLower();
        //return price < o.price;
    }
};

class form_ofertas : public QMainWindow
{
    Q_OBJECT

public:
    explicit form_ofertas(QWidget *parent = 0);
    ~form_ofertas();
    int rowSelected;
    void updateIngredientes( int id );
    void updatePrecio( int id );
    void updatePrecioSugerido( int id );
    void updatePrecioProduccion( int id );
    void updateDescripcion( int id );
    void updateNombre( int id );
    void updateOfertas(QString search , int rowS = -1);
    void limpiar();
    vector<infoOfertas> getOfertasSorted( QList<DishDto> L );
    bool sortByName( const infoOfertas &s1, const infoOfertas &s2 );
    bool sortByPrice( const infoOfertas &s1, const infoOfertas &s2 );
    bool sortByGanancia( const infoOfertas &s1, const infoOfertas &s2 );
    bool sortBySalen( const infoOfertas &s1, const infoOfertas &s2 );
    void selectOferta(int id );

    QList<IngredientsDto> ingredientsModel;
    QList<DishDto> dishModel;
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;


signals:
    rowChanged();

private slots:
    void updateAll();
    void on_pb_addOferta_clicked();
    void on_tw_ofertas_clicked(const QModelIndex &index);
    void on_le_search_textChanged(const QString &arg1);
    void updateUnit(QString product);

    void on_pb_insIngrediente_clicked();

    void on_pb_delIngrediente_clicked();

    void on_pb_guardar_clicked();

    void on_cb_sortBy_currentIndexChanged(const QString &arg1);

    void on_pb_delOferta_clicked();

private:
    Ui::form_ofertas *ui;
};

#endif // FORM_OFERTAS_H
