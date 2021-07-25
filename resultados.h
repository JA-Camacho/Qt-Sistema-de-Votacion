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
    explicit Resultados(QWidget *parent = nullptr, int arauz = 0, int lasso = 0, int blanco = 0, int nulo = 0);
    ~Resultados();

private:
    Ui::Resultados *ui;
    QPixmap lienzo;
    void dibujar(int arauz, int lasso, int blanco, int nulo);
};

#endif // RESULTADOS_H
