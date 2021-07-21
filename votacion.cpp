#include "votacion.h"
#include "ui_votacion.h"

Votacion::Votacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Votacion)
{
    ui->setupUi(this);
    m_voto = 0; //Voto en blanco
}

Votacion::~Votacion()
{
    delete ui;
}


int Votacion::voto() const
{
    return m_voto;
}

void Votacion::on_cmdVotar_released()
{
    if(ui->inArauz->isChecked() && !ui->inLasso->isChecked())
        m_voto = 1; //Voto por arauz
    else if(!ui->inArauz->isChecked() && ui->inLasso->isChecked())
        m_voto = 2; //Voto por lasso
    else if(ui->inArauz->isChecked() && ui->inLasso->isChecked())
        m_voto = 3; //Voto nulo
    this->close();
}
