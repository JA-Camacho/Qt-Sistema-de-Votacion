#include "principal.h"
#include <QApplication>
#include <QDate>
#include <QMessageBox>
#include <QObject>
#include <QTranslator>
#include <QInputDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Crea un objeto para manejar las traducciones
    QTranslator traduccion;

    QString lenguajeLocal = QLocale::system().name();

    QStringList lenguaje = lenguajeLocal.split("_");

    //Evaluar el idioma por defecto de la computadora
    if(lenguaje.at(0) == "qu")
    {
        traduccion.load(":/Traducciones/Proyecto_02_qu_EC.qm");
    }
    else if(lenguaje.at(0) == "en"){
        traduccion.load(":/Traducciones/Proyecto_02_en_US.qm");
    }
    else
        traduccion.load(":/Traducciones/Traducciones/Salario_es_EC.qm");

    //Establecer un idioma a la aplicación
    a.installTranslator(&traduccion);

    QFile fechas("Fecha.csv");
    QTextStream io;
    io.setDevice(&fechas);
    fechas.open(QIODevice::ReadOnly);
    //Linea donde va el nombre de cada cosa
    auto linea = io.readLine();
    //Linea donde van fecha;hora inicial,hora final separados por ;
    auto linea2 = io.readLine();
    auto valores =linea2.split(";");
    Principal w;
    QDate diaElectoral = QDate::fromString(valores.at(0), "d/M/yyyy");
    QTime tiempoElectoralI = QTime::fromString(valores.at(1), "h:mm");
    QTime tiempoElectoralF = QTime::fromString(valores.at(2), "h:mm");
    if(diaElectoral == QDate::currentDate())
    {
        if(QTime::currentTime() >= tiempoElectoralI  && QTime::currentTime() <= tiempoElectoralF)
            w.show();
        else
        {
            QMessageBox::warning(NULL, "Votaciones",
                                 QString("No es tiempo de Votar!"
                                         "\nHora Habilitado para sufragar %1-%2").arg(valores.at(1)).arg(valores.at(2)));
        return 0;
        }
    }
    else
    {
        QMessageBox::warning(NULL, "Votaciones", QString("No Habilitado para votar en esta fecha!"
                                               "\nDía Habilitado para sufragar (%1)").arg(valores.at(0)));
        return 0;
    }
    return a.exec();
}
