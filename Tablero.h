#ifndef TABLERO_H
#define TABLERO_H
#include <list>
#include "Constantes.h"
#include <QString>
#include <iostream>

class Tablero{

private:
    int tab[filas][columnas];
    int filaAColocar[columnas];

public:
    Tablero(Tablero &nuevo);
    Tablero();
    int getColor(int columna);
    int getColor(int fila,int columna);
    void insertarFicha(int columna, int color);
    bool columnaLlena(int columna);
    bool tableroLleno();
    void eliminarFicha(int columna);
    int getFilaAColocar(int columna);
    void setFilaAColocar();
    void formatearTablero();
    void imprimirTablero();
    std::string pasarAString();

};

#endif // TABLERO_H
