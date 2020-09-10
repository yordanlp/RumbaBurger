#ifndef FORM_INSERTAROFERTA_H
#define FORM_INSERTAROFERTA_H

#include <QDialog>

namespace Ui {
class form_insertarOferta;
}

class form_insertarOferta : public QDialog
{
    Q_OBJECT

public:
    explicit form_insertarOferta(QWidget *parent = 0);
    ~form_insertarOferta();

private:
    Ui::form_insertarOferta *ui;
};

#endif // FORM_INSERTAROFERTA_H
