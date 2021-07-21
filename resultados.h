#ifndef RESULTADOS_H
#define RESULTADOS_H

#include <QDialog>
#include <QPainter>
namespace Ui {
class Resultados;
}

class Resultados : public QDialog
{
    Q_OBJECT

public:
    explicit Resultados(QWidget *parent = nullptr);
    ~Resultados();

private:
    Ui::Resultados *ui;
    QPixmap lienzo;
    void dibujar();
};

#endif // RESULTADOS_H
