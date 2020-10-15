#ifndef FORM_CAMBIARPASSWORD_H
#define FORM_CAMBIARPASSWORD_H

#include <QDialog>

namespace Ui {
class form_cambiarpassword;
}

class form_cambiarpassword : public QDialog
{
    Q_OBJECT

public:
    explicit form_cambiarpassword(QWidget *parent = 0);
    ~form_cambiarpassword();

private slots:
    void on_pb_aceptar_clicked();

    void on_pb_cancelar_clicked();

private:
    Ui::form_cambiarpassword *ui;
};

#endif // FORM_CAMBIARPASSWORD_H
