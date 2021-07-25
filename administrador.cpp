#include "administrador.h"
#include "ui_administrador.h"
#include <QtDebug>
Administrador::Administrador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Administrador)
{
    ui->setupUi(this);

    map.insert("Jose", 123456);
    map.insert("Joel", 9876);

}

Administrador::~Administrador()
{
    delete ui;
}

void Administrador::on_cmdAcceder_clicked()
{
    QMapIterator<QString, int> i(map);
    while (i.hasNext())
    {
        i.next();
        if(i.key() == ui->inUsuario->text() && QString::number(i.value()) == ui->inContrasena->text())
        {
            Resultados *resultados = new Resultados(0,100,300,400,200);
            resultados->exec();
            break;
        }
    }
    QMessageBox::warning(this, "Administrador", "Usuario y/o Contraseña Incorrecta", "Chido");
}
