#ifndef CERTIFICADO_H
#define CERTIFICADO_H

#include <QDialog>
#include "votante.h"
namespace Ui {
class Certificado;
}

class Certificado : public QDialog
{
    Q_OBJECT

public:
    explicit Certificado(QWidget *parent = nullptr);
    ~Certificado();

    Votante *getVotante() const;
    void setVotante(Votante *value);

private:
    Ui::Certificado *ui;
    Votante *votante;
};

#endif // CERTIFICADO_H
