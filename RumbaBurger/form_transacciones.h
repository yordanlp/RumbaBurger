#ifndef FORM_TRANSACCIONES_H
#define FORM_TRANSACCIONES_H

#include <QMainWindow>

namespace Ui {
class form_transacciones;
}

class form_transacciones : public QMainWindow
{
    Q_OBJECT

public:
    explicit form_transacciones(QWidget *parent = 0);
    ~form_transacciones();

private:
    Ui::form_transacciones *ui;
};

#endif // FORM_TRANSACCIONES_H
