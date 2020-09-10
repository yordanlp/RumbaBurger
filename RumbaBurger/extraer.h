#ifndef EXTRAER_H
#define EXTRAER_H

#include <QDialog>

namespace Ui {
class Extraer;
}

class Extraer : public QDialog
{
    Q_OBJECT

public:
    explicit Extraer(QWidget *parent = 0);
    ~Extraer();

private:
    Ui::Extraer *ui;
};

#endif // EXTRAER_H
