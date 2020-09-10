#ifndef FORM_EXTRAER_H
#define FORM_EXTRAER_H

#include <QDialog>

namespace Ui {
class form_extraer;
}

class form_extraer : public QDialog
{
    Q_OBJECT

public:
    explicit form_extraer(QWidget *parent = 0);
    ~form_extraer();

private:
    Ui::form_extraer *ui;
};

#endif // FORM_EXTRAER_H
