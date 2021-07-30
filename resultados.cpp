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
    QPainter picasso(&lienzo);

    int x = 50;
    int y = 50;
    int ancho = 100;

    m_total = m_arauz+m_lasso+m_blanco+m_nulo;
    //PORCENTAJE
    porArauz=(m_arauz*100)/m_total;
    porLasso=(m_lasso*100)/m_total;
    porNulo=(m_nulo*100)/m_total;
    porBlanco=(m_blanco*100)/m_total;

    //Obtener el alto a partir del procentaje
    float alto_1 = porArauz*380/100;
    float alto_2 = porLasso*380/100;
    float alto_3 = porNulo*380/100;
    float alto_4 = porBlanco*380/100;


    //Crear el pincel para el borde
    QPen pincel;
    pincel.setWidth(5);
    pincel.setColor(Qt::red);
    QColor colorRelleno1(255, 120, 108);
    pincel.setJoinStyle(Qt::MiterJoin);

    //Establecer el pincel al pintor
    picasso.setPen(pincel);

    //Dibujar la primera barra
    picasso.drawRect(x, y+(400-alto_1), ancho, alto_1);

    picasso.setFont(QFont("Arial", 10));

    picasso.setPen(Qt::black);
    picasso.drawText(x, (400 - alto_1) + 17, "Arauz");
    picasso.drawText(x, (400 - alto_1), tr("Lista 1"));
    picasso.drawText(x, (400 - alto_1)+34,QString::number(porArauz,'f',2)+" %");

    //Crear un nuevo color
    QColor colorBorde2(78,3,48);
    QColor colorRelleno2(190,120,162);

    //Establecer el nuevo color al pincel
    pincel.setColor(colorBorde2);

    //Volver a establecer el pincel al objeto painter
    picasso.setPen(pincel);

    //Establecer el color de la brocha del objeto painter
    picasso.setBrush(colorRelleno2);

    //Dibujar la segunda barra
    picasso.drawRect(x+150, y+(400-alto_2), ancho, alto_2);

    picasso.setPen(Qt::black);
    picasso.drawText(x + 150, (400 - alto_2), tr("Lista 21"));
    picasso.drawText(x + 150, (400 - alto_2) + 17, "Lasso");
    picasso.drawText(x + 150, (400 - alto_2) + 34,QString::number(porLasso,'f',2)+" %");


    //Creando los colores de la tercera barra
    QColor colorRelleno3(253,253,115);
    QColor colorBorde3(174,174,51);

    //Establecer nuevo color al pincel
    pincel.setColor(colorBorde3);
    //Establecer el pincel y la brocha al painter
    picasso.setPen(pincel);
    picasso.setBrush(colorRelleno3);
    //Dibujar la tercera barra
    picasso.drawRect(x+300, y+(400-alto_3), ancho, alto_3);

    picasso.setPen(Qt::black);
    picasso.drawText(x + 300, (400-alto_3) + 17, tr("Nulo"));
    picasso.drawText(x + 300, (400-alto_3) + 34,QString::number(porNulo,'f',2)+" %");

    //Dibujar cuarta barra
    QColor colorRelleno4(110,250,125);
    QColor colorBorde4(100,100,100);
    pincel.setColor(colorBorde4);
    picasso.setPen(pincel);
    picasso.setBrush(colorRelleno4);
    picasso.drawRect(x+450, y+(400-alto_4), ancho, alto_4);

    picasso.setPen(Qt::black);
    picasso.drawText(x+450, (400-alto_4) + 17, tr("Blanco"));
    picasso.drawText(x+450, (400-alto_4) + 34,QString::number(porBlanco,'f',2)+" %");

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
                m_arauz = (valores.at(1).toInt());//retorna los votos como enteros
            }
            else if(valores.at(0) == "Lasso")
            {
                m_lasso = (valores.at(1).toInt());//retorna los votos como enteros
            }
            else if(valores.at(0) == tr("Nulo"))
            {
                m_nulo = (valores.at(1).toInt());//retorna los votos como enteros
            }
            else
                m_blanco = (valores.at(1).toInt());//retorna los votos como enteros
        }

    }
}

void Resultados::on_cmdImagen_released()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         tr("Guardar imagen"),
                                                         QString(),
                                                         "Imagenes (*.png)");
    if (!nombreArchivo.isEmpty()){
        if (lienzo.save(nombreArchivo))
            QMessageBox::information(this,
                                     tr("Guardar imagen"),
                                     tr("Archivo almacenado en: ") + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 tr("Guardar imagen"),
                                 tr("No se pudo almacenar la imagen."));
    }
}

void Resultados::on_cmdExcel_released()
{
    //Crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::home();

    //Agregar al path absoluto del objeto un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath() + "/Resultados.csv";

    //Abrir un cuadro de dialogo para seleccionar el nombre y ubicacion del archivo a guardar
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar archivo", pathArchivo, "CSV (delimitado por comas) (*.csv)");

    //Crear el archivo a partir del nombre arrojado por el cuadro de dialogo
    QFile f(fileName);

    //Crear el objeto QTextstream (permite escribir sobre el archivo)
    QTextStream out(&f);

    //Intentar abrir el archivo ya sea para escribir(si no existe) o para agregar texto(si existe)
    if(!f.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::warning(this, "Resumen", "No se puede abrir el archivo");
        return;
    }

    //Guardar el contenido
    out << ";CNE" << endl
        << "Resultados" << endl;
    out << "Arauz;" << "Lasso;" << "Nulo;" << "Blanco" << endl;
    out << QString::number(m_arauz) << ";"
        << QString::number(m_lasso) << ";"
        << QString::number(m_nulo) << ";"
        << QString::number(m_blanco) << endl;

    out << QString("%" "%1;").arg(porArauz)
        << QString("%" "%1;").arg(porLasso)
        << QString("%" "%1;").arg(porNulo)
        << QString("%" "%1").arg(porBlanco) << endl;

    out << endl << "Votos Totales" << endl << QString::number(m_total);
    f.close();
}
