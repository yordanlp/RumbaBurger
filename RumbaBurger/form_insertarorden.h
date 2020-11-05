#ifndef FORM_INSERTARORDEN_H
#define FORM_INSERTARORDEN_H

#include <QDialog>
#include <QRegExpValidator>

namespace Ui {
class form_insertarorden;
}

class form_insertarorden : public QDialog
{
    Q_OBJECT

public:
    explicit form_insertarorden(QWidget *parent = 0);
    ~form_insertarorden();
    void updateCosto();
    double getCosto();
    double getProfit(double precioDeVenta, double inversion);
    double getInversion();
    QRegExpValidator *valNumber;

private slots:
    void on_pb_add_clicked();

    void on_pb_del_clicked();

    void on_pb_accep_clicked();

    void on_pb_cancel_clicked();


    void on_sb_cantidad_valueChanged(double arg1);

    void on_tw_platos_cellClicked(int row, int column);


    void on_cb_plato_currentTextChanged(const QString &arg1);

private:
    Ui::form_insertarorden *ui;
};

#endif // FORM_INSERTARORDEN_H
