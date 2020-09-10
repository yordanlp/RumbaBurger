#ifndef FORM_PRODUCT_H
#define FORM_PRODUCT_H

#include <QDialog>

namespace Ui {
class form_product;
}

class form_product : public QDialog
{
    Q_OBJECT

public:
    explicit form_product(QWidget *parent = 0);
    ~form_product();

private slots:

    void on_pb_accept_clicked();

    void on_pb_cancel_clicked();

signals:
    done();

private:
    Ui::form_product *ui;
};

#endif // FORM_PRODUCT_H
