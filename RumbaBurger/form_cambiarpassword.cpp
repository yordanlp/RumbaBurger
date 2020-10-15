#include "form_cambiarpassword.h"
#include "ui_form_cambiarpassword.h"
#include <Services/userservice.h>
#include <QtCore>
#include <QtWidgets>

form_cambiarpassword::form_cambiarpassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_cambiarpassword)
{
    ui->setupUi(this);
    UserService userService;
    auto user = userService.getUserById(UserService::loggedUser);
    ui->l_usuario->setText("<h1><strong>Usuario: " + user.data.user+"</strong></h1>");
}

form_cambiarpassword::~form_cambiarpassword()
{
    delete ui;
}


void form_cambiarpassword::on_pb_aceptar_clicked()
{
    QString oldPass = ui->le_vieja->text();
    QString newPass = ui->le_nueva->text();
    QString confirmPass = ui->le_confirmar->text();

    UserService userService;
    auto user = userService.getUserById(UserService::loggedUser);
    if( oldPass != user.data.password ){
        QMessageBox::critical(this, "Error", "Contraseña incorrecta", QMessageBox::Ok);
        return;
    }

    if( newPass == "" ){
        QMessageBox::critical(this, "Error", "La contaseña debe contener al menos un símbolo", QMessageBox::Ok);
        return;
    }

    if( newPass != confirmPass ){
        QMessageBox::critical(this, "Error", "Las contraseñas no coinciden", QMessageBox::Ok);
        ui->le_nueva->setFocus();
        return;
    }

    user.data.password = newPass;
    userService.updateUser(user.data);
    QMessageBox::information(this, "Información", "Contraseña cambiada con éxito", QMessageBox::Ok);
    close();
}

void form_cambiarpassword::on_pb_cancelar_clicked()
{
    close();
}
