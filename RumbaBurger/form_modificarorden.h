#ifndef FORM_MODIFICARORDEN_H
#define FORM_MODIFICARORDEN_H

#include <QMainWindow>
#include <QRegExpValidator>
#include <Services/dishservice.h>
#include <QCompleter>
#include <QMessageBox>
#include <Services/orderservice.h>
#include <Services/orderdishservice.h>

namespace Ui {
class form_modificarorden;
}

class form_modificarorden : public QMainWindow
{
    Q_OBJECT

public:
    explicit form_modificarorden(QWidget *parent = 0, int orderId = -1);
    ~form_modificarorden();
    void updateCosto();
    double getCosto();
    double getProfit();
    QRegExpValidator *valNumber;
    void updateOrder();
    int orderId;
    Qt::ItemFlags flags = Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

signals:
    void done();

public slots:
    void on_pb_add_clicked();

    void on_pb_del_clicked();

    void on_pb_accep_clicked();

    void on_pb_cancel_clicked();
private:
    Ui::form_modificarorden *ui;
};

#endif // FORM_MODIFICARORDEN_H
