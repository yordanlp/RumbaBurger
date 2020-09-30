#ifndef FORM_REPORTES_H
#define FORM_REPORTES_H

#include <QDialog>

namespace Ui {
class form_reportes;
}

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

public slots:
    void filtrar();
private:
    Ui::form_reportes *ui;
};

#endif // FORM_REPORTES_H
