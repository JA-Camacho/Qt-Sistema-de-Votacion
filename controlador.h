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

public:
    explicit Controlador(QObject *parent = nullptr);
    bool siHaVotado(QString cedula);
    bool padron(QString cedula);
    bool validarCedulaEC(QString cedula);
    QString enviarNombre(QString cedula);
    void guardarVotos(int arauz, int lasso, int nulo, int blanco);
    void cargarVotos(QStack<int> &arauz, QStack<int> &lasso, QStack<int> &nulo, QStack<int> &blanco);
    void guardarCedulas(QString cedula);

signals:

};

#endif // CONTROLADOR_H
