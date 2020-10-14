#ifndef FORM_INICIAL_H
#define FORM_INICIAL_H

#include <QMainWindow>

namespace Ui {
class form_inicial;
}

class form_inicial : public QMainWindow
{
    Q_OBJECT

public:
    explicit form_inicial(QWidget *parent = 0);
    ~form_inicial();

private:
    Ui::form_inicial *ui;
};

#endif // FORM_INICIAL_H
