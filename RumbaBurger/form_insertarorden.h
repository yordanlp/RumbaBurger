#ifndef FORM_INSERTARORDEN_H
#define FORM_INSERTARORDEN_H

#include <QDialog>

namespace Ui {
class form_insertarorden;
}

class form_insertarorden : public QDialog
{
    Q_OBJECT

public:
    explicit form_insertarorden(QWidget *parent = 0);
    ~form_insertarorden();

private:
    Ui::form_insertarorden *ui;
};

#endif // FORM_INSERTARORDEN_H
