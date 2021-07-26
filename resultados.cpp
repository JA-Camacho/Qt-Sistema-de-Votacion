#include "resultados.h"
#include "ui_resultados.h"

Resultados::Resultados(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resultados)
{
    ui->setupUi(this);

    //Cargar los votos del archivo
    this->cargarVotos();

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
    int alto_1 = m_arauz;
    int alto_2 = m_lasso;
    int alto_3 = m_blanco;
    int alto_4 = m_nulo;

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
    painter.drawText(x, (400 - alto_1) + 17, "Arauz");
    painter.drawText(x, (400 - alto_1), "Lista 1");

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
    painter.drawText(x + 150, (400 - alto_2), "Lista 21");
    painter.drawText(x + 150, (400 - alto_2) + 17, "Lasso");


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
    painter.drawText(x + 300, (400-alto_3) + 17, "Nulo");


    //Dibujar cuarta barra
    QColor colorRelleno4(110,250,125);
    QColor colorBorde4(100,100,100);
    pincel.setColor(colorBorde4);
    painter.setPen(pincel);
    painter.setBrush(colorRelleno4);
    painter.drawRect(x+450, y+(400-alto_4), ancho, alto_4);

    painter.setPen(Qt::black);
    painter.drawText(x+450, (400-alto_4) + 17, "Blanco");

    //Mostrar el lienzo en el cuadro
    ui->outResultados->setPixmap(lienzo);
}

void Resultados::cargarVotos()
{
    QFile votos("Votos.csv");
    QTextStream io;
    io.setDevice(&votos);
    votos.open(QIODevice::ReadOnly);
    io.setDevice(&votos);
    while(!io.atEnd())
    {
        auto linea = io.readLine();
        auto valores =linea.split(";");
        int numeroColumnas = valores.size();
        for(int i = 0; i< numeroColumnas; i++)
        {
            if(valores.at(0) == "Arauz")
            {
                m_arauz = (valores.at(1).toInt());
            }
            else if(valores.at(0) == "Lasso")
            {
                m_lasso = (valores.at(1).toInt());
            }
            else if(valores.at(0) == "Nulo")
            {
                m_nulo = (valores.at(1).toInt());
            }
            else
                m_blanco = (valores.at(1).toInt());
        }

    }
}


void Resultados::on_cmdImagen_released()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imagenes (*.png)");
    if (!nombreArchivo.isEmpty()){
        if (lienzo.save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}
