#ifndef CERTIFICADO_H
#define CERTIFICADO_H

#include <QDir>
#include <QDialog>
#include <QDate>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>

#include "votante.h"
namespace Ui {
class Certificado;
}

class Certificado : public QDialog
{
    Q_OBJECT

public:
    explicit Certificado(QWidget *parent = nullptr, QString nombre = nullptr, QString cedula = nullptr);
    Certificado();
    ~Certificado();

private slots:
    void on_cmdGuardar_released();

private:
    Ui::Certificado *ui;
    QPixmap lienzo;
    QImage imagen;
    QString nombre;
    void dibujar(QString nombre, QString cedula);
};

#endif // CERTIFICADO_H
