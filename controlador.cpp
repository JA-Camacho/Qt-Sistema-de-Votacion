#include "controlador.h"

Controlador::Controlador(QObject *parent) : QObject(parent)
{

}

bool Controlador::siHaVotado(QString cedula)
{
    QFile usuario("Lista de Personas que ya votaron.csv");
    QTextStream io;
    usuario.open(QIODevice::ReadOnly);
    io.setDevice(&usuario);

    while(!io.atEnd())
    {
        auto linea = io.readLine();
        if(linea == cedula)
        {
            return true; //Si ya ha votado
        }
    }
    return false; //No ha votado
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
    QFile usuario("Padron Electoral.csv");
    QTextStream io;
    usuario.open(QIODevice::ReadOnly | QIODevice::Text);
    io.setDevice(&usuario);
    while(!io.atEnd())
    {
        auto linea = io.readLine();
        auto valores =linea.split(";");
        for(int i = 0; i< valores.size(); i++)
        {
            if(valores.at(0) == cedula)
            {
                return valores.at(1); //Retornamos el nombre de la cedula registrada en el Padron Electoral.csv
            }
            else
                break;
        }
    }
    return "\0";
}

void Controlador::guardarVotos(int arauz, int lasso, int nulo, int blanco)
{
    QFile votos("Votos.csv");
    QTextStream io;
    io.setDevice(&votos);
    votos.open(QIODevice::ReadWrite | QIODevice::Text);

    io << "Arauz;" << arauz << endl;
    io << "Lasso;" << lasso << endl;
    io << "Nulo;" << nulo << endl;
    io << "Blanco;" << blanco << endl;
    votos.close();

}

void Controlador::cargarVotos(QStack<int> &arauz, QStack<int> &lasso, QStack<int> &nulo, QStack<int> &blanco)
{
    //Crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::current();
    //Agregar al path absoluto del objeto un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath() + "/Votos.csv";
    QFile votos(pathArchivo);
    QTextStream io;
    io.setDevice(&votos);
    votos.open(QIODevice::ReadWrite | QIODevice::Text);
    if(!votos.isOpen())
    {
        QMessageBox::information(0, tr("Aviso"), tr("Error de Apertura"));
    }
    io.setDevice(&votos);

    while(!io.atEnd())
    {
        auto linea = io.readLine();
        auto valores =linea.split(";");
        int numeroColumnas = valores.size();
        for(int i = 0; i< numeroColumnas; i++)
        {
            if(valores.at(0) == "Arauz")
            {
                arauz.resize(valores.at(1).toInt());
            }
            else if(valores.at(0) == "Lasso")
            {
                lasso.resize(valores.at(1).toInt());
            }
            else if(valores.at(0) == "Nulo")
            {
                nulo.resize(valores.at(1).toInt());
            }
            else
                blanco.resize(valores.at(1).toInt());
        }

    }
}

void Controlador::guardarCedulas(QString cedula)
{
    QFile usuario("Lista de Personas que ya votaron.csv");
    QTextStream io;
    usuario.open(QIODevice::WriteOnly | QIODevice::Append);
    io.setDevice(&usuario);
    io << cedula << endl;
    usuario.close();
}

void Controlador::crearArchivos()
{
    //Se verifica si se tiene los archivos necesarios para que funcione el programa
    QTextStream io;
    //Comprueba si no existe la carpeta certificados para crearla
    if(!QDir("Certificados").exists())
        QDir().mkdir("Certificados");

    //Comprueba si no existe los archivos para crearlos
    if(!QFile("Fecha.csv").exists())
    {
        QFile fecha("Fecha.csv");
        fecha.open(QIODevice::ReadWrite | QIODevice::Text);
        io.setDevice(&fecha);
        io << "Fecha;Hora Inicio;Hora Final" << endl;
        io << QDate::currentDate().toString("dd/MM/yyyy") << ";7:00;23:00";
        fecha.close();
    }

    if(!QFile("Votos.csv").exists())
    {
        QFile votos("Votos.csv");
        io.setDevice(&votos);
        votos.open(QIODevice::ReadWrite | QIODevice::Text);

        io << "Arauz;0" << endl;
        io << "Lasso;0" << endl;
        io << "Nulo;0" << endl;
        io << "Blanco;0" << endl;
        votos.close();
    }

    if(!QFile("Padron Electoral.csv").exists())
    {
        QFile Padron("Padron Electoral.csv");
        io.setDevice(&Padron);
        Padron.open(QIODevice::ReadWrite | QIODevice::Text);
        io << "Cedula;Nombre";
        Padron.close();
    }

    if(!QFile("Lista de Personas que ya votaron.csv").exists())
    {
        QFile Lista("Lista de Personas que ya votaron.csv");
        Lista.open(QIODevice::ReadWrite | QIODevice::Text);
        Lista.close();
    }

}

bool Controlador::padron(QString cedula)
{
    QFile usuario("Padron Electoral.csv");
    QTextStream io;
    usuario.open(QIODevice::ReadOnly | QIODevice::Text);
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
                return true; //Si pertenece al Padron Electoral.csv
            }
            else
                break;
        }
    }
    return false; //No pertenece al Padron Electoral.csv
}
