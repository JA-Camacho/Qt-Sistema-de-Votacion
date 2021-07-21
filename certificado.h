#ifndef CERTIFICADO_H
#define CERTIFICADO_H

#include <QDialog>
#include <QDate>
#include "votante.h"
namespace Ui {
class Certificado;
}

class Certificado : public QDialog
{
    Q_OBJECT

public:
    explicit Certificado(QWidget *parent = nullptr, QString nombre = nullptr, QString cedula = nullptr);
    Certificado();
    ~Certificado();

private:
    Ui::Certificado *ui;
};

#endif // CERTIFICADO_H
