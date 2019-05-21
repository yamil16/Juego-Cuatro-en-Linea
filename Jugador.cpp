#include "Jugador.h"

jugador::jugador()
{
    int profundidad = 1;
    int color = 0;
    int heuristica = 1;
    int jug = 0;
    this->color=color;
    this->heuristica=heuristica;
    this->jug=jug;
    this->profundidad=profundidad;
    this->cantidadFichas=21;
 }

int jugador::getColor()
{
    return this->color;
}

int jugador::getHeuristica()
{
    return this->heuristica;
}

int jugador::getJugador()
{
    return this->jug;
}

int jugador::getProfundidad()
{
    return this->profundidad;
}

int jugador::getCantidadFichas()
{
    return this->cantidadFichas;
}

void  jugador::setJugador(int jug)
{
    this->jug=jug;
}

void  jugador::setHeuristica(int heuristica)
{
    this->heuristica=heuristica;
}

void  jugador::setProfundidad(int profundidad)
{
    this->profundidad=profundidad;
}

void  jugador::setColor(int color)
{
    this->color=color;
}

void jugador::setCantidadFichas(int cantidadFichas)  //el cantidad de fichas seria el getcantidad de fichas +1 o -1 dependiendo el caso.
{
    this->cantidadFichas=cantidadFichas;
}
