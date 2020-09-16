#ifndef FORM_ORDENES_H
#define FORM_ORDENES_H

#include <QDialog>

namespace Ui {
class form_ordenes;
}

class form_ordenes : public QDialog
{
    Q_OBJECT

public:
    explicit form_ordenes(QWidget *parent = 0);
    ~form_ordenes();

private:
    Ui::form_ordenes *ui;
};

#endif // FORM_ORDENES_H
