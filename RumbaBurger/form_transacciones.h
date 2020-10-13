#ifndef FORM_TRANSACCIONES_H
#define FORM_TRANSACCIONES_H

#include <QMainWindow>
#include <Dto/centralstoragetransactiondto.h>
#include <Dto/transactiondto.h>
#include <Services/transactionservice.h>
#include <utiles.h>

namespace Ui {
class form_transacciones;
}

class form_transacciones : public QMainWindow
{
    Q_OBJECT

public:
    explicit form_transacciones(QWidget *parent = 0);
    ~form_transacciones();
    QList<TransactionDto> Movimientos, Operaciones;
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    weigth PESO;
    void setUnit();

private:
    Ui::form_transacciones *ui;

public slots:
    void filtrarMovimientos();
    void filtrarOperaciones();
    void updateUnit();
private slots:
    void on_pb_deshacerMovimientos_clicked();
    void on_tw_moviemientos_cellClicked(int row, int column);
    void on_tw_CompraExtraccion_cellClicked(int row, int column);
    void on_pb_deshacerCompraExtraccion_clicked();
};

#endif // FORM_TRANSACCIONES_H
