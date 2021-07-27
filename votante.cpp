#include "votante.h"

QString Votante::cedula() const{
    return m_cedula;
}

void Votante::setCedula(const QString &cedula){
    m_cedula = cedula;
}

QString Votante::nombre() const{
    return m_nombre;
}

void Votante::setNombre(const QString &nombre){
    m_nombre = nombre;
}

Votante::Votante(QObject *parent) : QObject(parent){

}

Votante::Votante(QString nombre, QString cedula){
    m_nombre = nombre;
    m_cedula = cedula;
}
