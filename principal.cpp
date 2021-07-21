#include "principal.h"
#include "ui_principal.h"
#include <QDebug>
Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_cmdIngresar_clicked()
{
    //Obtener el nombre
    QString cedula = ui->inCedula->text();
    //valida que el nombre no este vacio
    if(cedula.isEmpty())
    {
        QMessageBox::warning(this, "Principal", "No has proporcionado la cedula");
        return;
    }
    QFile usuario(":/usuarios/Recursos/usuarios.csv");
    QTextStream io;
    usuario.open(QIODevice::ReadOnly | QIODevice::Text);
    io.setDevice(&usuario);
    auto linea = io.readLine();
    auto cedulas =linea.split(";");
    for(int i = 0; i< cedulas.size(); i++)
    {
        if(cedulas.at(i) == cedula)
        {
            this->hide();
            Votacion *votacion = new Votacion(this);
            Certificado *certificado = new Certificado(this);
            Votante *votante = new Votante("Jose", cedulas.at(i));
            votacion->exec();
            llenarPila(votacion->voto());
            certificado->setVotante(votante);
            certificado->exec();
            qDebug()<< "Arauz: " <<arauz.size();
            qDebug()<< "Lasoo: " <<lasso.size();
            qDebug()<< "Nulo: " <<nulo.size();
            qDebug()<< "Blanco: " <<blanco.size();
            this->show();
        }
        else
        {
            ui->outAdvertencia->setText("USTED NO PERTENECE A ESTE PADRON ELECTORAL");
            ui->inCedula->setText("");
            ui->inCedula->setFocus();
        }
    }
}

void Principal::llenarPila(int numero)
{
    switch(numero)
    {
    //Votos nulos
    case 0:
        nulo.append(1);
        break;
    //Votos para arauz
    case 1:
        arauz.append(1);
        break;
    //Votos para lasso
    case 2:
        lasso.append(1);
        break;
    //Votos blancos
    case 3:
        blanco.append(1);
        break;
    }
}

void Principal::on_actionResultados_triggered()
{
    this->hide();
    Administrador *admin = new Administrador();
    admin->show();
}
