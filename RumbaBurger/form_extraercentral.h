#ifndef FORM_EXTRAERCENTRAL_H
#define FORM_EXTRAERCENTRAL_H

#include <QDialog>

namespace Ui {
class form_extraerCentral;
}

class form_extraerCentral : public QDialog
{
    Q_OBJECT

public:
    explicit form_extraerCentral(QWidget *parent = 0);
    ~form_extraerCentral();

public slots:
    void updateRadioButtons( QString product );
    void updateExistente();

signals:
    void done();

private slots:
    void on_pb_cancelar_clicked();

    void on_pb_aceptar_clicked();

private:
    Ui::form_extraerCentral *ui;
};

#endif // FORM_EXTRAERCENTRAL_H
