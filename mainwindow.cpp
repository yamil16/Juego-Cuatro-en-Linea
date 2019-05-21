#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow( QApplication *a )
{
    m.setupUi(this);
    sonidoActivado=true;
    setFixedHeight(600);
    setFixedWidth(800);
    setWindowTitle("Cuatro en Linea");
    setWindowIcon(QIcon(":/Imagenes/icono"));
    m.pc->clearFocus();
    m.dosJugadores->clearFocus();
    m.unJugador->clearFocus();

}

void MainWindow::on_siguiente_clicked()
{

    m2.setupUi(this);
    setWindowTitle("Cuatro en Linea");
    if (m.dosJugadores->isChecked())
    {
        jugadorRojo.setJugador(1);
        jugadorAzul.setJugador(1);
        tipoJuego=0;
        m2.nroheu1->setDisabled(true);
        m2.nroprof1->setDisabled(true);
        m2.nroheu2->setDisabled(true);
        m2.nroprof2->setDisabled(true);
        Jugador1=m2.nombrerojo->text();
        Jugador2=m2.nombreazul->text();
    }
    else
    {
        if (m.unJugador->isChecked())
        {
            tipoJuego=1;
            m2.nroheu1->setDisabled(true);
            m2.nroprof1->setDisabled(true);
            m2.nroheu2->setDisabled(false);
            m2.nroprof2->setDisabled(false);
            m2.jugadorActual->setDisabled(true);
        }
        else
        {
            tipoJuego=2;
            m2.nroheu1->setDisabled(false);
            m2.nroprof1->setDisabled(false);
            m2.nroheu2->setDisabled(false);
            m2.nroprof2->setDisabled(false);
        }
    }
}

void MainWindow::crearTablero()
{
        window = new QGroupBox(this);
        window->setGeometry(0,0,600,600);
        window->setFlat(true);
        window->setTitle("Cuatro en Linea");
        tablero = new QGroupBox(this);
        tablero->setGeometry(2,0,600,547);
        tablero->setFlat(true);
        tablero->setTitle("Cuatro en Linea");
        QLabel * image = new QLabel(tablero);
        image->setGeometry(2,0,600,640);
        image->setPixmap(QPixmap(":/Imagenes/TableroRojo"));
        ContenedorSel =new QGroupBox(this);
        ContenedorSel->setGeometry(2,0,570,65);
        botones = new QSignalMapper(tablero);
        QPair<int,int> coordenada;
        int contador = -1;
        select= new QSignalMapper(ContenedorSel);
        int contadorSelect=-1;

    for (int j=0; j<=columnas -1; j++)
    {
        for (int i=0; i<=filas -1; i++)
        {
            contador++;
            coordenada.first = i;
            coordenada.second = j;
            map.insert(contador,coordenada);
            QPushButton * ficha = new QPushButton(tablero);
            ficha->setGeometry(5+80*j,63+80*i,85,85);
             ficha->setFlat(true);
             ficha->setIcon(QIcon(":/Imagenes/FichaRojo"));
            ficha->setIconSize(QSize(85,85));
            botones->setMapping(ficha,contador);
            board_G[i][j] = ficha;
          }
        contadorSelect++;
        QPushButton * FichaSelecionar = new QPushButton(ContenedorSel);
        FichaSelecionar->setGeometry(8+80*j,0,65,65);
        FichaSelecionar->setFlat(true);
        FichaSelecionar->setIcon(QIcon(":/Imagenes/selec"));
        FichaSelecionar->setIconSize(QSize(60,60));
        connect(FichaSelecionar,SIGNAL(clicked()),select,SLOT(map()));
        select->setMapping(FichaSelecionar,contadorSelect);
        ConjuntoSelect[j] = FichaSelecionar;
    }
    connect(select,SIGNAL(mapped(int)),this,SLOT(botones_cliked(int)));
    window->show();
    ContenedorSel->show();
    tablero->show();
}

void MainWindow::botones_cliked(int pos)
{
     posicion=pos;
    if (tipoJuego == JugadorVsMaquina)
    {
        jugador_vs_maquina();
        jugador_vs_maquina();
    }
    else
        if (tipoJuego == JugadorVsJugador)
            jugador_vs_jugador();             
}

void MainWindow::maquina_vs_maquina(bool &corte)
{
   if (numeroTurno<=42)
   {

       posicion =juego.JugadorVirtual(tab,jugActual);//jugActual == color
       int fila=tab.getFilaAColocar(posicion);
       Graficar();
       tab.insertarFicha(posicion,jugActual);    
       if(!juego.hayCuatroEnLinea(fila,posicion,tab))
       {
           jugActual = cambiarJugador(jugActual);
           mostrarJugadorActual();
           numeroTurno++;
       }
       else
       {

           corte = true;
           QString gan=" ";
           if (jugActual == rojo )
               gan="gano el color rojo "+Jugador1;
           else
               gan="gano el color azul "+Jugador2;
           int valor = QMessageBox::question(NULL,"Hay un ganador","<font color = green ><font family = Calibri > Felicitaciones "+ gan + " ,deseas empezar una nueva partida?",QMessageBox::Yes,QMessageBox::No);
           if (valor == QMessageBox::Yes)
           {
               tablero->close();
               window->close();
               this->m.setupUi(this);
                 setWindowTitle("Cuatro en Linea");

           }
           else
               this->close();
        }
    if (numeroTurno>42)
    {
        corte = true;
       int valor = QMessageBox::question(NULL,"Hay Empate","<font color = green ><font family = Calibri >Ha habido un empate, deseas empezar una nueva partida?",QMessageBox::Yes,QMessageBox::No);
       if (valor == QMessageBox::Yes)
       {
           tablero->close();
           window->close();
           this->m.setupUi(this);
            setWindowTitle("Cuatro en Linea");

       }
       else
           this->close();
    }
   }
}


void MainWindow::jugador_vs_maquina()
{
    bool corte = true;
    if (jugActual == rojo )
        jugador_vs_jugador();
    else
    {
        int fila = tab.getFilaAColocar(posicion)+1;
        if (!juego.hayCuatroEnLinea(fila, posicion, tab))
            if (jugActual == azul)
            {
                corte = false;
                maquina_vs_maquina(corte);
            }
    }
}

int MainWindow::cambiarJugador(int jugador)
{
    if (jugador == rojo)
        return azul;
    else return rojo;
}

void MainWindow::mostrarJugadorActual(){
    if (jugActual==rojo)
        t.jugActual->setText(Jugador1+" Rojo");
    else
        t.jugActual->setText(Jugador2+" Azul");
}

void MainWindow::jugador_vs_jugador()
{

    int fila = tab.getFilaAColocar(posicion);
    if ((fila>=0) && (tab.getColor(fila,posicion)==casilleroLibre) && (numeroTurno<=42))
    {
        Graficar();
        int color;
        if (jugActual==rojo)
            color=1;
        else
            color=2;
        tab.insertarFicha(posicion,color);
        juego.actualizarFicha(color, resta);
        int fila = tab.getFilaAColocar(posicion)+1;
        if(juego.hayCuatroEnLinea(fila, posicion, tab) && (numeroTurno<=42))
        {
            QString gan=" ";
            if (jugActual == rojo )
                gan="gano el color rojo "+Jugador1;
            else
                gan="gano el color azul "+Jugador2;
            int valor = QMessageBox::question(NULL,"Hay un ganador","<font color = green ><font family = Calibri > Felicitaciones "+ gan + " , deseas empezar una nueva partida?",QMessageBox::Yes,QMessageBox::No);
            if (valor == QMessageBox::Yes){
                this->m.setupUi(this);
                 setWindowTitle("Cuatro en Linea");
                }
            else
                this->close();

        }
        else
            if(numeroTurno==42)
            {
                int valor = QMessageBox::question(NULL,"Hay Empate","<font color = green ><font family = Calibri >Ha habido un empate, desaas empezar una nueva partida?",QMessageBox::Yes,QMessageBox::No);
                if (valor == QMessageBox::Yes){
                    this->m.setupUi(this);
                     setWindowTitle("Cuatro en Linea");
                       }
                else
                    this->close();
            }
            else
            numeroTurno++;
            jugActual = cambiarJugador(jugActual);
            mostrarJugadorActual();
    }
    else
    {
        QErrorMessage * errorMessageDialog = new QErrorMessage(NULL);
        errorMessageDialog->showMessage("<font family = Calibri >Le informamos que esta queriendo insertar una ficha en una columna llena. ");
    }
}



void MainWindow::Graficar()
{
    int fila = tab.getFilaAColocar(posicion);
    if (jugActual == rojo)
        board_G[fila][posicion]->setIcon(QIcon(":/Imagenes/FichaRojaM"));
    else
        board_G[fila][posicion]->setIcon(QIcon(":/Imagenes/FichaAzulM"));
    QCoreApplication::processEvents();
}

void MainWindow::on_jugar_clicked()
{


    if (tipoJuego == 1)
    {
        int HeuristicaAzul = m2.nroheu2->currentIndex()+1;
        int ProfundidadAzul = m2.nroprof2->currentIndex()+1;
        jugadorAzul.setHeuristica(HeuristicaAzul);
        jugadorAzul.setJugador(2); //maquina==2
        jugadorAzul.setProfundidad(ProfundidadAzul);
        jugadorRojo.setJugador(1);
        juego.cargarJugadores(jugadorRojo, jugadorAzul);
    }
    else
        if (tipoJuego==2)
        {
            int HeuristicaRojo = m2.nroheu1->currentIndex()+1;
            int HeuristicaAzul = m2.nroheu2->currentIndex()+1;
            int ProfundidadRojo = m2.nroprof1->currentIndex()+1;
            int ProfundidadAzul = m2.nroprof2->currentIndex()+1;
            jugadorRojo.setHeuristica(HeuristicaRojo);
            jugadorRojo.setJugador(2);
            jugadorRojo.setProfundidad(ProfundidadRojo);
            jugadorRojo.setCantidadFichas(21);
            jugadorAzul.setHeuristica(HeuristicaAzul);
            jugadorAzul.setJugador(2);
            jugadorAzul.setProfundidad(ProfundidadAzul);
            jugadorAzul.setCantidadFichas(21);
            juego.cargarJugadores(jugadorRojo, jugadorAzul);

        }
    Jugador2=m2.nombreazul->text();
    Jugador1=m2.nombrerojo->text();
    t.setupUi(this);
    setWindowTitle("Cuatro en Linea");
    numeroTurno=1;
    tab.setFilaAColocar();
    tab.formatearTablero();
    if (m2.jugadorActual->currentIndex() == 0)
        jugActual = rojo;
    else
        jugActual = azul;
    mostrarJugadorActual();
    crearTablero();
    if (tipoJuego == MaquinaVsMaquina)
    {
        disconnect(select,SIGNAL(mapped(int)),this,SLOT(botones_cliked(int)));
        bool corte = false;
        while((!corte) && (numeroTurno <= 42))
        {
            maquina_vs_maquina(corte);
        }
    }
}

void MainWindow::on_Atras_clicked()
{
    m.setupUi(this);
     setWindowTitle("Cuatro en Linea");
}

void MainWindow::on_Atras2_clicked()
{
    m.setupUi(this);
     setWindowTitle("Cuatro en Linea");
}

void MainWindow::on_Salir_clicked()
{
    this->close();
}

void MainWindow::on_siguiente_2_clicked()
{
    if (sonidoActivado==true){

        sonidoActivado=false;
    }
    else
    {

        sonidoActivado=true;
    }
}




