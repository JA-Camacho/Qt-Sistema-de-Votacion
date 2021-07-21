#include "certificado.h"
#include "ui_certificado.h"

Certificado::Certificado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Certificado)
{
    ui->setupUi(this);
}

Certificado::~Certificado()
{
    delete ui;
}

Votante *Certificado::getVotante() const
{
    return votante;
}

void Certificado::setVotante(Votante *value)
{
    votante = value;
}
