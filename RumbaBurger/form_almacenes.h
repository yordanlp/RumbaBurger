#ifndef FORM_ALMACENES_H
#define FORM_ALMACENES_H

#include <QMainWindow>
#include <form_product.h>
#include <utiles.h>
#include <form_compra.h>
#include <form_mover.h>

namespace Ui {
class form_almacenes;
}

class form_almacenes : public QMainWindow
{
    Q_OBJECT

public:
    explicit form_almacenes(QWidget *parent = 0);
    ~form_almacenes();
    form_product *formProduct;
    form_compra *formCompra;
    form_mover *formMover;
    void updateCentralTable( QString search );
    void updateLocalTable( QString search );

private slots:
    void on_pb_newProduct_clicked();

    void on_le_Centralsearch_textChanged(const QString &search);

    void on_le_localSearch_textChanged(const QString &arg1);

    void on_pb_compra_clicked();

    void clearCentralMdi();

    void on_pb_moveToLocal_clicked();

private:
    Ui::form_almacenes *ui;
};

#endif // FORM_ALMACENES_H
