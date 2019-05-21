#ifndef JUGADOR_H
#define JUGADOR_H
#include "Constantes.h"

class jugador{

   private:
        int jug;
        int heuristica;
        int profundidad;
        int color;
        int cantidadFichas;

   public:
        jugador();
        int getJugador();
        int getHeuristica();
        int getProfundidad();
        int getColor();
        int getCantidadFichas();
        void setCantidadFichas(int cantidadFichas);
        void setJugador(int jug);
        void setHeuristica(int heuristica);
        void setProfundidad(int profundidad);
        void setColor(int color);
};


#endif // JUGADOR_H
