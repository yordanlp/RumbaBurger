#ifndef FORM_GETOFERTA_H
#define FORM_GETOFERTA_H

#include <QDialog>

namespace Ui {
class form_getOferta;
}

class form_getOferta : public QDialog
{
    Q_OBJECT

public:
    explicit form_getOferta(QWidget *parent = 0);
    ~form_getOferta();
signals:
    ofertName( QString );
private slots:
    void on_pb_accept_clicked();

private:
    Ui::form_getOferta *ui;
};

#endif // FORM_GETOFERTA_H
