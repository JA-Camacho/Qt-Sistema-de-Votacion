#include "administrador.h"
#include "ui_administrador.h"

Administrador::Administrador(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Administrador)
{
    ui->setupUi(this);

    map.insert("Jose", 123456);
    map.insert("Joel", 9876);
    map.insert("Gilmar",5473);

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
            Resultados *resultados = new Resultados(this);
            resultados->exec();
            break;
        }
    }
    QMessageBox::warning(this, "Administrador", "Usuario y/o Contraseña Incorrecta", "Aceptar");
}
