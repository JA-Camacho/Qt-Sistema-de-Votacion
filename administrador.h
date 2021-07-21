#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <QMainWindow>
#include <QMap>
#include <QString>
#include "resultados.h"

using namespace std;
namespace Ui {
class Administrador;
}

class Administrador : public QMainWindow
{
    Q_OBJECT

public:
    explicit Administrador(QWidget *parent = nullptr);
    ~Administrador();

private slots:
    void on_cmdAcceder_clicked();

private:
    Ui::Administrador *ui;
    QMap<QString, int> map;
};

#endif // ADMINISTRADOR_H
