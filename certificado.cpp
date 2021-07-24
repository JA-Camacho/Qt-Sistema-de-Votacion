#include "certificado.h"
#include "ui_certificado.h"
#include <QDebug>
Certificado::Certificado(QWidget *parent, QString nombre, QString cedula) :
    QDialog(parent),
    ui(new Ui::Certificado)
{
    ui->setupUi(this);
    //Crear el lienzo
    lienzo = QPixmap(350,140);
    //QFile Foto("Foto.jpeg");
    //Invocar al metodo dibujar
    this->dibujar(nombre, cedula);
}

Certificado::~Certificado()
{
    delete ui;
}

void Certificado::dibujar(QString nombre, QString cedula)
{
    QTime tiempo = QTime::currentTime();
    QDate fecha = QDate::currentDate();
    //Rellenar el lienzo de color blanco
    lienzo.fill(Qt::white);

    //Crear el pintor
    QPainter painter(&lienzo);

    int x = 50;
    int y = 50;
    painter.drawImage(x,y, imagen.scaled(100,110));
    painter.setFont(QFont("Arial", 10));

    painter.drawText(x+200, y,"Certificado de Votación");
    painter.drawText(x+250, y+30,"Elecciones 2021");
    painter.drawText(x+200, y+50,"Nombre: " + nombre);
    painter.drawText(x+200, y+70,"Cedula: " + cedula);
    painter.drawText(x+200, y+90,"Fecha: " + tiempo.toString("hh:mm"));
    painter.drawText(x+200, y+110,"Hora: " + fecha.toString("dd-MM-yyyy"));
    ui->outCertificado->setPixmap(lienzo);
}
