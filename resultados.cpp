#include "resultados.h"
#include "ui_resultados.h"

Resultados::Resultados(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resultados)
{
    ui->setupUi(this);

    //Crear el lienzo
    lienzo = QPixmap(660,500);

    //Invocar al metodo dibujar
    this->dibujar();
}

Resultados::~Resultados()
{
    delete ui;
}

void Resultados::dibujar()
{
    //Rellenar el lienzo de color blanco
    lienzo.fill(Qt::white);
    //Crear el pintor
    QPainter painter(&lienzo);

    int x = 50;
    int y = 50;
    int ancho = 100;
    int alto_1 = 50;
    int alto_2 = 20;
    int alto_3 = 50;
    int alto_4 = 100;

    //Crear el pincel para el borde
    QPen pincel;
    pincel.setWidth(5);
    pincel.setColor(Qt::red);
    pincel.setJoinStyle(Qt::MiterJoin);

    //Establecer el pincel al pintor
    painter.setPen(pincel);

    //Dibujar la primera barra
    painter.drawRect(x, y+(400-alto_1), ancho, alto_1);

    painter.setFont(QFont("Arial", 10));

    painter.setPen(Qt::black);
    painter.drawText(x, (400 - alto_1), "Arauz");

    //Crear un nuevo color
    QColor colorBorde2(78,3,48);
    QColor colorRelleno2(190,120,162);

    //Establecer el nuevo color al pincel
    pincel.setColor(colorBorde2);

    //Volver a establecer el pincel al objeto painter
    painter.setPen(pincel);

    //Establecer el color de la brocha del objeto painter
    painter.setBrush(colorRelleno2);

    //Dibujar la segunda barra
    painter.drawRect(x+150, y+(400-alto_2), ancho, alto_2);

    painter.setPen(Qt::black);
    painter.drawText(x + 150, (400 - alto_2), "Lasso");

    //Creando los colores de la tercera barra
    QColor colorRelleno3(253,253,115);
    QColor colorBorde3(174,174,51);

    //Establecer nuevo color al pincel
    pincel.setColor(colorBorde3);
    //Establecer el pincel y la brocha al painter
    painter.setPen(pincel);
    painter.setBrush(colorRelleno3);
    //Dibujar la tercera barra
    painter.drawRect(x+300, y+(400-alto_3), ancho, alto_3);

    painter.setPen(Qt::black);
    painter.drawText(x + 300, (400-alto_3), "Nulo");

    //Dibujar cuarta barra
    QColor colorRelleno4(110,250,125);
    QColor colorBorde4(100,100,100);
    pincel.setColor(colorBorde4);
    painter.setPen(pincel);
    painter.setBrush(colorRelleno4);
    painter.drawRect(x+450, y+(400-alto_4), ancho, alto_4);

    painter.setPen(Qt::black);
    painter.drawText(x+450, (400-alto_4), "Blanco");

    //Mostrar el lienzo en el cuadro
    ui->outResultados->setPixmap(lienzo);
}

