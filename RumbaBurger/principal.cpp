#include "principal.h"
#include "ui_principal.h"
#include <QDebug>
#include <QLabel>
#include <QInputDialog>

Principal::Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principal)
{

    QSettings settings("Limitless", "RumbaBurger");
    settings.beginGroup(QString::number(UserService::loggedUser));
    utiles::IMPUESTO = settings.value("ONAT", 10).toDouble()/100.0;
    utiles::GANANCIA = settings.value("Ganancia", 100).toDouble()/100.0;
    utiles::MONEDA = settings.value("Moneda", "CUP").toString();
    utiles::UNIDAD = settings.value("Unidad", "G").toString();
    settings.endGroup();

    ui->setupUi(this);
    mdi = new QMdiArea(this);
    setCentralWidget(mdi);

    formInicial = new form_inicial(this);
    mdi->addSubWindow(formInicial);
    formInicial->showMaximized();

    if( UserService::loggedUser == 0 ){
        qDebug() << UserService::loggedUser;
        ui->menuAjustes->setVisible(false);
        ui->menuPorcientos->setVisible(false);
        ui->actionNuevo_usuario->setVisible(false);
        ui->actionAdministrar->setVisible(false);
    }else{
        ui->menuAjustes->setVisible(true);
        ui->menuPorcientos->setVisible(true);
        ui->actionNuevo_usuario->setVisible(true);
        ui->actionAdministrar->setVisible(true);
    }

}

Principal::~Principal()
{
    delete ui;
}

//insertar producto
void Principal::on_actionInsertar_Producto_triggered()
{
    /*form_Product = new form_product(this);
    form_Product->setModal(true);
    form_Product->show();*/

}

void Principal::on_actionAlmacenes_triggered()
{
    mdi->closeAllSubWindows();
    form_Almacenes = new form_almacenes(this);
    mdi->addSubWindow(form_Almacenes);
    connect(this, SIGNAL(UnitChanged()), form_Almacenes, SLOT(updateUnit()));
    form_Almacenes->showMaximized();
}

void Principal::on_actionOfertas_triggered()
{
    formOfertas = new form_ofertas(this);
    connect(this, SIGNAL(ImpuestoChanged()), formOfertas, SLOT(updateImpuesto()));
    connect(this, SIGNAL(GananciaChnged()), formOfertas, SLOT(updateGanancia()));
    mdi->closeAllSubWindows();
    mdi->addSubWindow(formOfertas);
    formOfertas->showMaximized();
}

void Principal::on_actionInsertar_orden_triggered()
{
    formInsOrden = new form_insertarorden(this);
    formInsOrden->show();
}

void Principal::on_actionMostrarOrden_triggered()
{
    qDebug() << "mostrar ordenes";
    mdi->closeAllSubWindows();
    formOrdenes = new form_ordenes(this);
    mdi->addSubWindow(formOrdenes);
    formOrdenes->showMaximized();
}

void Principal::on_actionOrdenes_triggered()
{
    on_actionMostrarOrden_triggered();

}

void Principal::on_actionGastos_triggered()
{
    qDebug() << "mostrar gastos";
    mdi->closeAllSubWindows();
    formGastos = new form_gastos(this);
    mdi->addSubWindow(formGastos);
    formGastos->showMaximized();
}

void Principal::on_actionEstadisticas_triggered()
{
    qDebug() << "mostrar reportes";
    mdi->closeAllSubWindows();
    formReportes = new form_reportes(this);
    connect(this, SIGNAL(ImpuestoChanged()), formReportes, SLOT(updateImpuesto()));
    mdi->addSubWindow(formReportes);
    formReportes->showMaximized();
}

void Principal::on_actionTransacciones_triggered()
{
    qDebug() << "transacciones";
    mdi->closeAllSubWindows();
    formTransacciones = new form_transacciones(this);
    connect(this, SIGNAL(UnitChanged()), formTransacciones, SLOT(updateUnit()));
    mdi->addSubWindow(formTransacciones);
    formTransacciones->showMaximized();
}

void Principal::on_actionImpuesto_triggered()
{
    double impuesto = QInputDialog::getDouble(this, "Porcentaje de Impuesto ONAT","Impuesto ONAT (%)", utiles::IMPUESTO * 100, 0, 100, 2);
    utiles::IMPUESTO = impuesto / 100.0;
    QSettings settings("Limitless", "RumbaBurger");
    settings.beginGroup(QString::number(UserService::loggedUser));
    settings.setValue("ONAT", impuesto);
    settings.endGroup();
    emit ImpuestoChanged();
}

void Principal::on_actionGanancia_triggered()
{
    double ganancia = QInputDialog::getDouble(this, "Porcentaje de Ganancia","Ganancia (%)", utiles::GANANCIA * 100, 0, 1000000000, 2);
    qDebug() << "GANANCIA" << ganancia;
    utiles::GANANCIA = ganancia / 100.0;
    QSettings settings("Limitless", "RumbaBurger");
    settings.beginGroup(QString::number(UserService::loggedUser));
    settings.setValue("Ganancia", ganancia);
    settings.endGroup();
    emit GananciaChnged();
}

void Principal::on_actionUnidad_triggered()
{
    QStringList L;
    //L << "Gramos" << "Kilogramos" << "Libras";
    L << "Gramos" << "Kilogramos";
    int selected = 0;
    if( utiles::UNIDAD == "Gramos" )
        selected = 0;
    if( utiles::UNIDAD == "Kilogramos" )
        selected = 1;
    /*if( utiles::UNIDAD == "Libras" )
        selected = 2;*/
    QString unidad = QInputDialog::getItem(this,"Unidad de peso", "Unidad de peso", L, selected, false);
    utiles::UNIDAD = unidad;
    QSettings settings("Limitless", "RumbaBurger");
    settings.beginGroup(QString::number(UserService::loggedUser));
    settings.setValue("Unidad", unidad);
    settings.endGroup();
    emit UnitChanged();
}

void Principal::on_actionMoneda_triggered()
{
    QStringList L;
    L << "CUC" << "CUP";
    int selected = 0;
    if( utiles::MONEDA == "CUC" )
        selected = 0;
    else
        selected = 1;
    QString moneda = QInputDialog::getItem(this,"Moneda", "Moneda", L, selected, false, nullptr);
    utiles::MONEDA = moneda;
    QSettings settings("Limitless", "RumbaBurger");
    settings.beginGroup(QString::number(UserService::loggedUser));
    settings.setValue("Moneda", moneda);
    settings.endGroup();
    emit MonedaChanged();
}

void Principal::on_actionNuevo_usuario_triggered()
{
    qDebug() << "nuevo usuario";
    formUser = new form_user(this);
    formUser->setModal(true);
    formUser->show();
}

void Principal::on_actionAdministrar_triggered()
{
    formCambiarPassword = new form_cambiarpassword(this);
    formCambiarPassword->setModal(true);
    formCambiarPassword->show();
}

void Principal::on_actionCerrar_Sesi_n_triggered()
{
    emit done();
    close();
}
