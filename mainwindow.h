#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QMap>
#include <QPair>
#include <QString>
#include <QSignalMapper>
#include <QApplication>
#include "Juego.h"
#include "Tablero.h"
#include "Jugador.h"
#include "ui_mainwindow.h"
#include "ui_mainwindow2.h"
#include "ui_PantallaInicial.h"
#include "Constantes.h"



#include <QFile>
#include <QDir>
#include <QUrl>
#include <QtGui>


#include <QCoreApplication>


#include<QErrorMessage>
#include <QMessageBox>

namespace BackendCapabilities{
class MainWindow;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT
public:
    static const int JugadorVsJugador = 0;
    static const int JugadorVsMaquina= 1;
    static const int MaquinaVsMaquina = 2;
    int cambiarJugador(int jugActual);


   MainWindow(QApplication *a);

private slots:
   void on_siguiente_clicked();

   void on_jugar_clicked();

   void on_Atras_clicked();

   void on_Atras2_clicked();

   void on_Salir_clicked();

   void botones_cliked(int pos);



   void on_siguiente_2_clicked();


private:

   Ui::Menu1 m;
   Ui::Menu2 m2;
   Ui::TableroJuego t;
   QGroupBox *  tablero;
   QGroupBox *  window;
   QPushButton * board_G[6][7];



   QPushButton *ConjuntoSelect[7];
   QGroupBox * ContenedorSel;

   void crearTablero();
   void jugador_vs_maquina();
   void jugador_vs_jugador();
   void mostrarJugadorActual();
   void maquina_vs_maquina(bool &corte);
   void Graficar();
   Tablero tab;
   Juego juego;

   int posicion;
   int jugActual;
   int tipoJuego;
   int numeroTurno;
   QString Jugador1;
   QString Jugador2;
   jugador jugadorRojo;
   jugador jugadorAzul;
   QSignalMapper * botones;
   QMap <int,QPair<int,int> > map;
   bool sonidoActivado;

   QSignalMapper *select;
   int filaAInsertar[7];

};
#endif //MAINWINDOW_H
