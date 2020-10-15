#ifndef FORM_USER_H
#define FORM_USER_H

#include <QDialog>

namespace Ui {
class form_user;
}

class form_user : public QDialog
{
    Q_OBJECT

public:
    explicit form_user(QWidget *parent = 0);
    ~form_user();

private slots:
    void on_pb_aceptar_clicked();

    void on_pb_cancelar_clicked();

private:
    Ui::form_user *ui;
};

#endif // FORM_USER_H
