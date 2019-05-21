#ifndef JUEGO_H
#define JUEGO_H
#include "Tablero.h"
#include "Jugador.h"
#include <QObject>
#include "Constantes.h"
#include <iostream>

#include <QString>
#include <QList>
#include <QMap>
#include <QPair>


class Juego{

private:
         int numeroTurno;
         int jugActual;
         Tablero tab;
         jugador jug[2];

          int cantidadFichas(int fila, int columna, int operador1, int operador2, Tablero tab);
          int cantidadFichasIzquierda(int fila,int columna, Tablero tab);
          int cantidadFichasDerecha(int fila,int columna, Tablero tab);
          int cantidadFichasAbajo(int fila,int columna, Tablero tab);
          int cantidadFichasDiagonalSupIzq(int fila, int columna, Tablero tab);
          int cantidadFichasDiagonalSupDer(int fila, int columna, Tablero tab);
          int cantidadFichasDiagonalInfIzq(int fila, int columna, Tablero tab);
          int cantidadFichasDiagonalInfDer(int fila, int columna, Tablero tab);
          std::list<int> jugadasPosibles(Tablero nuevo);

          int ContarNenLinea(Tablero tab,int pos,int fil,int col);
          int MatrizAuxHeu1(int i, int j);
          int MatrizAuxHeu3(int i, int j);
          int EvalHeuUno(Tablero tab);
          int EvalHeuDos(Tablero tab);
          int EvalHeuTres(Tablero tab);
          int evaluarHeuristica(int heuristica, Tablero tab);

          void RealizarMovimientoJugadorVirtual(int pos);
          int BusquedaEnProfundidad(Tablero Actual, int heu, int prof, int asigjug , int JugActual, int alpha, int betha, QMap<std::string, int> &visitados, int posicionColumna/*, int &contador*/);
          int HeuristicaEval(Tablero tab, int heur);
          void Ordenar(Tablero tab, std::list<int> &jugadasPosibles, int color);


public:
          explicit Juego ();
          int JugadorVirtual(Tablero Actual, int color);
          bool hayCuatroEnLinea(int fila, int columna, Tablero tab);

          void cargarJugadores(jugador j1, jugador j2);
          int cambiarJugador(int jugador);
          void actualizarFicha(int jugador, int operador);

};

#endif // JUEGO_H
