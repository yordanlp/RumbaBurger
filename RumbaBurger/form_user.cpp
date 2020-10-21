#include "form_user.h"
#include "ui_form_user.h"
#include <Services/userservice.h>
#include <QtCore>
#include <QtWidgets>

form_user::form_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_user)
{
    ui->setupUi(this);
    QRegExp expUser ("[A-Za-z0-9ñÑ_]+");
    QRegExpValidator *valUser = new QRegExpValidator(expUser,this);
    ui->le_username->setValidator(valUser);
}

form_user::~form_user()
{
    delete ui;
}

void form_user::on_pb_aceptar_clicked()
{
    QString name = ui->le_nombre->text();
    QString username = ui->le_username->text();
    QString pass = ui->le_pass->text();
    QString confirmpass = ui->le_confirmpass->text();

    UserService userService;
    auto user = userService.getUserByUsername(username);
    if( user.res == SUCCESS ){
        QMessageBox::critical(this, "Error", "Ya existe un usuario con el nombre <strong>" + username + "</strong>", QMessageBox::Ok );
        return;
    }

    if( username == "" ){
        QMessageBox::critical(this, "Error", "El nombre de usuario no puede estar vacío", QMessageBox::Ok );
        return;
    }

    if( pass == "" ){
        QMessageBox::critical(this, "Error", "La contraseña no puede ser vacía", QMessageBox::Ok );
        return;
    }
    if( pass != confirmpass ){
        QMessageBox::critical(this, "Error", "Las contraseña de confirmación no coincide con la principal", QMessageBox::Ok );
        return;
    }

    auto res = QMessageBox::information(this, "Información", "Está seguro que desea añadir al usuario <strong>" + username + "</strong>", QMessageBox::Ok, QMessageBox::Cancel);
    if( res == QMessageBox::Ok ){
        userService.insertUser(UserDto(0, username, pass, name, 1));
        QMessageBox::information(this, "Información", "Usuario creado con éxito", QMessageBox::Ok );
        close();
    }
}



void form_user::on_pb_cancelar_clicked()
{
    close();
}
