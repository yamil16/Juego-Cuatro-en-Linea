#include "Tablero.h"
#include <iostream>
#include "Jugador.h"
using namespace std;

Tablero::Tablero()
{
    for(int j=0;j<=columnas -1;j++)
    {
        for(int i=0;i<=filas -1;i++)
            tab[i][j]= casilleroLibre;
        filaAColocar[j] = filas - 1;
    }
}

Tablero::Tablero(Tablero &nuevo)
{
    for(int j=0;j<=columnas -1;j++)
    {
        for(int i=0;i<=filas -1;i++)
            tab[i][j]= nuevo.getColor(i,j);
        filaAColocar[j] = nuevo.getFilaAColocar(j);
    }
}

void Tablero::imprimirTablero(){
    for(int i=0;i<=filas-1;i++){
        for(int j=0;j<=columnas-1;j++){
            cout<<tab[i][j]<< " ";
        }
        cout <<""<< endl;
    }
}

void Tablero::formatearTablero()
{
    for(int j=0;j<=columnas -1;j++)
    {
        for(int i=0;i<=filas -1;i++)
            tab[i][j]= casilleroLibre;
        filaAColocar[j] = filas - 1;
    }
}

int Tablero::getColor(int fila, int columna)
{
    return tab[fila][columna];
}

int Tablero::getColor(int columna)
{
    int fila=getFilaAColocar(columna);
    return tab[fila][columna];
}

int Tablero::getFilaAColocar(int columna)
{
    return filaAColocar[columna];
}

void Tablero::setFilaAColocar()
{
    for(int i=0;i<=columnas-1;i++)
         filaAColocar[i] = filas - 1;
}

void Tablero::insertarFicha(int columna, int color)
{
    int fila = filaAColocar[columna];
    if ((columna >= 0) && (columna <= columnas -1) && (fila >= 0))
    {
        tab[fila][columna]=color;
        filaAColocar[columna] --;
    }
    else
        cout << "no se puede insertar la ficha" << endl;
}

bool Tablero::columnaLlena(int columna)
{
   if (tab[0][columna]!=casilleroLibre)
       return true;
   else
       return false;
}

bool Tablero::tableroLleno()
{
    bool resultado = true;
    for (int i=0; i <= columnas-1; i++)
        if (!columnaLlena(i))
            resultado = false;
    return resultado;

}

void Tablero::eliminarFicha(int columna)
{
    int fila = filaAColocar[columna] + 1;
    if (tab[fila][columna]!=casilleroLibre)
    {
        tab[fila][columna]=casilleroLibre;
        filaAColocar[columna] ++;
    }else
        cout << "no se puede eliminar la ficha" << endl;
}

std::string Tablero::pasarAString()
{
    string salida = "";
    for (int i=0; i<=filas-1; i++)
        for (int j=0; j<=columnas-1; j++)
        {
            char val;
            if (tab[i][j] == 0)
                val = 'l';
            else
                if (tab[i][j] == 1)
                    val = 'r';
                else
                    if (tab[i][j] == 2)
                        val = 'a';

            salida.push_back(val);
        }
    return salida;
}
