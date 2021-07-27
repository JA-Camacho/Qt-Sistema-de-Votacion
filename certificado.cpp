#include "certificado.h"
#include "ui_certificado.h"


Certificado::Certificado(QWidget *parent, QString nombre, QString cedula) :
    QDialog(parent),
    ui(new Ui::Certificado)
{
    ui->setupUi(this);
    this->nombre = cedula;
    imagen = QImage(QString("%1.jpeg").arg(cedula));
    //ejemplo: arg(cedula)=1751222454        .jpeg
    //Crear el lienzo
    lienzo = QPixmap(523,200);
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

    painter.drawText(x+200, y,tr("Certificado de Votación"));
    painter.drawText(x+225, y+17,tr("Elecciones 2021"));
    painter.drawText(x+200, y+50,tr("Nombre: ") + nombre);
    painter.drawText(x+200, y+70,tr("Cedula: ") + cedula);
    painter.drawText(x+200, y+90,tr("Fecha: ") + fecha.toString("dd-MM-yyyy"));
    painter.drawText(x+200, y+110,tr("Hora: ") + tiempo.toString("hh:mm"));
    ui->outCertificado->setPixmap(lienzo);
}

void Certificado::on_cmdGuardar_released()
{
    //Crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::current();
    //Agregar al path absoluto del objeto un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath() + tr("/Certificados/");
    lienzo.save(QString(pathArchivo + nombre + ".png"));
    this->close();
}
