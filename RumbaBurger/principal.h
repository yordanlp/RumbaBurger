#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QMdiArea>

namespace Ui {
class Principal;
}

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);
    ~Principal();
    QMdiArea *mdi;

private:
    Ui::Principal *ui;
};

#endif // PRINCIPAL_H
