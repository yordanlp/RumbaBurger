#ifndef FORM_NEWUSER_H
#define FORM_NEWUSER_H

#include <QMainWindow>

namespace Ui {
class form_newUser;
}

class form_newUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit form_newUser(QWidget *parent = 0);
    ~form_newUser();

private slots:
    void on_pb_aceptar_clicked();

private:
    Ui::form_newUser *ui;
};

#endif // FORM_NEWUSER_H
