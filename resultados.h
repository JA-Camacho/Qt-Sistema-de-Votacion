#ifndef RESULTADOS_H
#define RESULTADOS_H

#include <QDialog>
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

namespace Ui {
class Resultados;
}

class Resultados : public QDialog
{
    Q_OBJECT

public:
    explicit Resultados(QWidget *parent = nullptr);
    ~Resultados();

private slots:
    void on_cmdImagen_released();

private:
    Ui::Resultados *ui;
    QPixmap lienzo;
    void dibujar();
    void cargarVotos();
    int m_arauz;
    int m_lasso;
    int m_blanco;
    int m_nulo;
};

#endif // RESULTADOS_H
