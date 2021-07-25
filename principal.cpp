#include "principal.h"
#include "ui_principal.h"
#include <QDebug>
Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    m_cedula = "";
}

Principal::~Principal()
{
    delete ui;
}
void Principal::on_cmdIngresar_clicked()
{
    //Obtener la cedula
    m_cedula = ui->inCedula->text();
    //valida que el nombre no este vacio
    if(m_cedula.isEmpty())
    {
        QMessageBox::warning(this, "Principal", "No has proporcionado la cedula");
        return;
    }
    if(!validar(m_cedula))
        return;
    else
    {

        Votacion *votacion = new Votacion(this);
        Votante *votante = new Votante(m_controlador->enviarNombre(m_cedula), m_cedula);
        votacion->exec();

        this->llenarPila(votacion->voto());

        Certificado *certificado = new Certificado(this, votante->nombre(), votante->cedula());
        certificado->exec();
        ui->inCedula->clear();
        ui->inCedula->setFocus();
    }
}

void Principal::on_actionResultados_triggered()
{
    this->hide();
    Administrador *admin = new Administrador(this);
    admin->show();
}

bool Principal::validar(QString cedula)
{
    if(!m_controlador->validarCedulaEC(cedula))
    {
        ui->statusbar->setStyleSheet("color: rgb(255, 48, 48);");
        ui->statusbar->showMessage(tr("La cedula que ha ingresado no es Ecuatoriana"), 5000);
        return false;
    }
    else if(!m_controlador->padron(cedula))
    {
        ui->statusbar->setStyleSheet("color: rgb(255, 48, 48);");
        ui->statusbar->showMessage(tr("Usted no pertenece a este Padrón Electoral"), 5000);
        return false;
    }
    /*else if(m_controlador->siHaVotado(cedula))
    {
        QMessageBox::warning(this, "Principal", "Usted ya ha votado");
        return false;
    }*/
    return true;
}

QString Principal::cedula() const
{
    return m_cedula;
}

void Principal::llenarPila(int numero)
{
    switch(numero)
    {
    //Votos blanco
    case 0:
        blanco.append(1);
        break;
        //Votos para arauz
    case 1:
        arauz.append(1);
        break;
        //Votos para lasso
    case 2:
        lasso.append(1);
        break;
        //Votos nulos
    case 3:
        nulo.append(1);
        break;
    }
}
