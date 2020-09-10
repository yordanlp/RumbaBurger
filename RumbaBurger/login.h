#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    QRegExpValidator *valUser;
    ~Login();

private slots:

    void on_cancel_clicked();

    void on_accept_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
