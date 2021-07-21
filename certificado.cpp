#include "certificado.h"
#include "ui_certificado.h"
#include <QDebug>
Certificado::Certificado(QWidget *parent, QString nombre, QString cedula) :
    QDialog(parent),
    ui(new Ui::Certificado)
{
    ui->setupUi(this);
    ui->outNombre->setText(nombre);
    ui->outCedula->setText(cedula);
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    ui->outHora->setText(time.toString("hh:mm:ss"));
    ui->outFecha->setText(date.toString("dd-MM-yyyy"));
}

Certificado::~Certificado()
{
    delete ui;
}
