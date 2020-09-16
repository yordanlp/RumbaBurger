#ifndef FORM_MOVER_H
#define FORM_MOVER_H

#include <QDialog>

namespace Ui {
class form_mover;
}

class form_mover : public QDialog
{
    Q_OBJECT

public:
    explicit form_mover(QWidget *parent = 0);
    ~form_mover();

public slots:
    void updateRadioButtons(QString product);
    void updateExistente();

private:
    Ui::form_mover *ui;

signals:
    done();
private slots:
    void on_pb_accept_clicked();
    void on_pb_cancel_clicked();
};

#endif // FORM_MOVER_H
