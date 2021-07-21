#ifndef VOTACION_H
#define VOTACION_H

#include <QDialog>

namespace Ui {
class Votacion;
}

class Votacion : public QDialog
{
    Q_OBJECT

public:
    explicit Votacion(QWidget *parent = nullptr);
    ~Votacion();
    int voto() const;

private slots:
    void on_cmdVotar_released();

private:
    Ui::Votacion *ui;
    int m_voto;
};

#endif // VOTACION_H
