#ifndef FORM_COMPRA_H
#define FORM_COMPRA_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include <Services/productservice.h>
#include <Dto/centralstoragedto.h>

namespace Ui {
class form_compra;
}

class form_compra : public QDialog
{
    Q_OBJECT

public:
    explicit form_compra(QWidget *parent = 0);
    ~form_compra();

private slots:
    void on_cb_merma_clicked();


    void on_pb_cancelar_clicked();

    void on_pb_aceptar_clicked();

signals:
    done();

private:
    Ui::form_compra *ui;
};

#endif // FORM_COMPRA_H
