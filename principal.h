#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QStack>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include "votacion.h"
#include "certificado.h"
#include "votante.h"
#include "administrador.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

private slots:

    void on_cmdIngresar_clicked();
    void on_actionResultados_triggered();

private:
    Ui::Principal *ui;
    QStack <int> arauz;
    QStack <int> lasso;
    QStack <int> nulo;
    QStack <int> blanco;
    Votante *votante;
    void llenarPila(int numero);
};
#endif // PRINCIPAL_H
