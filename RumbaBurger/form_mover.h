#ifndef FORM_MOVER_H
#define FORM_MOVER_H

#include <QDialog>

namespace Ui {
class form_mover;
}

class form_mover : public QDialog
{
    Q_OBJECT

public:
    explicit form_mover(QWidget *parent = 0);
    ~form_mover();

private:
    Ui::form_mover *ui;
};

#endif // FORM_MOVER_H
