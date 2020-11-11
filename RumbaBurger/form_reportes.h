#ifndef FORM_REPORTES_H
#define FORM_REPORTES_H

#include <QDialog>

namespace Ui {
class form_reportes;
}

struct VentasModel{
    QString dishName;
    int ventas;
    double inversion;
    double ingresos;
    double ganancia;
    double promedioVentas;
    int cobertura;
    int orderBy;
    int maxId;
    VentasModel(){
        dishName = "";
        promedioVentas = ventas = inversion = ingresos = ganancia = cobertura = 0;
        maxId = 0;
        orderBy = 0;
    }
    bool operator<(const VentasModel &o ){
        if( orderBy == 0 ) return dishName < o.dishName;
        if( orderBy == 1 ) return ventas < o.ventas;
        if( orderBy == 2 ) return inversion < o.inversion;
        if( orderBy == 3 ) return ingresos < o.ingresos;
        if( orderBy == 4 ) return ganancia < o.ganancia;
        if( orderBy == 5 ) return promedioVentas < o.promedioVentas;
        return cobertura < o.cobertura;
    }
};

class form_reportes : public QDialog
{
    Q_OBJECT

public:
    explicit form_reportes(QWidget *parent = 0);
    ~form_reportes();
    void updateOrdenes();
    void updateGastos();
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    double Tinversion, Tingresos, Tganancia, Tgastos;
    void updateTotal();
    void updateVentas();
    QVector<VentasModel> ventasModel;
    QVector<VentasModel> getVentasModel(QDate ini, QDate fin);
    void sortVentasModel( QVector<VentasModel>&v );
    void fillVentasTable();

public slots:
    void updateImpuesto();
    void filtrar();
    void updateVentasBySort();


private:
    Ui::form_reportes *ui;
};

#endif // FORM_REPORTES_H
