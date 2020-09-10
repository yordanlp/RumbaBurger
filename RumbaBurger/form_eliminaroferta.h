#ifndef FORM_ELIMINAROFERTA_H
#define FORM_ELIMINAROFERTA_H

#include <QDialog>

namespace Ui {
class form_eliminarOferta;
}

class form_eliminarOferta : public QDialog
{
    Q_OBJECT

public:
    explicit form_eliminarOferta(QWidget *parent = 0);
    ~form_eliminarOferta();

private:
    Ui::form_eliminarOferta *ui;
};

#endif // FORM_ELIMINAROFERTA_H
