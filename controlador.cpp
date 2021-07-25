#include "controlador.h"


Controlador::Controlador(QObject *parent) : QObject(parent)
{

}

/*void Controlador::llenarPila(int numero)
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
}*/

bool Controlador::siHaVotado(QString cedula)
{
    if(!listaVotantes.empty())
    {
        for(int i = 0; i < listaVotantes.length(); i++)
        {
            if(listaVotantes[i] == cedula)
                return true; //Ya voto
        }
        return false; //No ha votado
    }
    else
    {
        return false;
    }
}

bool Controlador::validarCedulaEC(QString cedula)
{
    //Creamos una lista temporal
    QString temp[10];
    int aux;
    int sumaPar = 0;
    int sumaImpar = 0;
    //Recogemos de la cedula los 9 primeros digitos
    for(int i = 0; i < 9; i++)
    {
        //A la lista temporal le vamos ingresando los valores de la cedula uno por uno
        temp[i] = cedula[i];
        //Le damos el valor de la lista temporal, en posicion i, a la variable aux
        aux = temp[i].toInt();
        //Si i + 1 es par
        if((i+1)%2==0)
            //Se aumenta a sumaPar
            sumaPar += aux;
        //Si no
        else
        {
            //Si al multiplicar el aux por 2 rebasa 9
            if(aux * 2 > 9)
                //Aumentaremos a sumaImpar el aux multiplicado por 2 y restado 9
                sumaImpar = sumaImpar + ((aux * 2) - 9);
            //Si no
            else
                //Se aumenta a sumaImpar
                sumaImpar += aux * 2;
        }
    }
    //Se obtiene el ultimo digito de la cedula
    int ultimoCedula = cedula.toInt()%10;
    //Obtenemos el módulo de la suma de los numeros pares e impares
    int verificador = (sumaPar + sumaImpar)%10;
    //Si verificador es diferente de cero
    if(verificador !=0)
        //De 10 se le resta el verificador
        verificador = 10 - verificador;
    return ultimoCedula == verificador? true : false;
}

QString Controlador::enviarNombre(QString cedula)
{
    QFile usuario(":/usuarios/Recursos/usuarios.csv");
    QTextStream io;
    usuario.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!usuario.isOpen())
    {
        QMessageBox::information(0, "Aviso", "Error de Apertura");
    }
    io.setDevice(&usuario);
    while(!io.atEnd())
    {
        auto linea = io.readLine();
        auto valores =linea.split(";");
        for(int i = 0; i< valores.size(); i++)
        {
            if(valores.at(0) == cedula)
            {
                return valores.at(1); //Si pertenece al padron electoral
            }
            else
                break;
        }
    }
}

/*int Controlador::getArauz()
{
    return arauz.size();
}

int Controlador::getLasso()
{
    return lasso.size();
}

int Controlador::getNulo()
{
    return nulo.size();
}

int Controlador::getBlanco()
{
    return blanco.size();
}*/

bool Controlador::padron(QString cedula)
{
    QFile usuario(":/usuarios/Recursos/usuarios.csv");
    QTextStream io;
    usuario.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!usuario.isOpen())
    {
        QMessageBox::information(0, "Aviso", "Error de Apertura");
    }
    io.setDevice(&usuario);

    while(!io.atEnd())
    {
        auto linea = io.readLine();
        auto valores =linea.split(";");
        int numeroColumnas = valores.size();
        for(int i = 0; i< numeroColumnas; i++)
        {
            if(valores.at(0) == cedula)
            {
                return true; //Si pertenece al padron electoral
            }
            else
                break;
        }

    }
    return false; //No pertenece al padron electoral
}
