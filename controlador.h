#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>
#include <QStack>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>

class Controlador : public QObject
{
    Q_OBJECT
private:
    /*QStack <int> arauz;
    QStack <int> lasso;
    QStack <int> nulo;
    QStack <int> blanco;*/
    QStringList listaVotantes;

public:
    explicit Controlador(QObject *parent = nullptr);
    void llenarPila(int numero);
    bool siHaVotado(QString cedula);
    bool padron(QString cedula);
    bool validarCedulaEC(QString cedula);
    int getArauz();
    int getLasso();
    int getNulo();
    int getBlanco();


signals:

};

#endif // CONTROLADOR_H
