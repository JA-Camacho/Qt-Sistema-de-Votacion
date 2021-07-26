#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include "administrador.h"
#include "controlador.h"
#include "votacion.h"
#include "votante.h"
#include "certificado.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT
    
public:
    Principal(QWidget *parent = nullptr);
    ~Principal();
    QString cedula() const;

private slots:

    void on_cmdIngresar_clicked();
    void on_actionResultados_triggered();
    
private:
    Ui::Principal *ui;
    QString m_cedula;
    Controlador *m_controlador;
    QQueue <QString> yaVotaron;
    QStack <int> arauz;
    QStack <int> lasso;
    QStack <int> nulo;
    QStack <int> blanco;
    bool validar(QString cedula);
    void llenarPila(int numero);


};
#endif // PRINCIPAL_H
