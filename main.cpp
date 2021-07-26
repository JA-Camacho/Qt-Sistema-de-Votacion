#include "principal.h"
#include <QApplication>
#include <QDate>
#include <QMessageBox>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile fechas("Fecha.csv");
    QTextStream io;
    io.setDevice(&fechas);
    fechas.open(QIODevice::ReadWrite | QIODevice::Text);
    auto linea = io.readLine();
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
