#ifndef VOTANTE_H
#define VOTANTE_H

#include <QObject>

class Votante : public QObject
{
    Q_OBJECT
private:
    QString m_cedula;
    QString m_nombre;
public:
    explicit Votante(QObject *parent = nullptr);
    Votante(QString nombre, QString cedula);
    QString cedula() const;
    void setCedula(const QString &cedula);

    QString nombre() const;
    void setNombre(const QString &nombre);

signals:

};

#endif // VOTANTE_H
