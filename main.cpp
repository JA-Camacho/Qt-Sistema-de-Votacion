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
    QTranslator traducion;
    // Solicitando al usuario que seleccione un idioma
    QStringList idiomas;
    idiomas << "Kichwa" << "Inglés" << "Español";
    QString idiomaSeleccionado = QInputDialog::getItem(NULL, "Idioma",
                               "Seleccione un idioma",
                               idiomas);
    // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
    if (idiomaSeleccionado == "Kichwa"){
        traducion.load(":/Traducciones/Proyecto_02_qu_EC.qm");
    }else if (idiomaSeleccionado == "Inglés"){
        traducion.load(":/Traducciones/Proyecto_02_en_US.qm");
    }
    // Si es diferente de español, se instala la traducción en TODA la aplicación
    if (idiomaSeleccionado != "Español"){
        a.installTranslator(&traducion);
    }

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
