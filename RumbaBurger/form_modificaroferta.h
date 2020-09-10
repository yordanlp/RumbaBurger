#ifndef FORM_MODIFICAROFERTA_H
#define FORM_MODIFICAROFERTA_H

#include <QDialog>

namespace Ui {
class form_modificarOferta;
}

class form_modificarOferta : public QDialog
{
    Q_OBJECT

public:
    explicit form_modificarOferta(QWidget *parent = 0, QString oferta = "");
    ~form_modificarOferta();
    QString oferta;


private:
    Ui::form_modificarOferta *ui;
};

#endif // FORM_MODIFICAROFERTA_H
