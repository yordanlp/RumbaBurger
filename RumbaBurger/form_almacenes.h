#ifndef FORM_ALMACENES_H
#define FORM_ALMACENES_H

#include <QMainWindow>
//#include <form_product.h>
#include <utiles.h>
//#include <form_compra.h>
//#include <form_mover.h>
//#include <form_extraercentral.h>
#include <Dto/centralstoragedto.h>
#include <Dto/storagedto.h>
#include <utiles.h>
namespace Ui {
class form_almacenes;
}

class form_almacenes : public QMainWindow
{
    Q_OBJECT

public:
    explicit form_almacenes(QWidget *parent = 0);
    ~form_almacenes();
    //form_product *formProduct;
    //form_compra *formCompra;
    //form_mover *formMover;
    //form_extraerCentral *formExtraerCentral;
    void updateCentralTable( QString search );
    void updateLocalTable( QString search );
    void updateProducts();
    void updateExistentes();

    weigth PESO;
    void setUnit();

    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;


private slots:

    void updateUnit();
    void updateSuffixCompra();
    void updateRadioButtonsExtraer( QString product );
    void updateRadioButtonsExtraerLocal( QString product );
    void updateExistenteExtraer();
    void updateExistenteExtraerLocal();

    void updateRadioButtonsCompra( QString product );

    void on_le_Centralsearch_textChanged(const QString &search);

    void on_le_localSearch_textChanged(const QString &arg1);

    void updateMCExistente();

    void updateExistenteMoverAlLocal();

    void updateMCRadioButtons(QString product);

    void updateRadioButtonsMoverAlLocal( QString product );

    void on_pb_mcAccept_clicked();

    void on_cb_mermaCompra_clicked();

    void on_pb_insertarCompra_clicked();

    void on_pb_acceptInsertar_clicked();

    void on_pb_MoverAlLocal_clicked();

    void on_pb_aceptarExtraer_clicked();

    void on_pb_eliminarProduct_clicked();

    void on_centralTable_cellClicked(int row, int column);

    void on_pb_aceptarExtraerLocal_clicked();

private:
    Ui::form_almacenes *ui;
};

#endif // FORM_ALMACENES_H
