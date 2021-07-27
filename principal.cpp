#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    m_cedula = "";
    m_controlador->cargarVotos(arauz, lasso, nulo, blanco);

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
        QMessageBox::warning(this, tr("Principal"), tr("No has proporcionado la cedula"));
        return;
    }
    if(!validar(m_cedula))
        return;
    else
    {
        //Objeto Dinamico votacion y votante
        Votacion *votacion = new Votacion(this);

        Votante *votante = new Votante(m_controlador->enviarNombre(m_cedula), m_cedula);
        votacion->exec();

        this->llenarPila(votacion->voto());
        m_controlador->guardarCedulas(m_cedula);
        m_controlador->guardarVotos(arauz.size(), lasso.size(), nulo.size(), blanco.size());
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
        ui->statusbar->setStyleSheet("color: rgb(255, 48, 48);");//COLOR ROJO
        ui->statusbar->showMessage(tr("La cedula que ha ingresado no es Ecuatoriana"), 5000);//TIEMPO EN MILISEGUNDOS
        return false;//NO PUEDE VOTAR
    }
    else if(!m_controlador->padron(cedula))
    {
        ui->statusbar->setStyleSheet("color: rgb(255, 48, 48);");
        ui->statusbar->showMessage(tr("Usted no pertenece a este Padrón Electoral"), 5000);
        return false;//NO PUEDE VOTAR
    }
    else if(m_controlador->siHaVotado(cedula)){
        QMessageBox::warning(this, tr("Principal"), tr("Usted ya ha votado"));
        ui->inCedula->clear();
        ui->inCedula->setFocus();
        return false;//NO PUEDE VOTAR
    }
    return true;//si puede votar
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
