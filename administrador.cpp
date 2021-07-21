#include "administrador.h"
#include "ui_administrador.h"
#include <QtDebug>
Administrador::Administrador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Administrador)
{
    ui->setupUi(this);
    map["Jose"] = 123456;
    map["Steven"] = 9876;
}

Administrador::~Administrador()
{
    delete ui;
}

void Administrador::on_cmdAcceder_clicked()
{
    foreach (int value, map)

        if(QString::number(value) == ui->inContrasena->text())
        {
            qDebug() << "Permitido";
            break;
        }
        else
        {
            qDebug() << "No es un usuario";
            break;
        }
}
