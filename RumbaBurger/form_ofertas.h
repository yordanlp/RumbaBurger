#ifndef FORM_OFERTAS_H
#define FORM_OFERTAS_H

#include <QMainWindow>

namespace Ui {
class form_ofertas;
}

class form_ofertas : public QMainWindow
{
    Q_OBJECT

public:
    explicit form_ofertas(QWidget *parent = 0);
    ~form_ofertas();

private:
    Ui::form_ofertas *ui;
};

#endif // FORM_OFERTAS_H
