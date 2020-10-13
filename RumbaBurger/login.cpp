#include "login.h"
#include "ui_login.h"
#include "principal.h"
#include "Services/userservice.h"
#include "result.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setMaximumSize(width(),height());
    setMinimumSize(width(), height());
    connect(ui->cb_invitado, SIGNAL(clicked(bool)), this, SLOT(invitado()));

    //validador de user
    QRegExp expUser ("[A-Za-z0-9ñÑ_]+");
    valUser = new QRegExpValidator(expUser,this);
    ui->user->setValidator(valUser);

    //quitar
    ui->user->setText("admin");
    ui->pass->setText("admin");
}

Login::~Login()
{
    delete ui;
}

void Login::invitado()
{
    int state = ui->cb_invitado->isChecked();
    if( state == 1 ){
        ui->label_2->setEnabled(false);
        ui->label_3->setEnabled(false);
        ui->user->setEnabled(false);
        ui->pass->setEnabled(false);
    }else{
        ui->label_2->setEnabled(true);
        ui->label_3->setEnabled(true);
        ui->user->setEnabled(true);
        ui->pass->setEnabled(true);
    }
}


void Login::on_cancel_clicked()
{
    close();
}

void Login::on_accept_clicked()
{
    if( ui->cb_invitado->isChecked() ){
        UserService::loggedUser = 0;
        Principal *principal = new Principal(this);
        principal->showMaximized();
    }else{
        QString user = ui->user->text();
        QString pass = ui->pass->text();
        UserService userService;
        auto us = userService.getUserByUsername(user);
        if( us.res != SUCCESS ){
            QMessageBox::critical(this,"Error","Usuario o Contraseña incorrectos",QMessageBox::Ok);
            ui->user->setFocus();
            return;
        }

        UserService::loggedUser = us.data.id;
        Principal *principal = new Principal(this);
        principal->showMaximized();
    }
    hide();
}

void Login::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == 16777220 ){
        on_accept_clicked();
    }
}
