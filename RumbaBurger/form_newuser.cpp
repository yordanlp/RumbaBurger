#include "form_newuser.h"
#include "ui_form_newuser.h"
#include <Services/userservice.h>
#include <QtCore>
#include <QtWidgets>

form_newUser::form_newUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form_newUser)
{
    ui->setupUi(this);
}

form_newUser::~form_newUser()
{
    delete ui;
}

void form_newUser::on_pb_aceptar_clicked()
{
    QString name = ui->le_nombre->text();
    QString username = ui->le_username->text();
    QString pass = ui->le_pass->text();
    QString confirmpass = ui->le_pass->text();

    UserService userService;
    auto user = userService.getUserByUsername(username);
    if( user.res == SUCCESS ){
        QMessageBox::critical(this, "Error", "Ya existe un usuario con el nombre <strong>" + username + "</strong>", QMessageBox::Ok );
        return;
    }

    if( pass != confirmpass ){
        QMessageBox::critical(this, "Error", "Las contraseña de confirmación no coincide con la principal", QMessageBox::Ok );
        return;
    }

    auto res = QMessageBox::information(this, "Información", "Está seguro que desea añadir al usuario <strong>" + username + "</strong>", QMessageBox::Ok, QMessageBox::Cancel);
    if( res == QMessageBox::Ok ){
        userService.insertUser(UserDto(0, username, pass, name, 1));
        close();
    }
}
