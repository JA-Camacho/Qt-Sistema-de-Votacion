#include "principal.h"
#include <QApplication>
#include <QDate>
#include <QMessageBox>
#include <QObject>
#include <QDebug>
#define FECHA "21-07-2021"
#define HORAINICIAL "00:00"
#define HORAFINAL "23:59"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Principal w;
    QDate diaElectoral = QDate::fromString(FECHA, "dd-MM-yyyy");
    QTime tiempoElectoralI = QTime::fromString(HORAINICIAL, "hh:mm");
    QTime tiempoElectoralF = QTime::fromString(HORAFINAL, "hh:mm");
    if(diaElectoral == QDate::currentDate())
    {
        if(QTime::currentTime() >= tiempoElectoralI  && QTime::currentTime() <= tiempoElectoralF)
            w.show();
        else
            QMessageBox::warning(&w, "Votaciones", "No es tiempo de Votar!"
                                                   "\nHora Habilitado para sufragar (" HORAINICIAL "-" HORAFINAL ")");
    }
    else
        QMessageBox::warning(&w, "Votaciones", "No Habilitado para votar en esta fecha!"
                                               "\nDía Habilitado para sufragar (" FECHA ")");
    return a.exec();
}
