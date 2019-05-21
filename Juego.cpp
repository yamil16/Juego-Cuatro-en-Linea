#include "Juego.h"
#include <QMetaMethod>


using namespace std;

Juego::Juego()//QObject *parent)
{

}

int Juego::cantidadFichas(int fila, int columna, int operador1, int operador2, Tablero tab)
{
    int contador=0;
    bool seguir=true;
    int posc=columna;
    int posf=fila;
    while ((posc<=columnas-1) && (posc>=0) && (posf<=filas-1) && (posf>=0) && (seguir))
    {
        posc= posc + operador2;
        posf= posf + operador1;
        if ((posc<=columnas-1) && (posc>=0) && (posf <= filas-1) && (posf >= 0))
        {
            if ((tab.getColor(fila,columna) != 0) && (tab.getColor(posf,posc)==tab.getColor(fila,columna)))
                contador++;
            else
                seguir=false;
        }
    }
    return contador;
}

int Juego::cantidadFichasDerecha(int fila, int columna, Tablero tab)
{
    int contador= cantidadFichas(fila, columna, igual, suma, tab);
    return contador;
}
int Juego::cantidadFichasIzquierda(int fila, int columna, Tablero tab)
{
    int contador= cantidadFichas(fila, columna, igual, resta, tab);
    return contador;
}
int Juego::cantidadFichasAbajo(int fila, int columna, Tablero tab)
{
    int contador= cantidadFichas(fila, columna, suma, igual, tab); //xq empieza de 00 y x va aumentando
    return contador;
}
int Juego::cantidadFichasDiagonalSupDer(int fila, int columna, Tablero tab)
{
    int contador= cantidadFichas(fila, columna, resta, suma, tab);
    return contador;
}
int Juego::cantidadFichasDiagonalSupIzq(int fila, int columna, Tablero tab)
{
    int contador= cantidadFichas(fila, columna, resta, resta, tab);
    return contador;
}
int Juego::cantidadFichasDiagonalInfDer(int fila, int columna, Tablero tab)
{
    int contador= cantidadFichas(fila, columna, suma, suma, tab);
    return contador;
}
int Juego::cantidadFichasDiagonalInfIzq(int fila, int columna, Tablero tab)
{
    int contador= cantidadFichas(fila, columna, suma, resta, tab);
    return contador;
}

bool Juego::hayCuatroEnLinea(int fila, int columna, Tablero tab)
{
    int contador=0;
    bool si = false;
    if (tab.getColor(fila,columna) != 0)
    {
        contador = cantidadFichasDerecha(fila,columna, tab) + 1 + cantidadFichasIzquierda(fila, columna, tab);
        if (contador >= 4)
            si = true;
        else
        {
            contador = cantidadFichasAbajo(fila, columna, tab) + 1;
            if (contador >= 4)
                si =  true;
            else
            {
                contador = cantidadFichasDiagonalInfDer(fila, columna, tab) + 1 + cantidadFichasDiagonalSupIzq(fila, columna, tab);
                if (contador >= 4)
                    si = true;
                else
                {
                    contador = cantidadFichasDiagonalInfIzq(fila, columna, tab) + 1 + cantidadFichasDiagonalSupDer(fila, columna, tab);
                    if (contador >= 4)
                        si = true;
                }
            }
        }
    }
    return si;
}

void Juego::cargarJugadores(jugador j1, jugador j2)
{
        jug[jugadorRojo].setHeuristica(j1.getHeuristica());
        jug[jugadorRojo].setColor(rojo);
        jug[jugadorRojo].setJugador(j1.getJugador());
        jug[jugadorRojo].setProfundidad(j1.getProfundidad());
        jug[jugadorRojo].setCantidadFichas(j1.getCantidadFichas());
        jug[jugadorAzul].setCantidadFichas(j2.getCantidadFichas());
        jug[jugadorAzul].setHeuristica(j2.getHeuristica());
        jug[jugadorAzul].setColor(azul);
        jug[jugadorAzul].setJugador(j2.getJugador());
        jug[jugadorAzul].setProfundidad(j2.getProfundidad());
}

int Juego::HeuristicaEval(Tablero tab, int heur)
{
    switch (heur)
    {
        case 1:
        {
            return EvalHeuUno(tab);
            break;
        }
            case 2:
        {
               return EvalHeuDos(tab);
                break;
        }
            case 3:
        {
               return EvalHeuTres(tab);
               break;
        }
            default:
        {
            return EvalHeuUno(tab);
            break;
        }
    }
}


void Juego::Ordenar(Tablero Actual, std::list <int> &jugadas, int color)
{
    std::list <int> ordenada;
    while (!jugadas.empty())
    {
    list <int>::iterator puntMenor = jugadas.begin();
    int min = 5000;
    int minJug;
    int val = 0;
    for (list<int>::iterator jug=jugadas.begin();jug!=jugadas.end();jug++)
    {
        Actual.insertarFicha(*jug, color);
        if (color == azul)
            val = EvalHeuTres(Actual);
        else
            val = - EvalHeuTres(Actual);
        if (val < min)
        {
            min = val;
            puntMenor = jug;
        }
        Actual.eliminarFicha(*jug);
    }
    minJug = *puntMenor;
    ordenada.splice(ordenada.begin(),jugadas,puntMenor);
    }
    jugadas = ordenada;
}


void Juego::actualizarFicha(int jugador, int operador)
{
    jug[jugador-1].setCantidadFichas(jug[jugador-1].getCantidadFichas()+ operador);
}

std::list<int> Juego::jugadasPosibles(Tablero nuevo)
{
    list<int> listaN;
    for (int i=0;i<=columnas-1;i++)
       if(!nuevo.columnaLlena(i))
           listaN.push_back(i);
    return listaN;
}

int Juego::cambiarJugador(int jugador)
{
    if (jugador == rojo)
        return azul;
    else
        return rojo;
}

 int Juego::JugadorVirtual(Tablero Actual, int color)
{
    QMap<string, int> visitados;
    int betha=-5000;
    /*int contador = 0;*/
    list<int>JugPos=jugadasPosibles(Actual);
    Tablero nuevo(Actual);
    int max = 0; //la pos que retorno.
    Ordenar(nuevo, JugPos, color);
    for( list<int>::iterator it=JugPos.begin();it!=JugPos.end();it++)
    {
        if (nuevo.getColor(*it)== casilleroLibre)
        {
            nuevo.insertarFicha(*it,color);
            string clave = nuevo.pasarAString();
            int auxiliar = 1234;
            visitados.insert(clave, auxiliar);
            actualizarFicha(color, resta);
            int val=1;
            int asignarJug;
            if(color== rojo)
                asignarJug=-1;
            else
                asignarJug=1;
            /*contador = 0;*/
            if (jug[color-1].getProfundidad() > 0)
                val=-BusquedaEnProfundidad(nuevo,jug[color-1].getHeuristica(),jug[color-1].getProfundidad()-1,-asignarJug,cambiarJugador(color),-5000, -betha, visitados,*it/*, contador*/);
           visitados[clave] = val;
            if(val>betha)
            {
                betha=val;
                max=*it;
                /** beta se queda con el mas chico, pero en la columna a insertar se queda con el mas grande**/
            }
            nuevo.eliminarFicha(*it);
            actualizarFicha(color, suma);
        }
    }
    nuevo.insertarFicha(max, color);
    return max;
}

int Juego::BusquedaEnProfundidad(Tablero Actual,int heu,int prof,int asigjug ,int jugador,int alpha,int betha, QMap<std::string, int> &visitados,int posicionColumna/*, int &contador*/)
{
    string clave = Actual.pasarAString();
    if ((!visitados.contains(clave)) || (visitados[clave] == 1234))
     {
        /*contador++;*/
        int fila = Actual.getFilaAColocar(posicionColumna)+1;
         int auxiliar = 1234;
         visitados.insert(clave, auxiliar);
         if (hayCuatroEnLinea(fila,posicionColumna,Actual))
         {
             alpha = 999*(-1);
         }

         else
         {
             if ((prof==0) || (Actual.tableroLleno()))
             {
                 alpha= (asigjug)* HeuristicaEval(Actual,heu);
             }
             else
             {
                 list<int>jugadas=jugadasPosibles(Actual);
                 Ordenar(Actual, jugadas, jugador);
                 for(list<int >::iterator it=jugadas.begin();it!=jugadas.end();it++)
                 {
                     if (Actual.getColor(*it)==casilleroLibre)
                     {
                         Actual.insertarFicha(*it,jug[jugador-1].getColor());
                         actualizarFicha(jugador, resta);


                         int val=-BusquedaEnProfundidad(Actual, heu, prof-1,-asigjug ,cambiarJugador(jugador),-betha,-alpha,visitados,*it/*, contador*/);
                         Actual.eliminarFicha(*it);
                         actualizarFicha(jugador, suma);
                         if(val>alpha)
                         {
                             alpha=val;
                         }
                         if (alpha>=betha)
                         {
                             return alpha;
                         }
                     }
                }
            }
        }
        visitados[clave] = alpha;
     }
     else
    {
         alpha = visitados.value(clave);
    }
    return alpha;
}


 int Juego::MatrizAuxHeu1(int i, int j)
{
    int tablero_H1[6][7]={
                            0,  1,  5, 20,  5,  1,  0,
                            1,  5, 10, 30, 10,  5,  1,
                            5, 10, 30, 50, 30, 10,  5,
                            5, 10, 30, 50, 30, 10,  5,
                            1,  5, 20, 30, 20,  5,  1,
                            0,  1, 15, 20, 15,  1,  0
                        }; //heuristica 1

    return tablero_H1[i][j];
}

 int Juego::MatrizAuxHeu3(int i, int j)
{
    int tablero_H2[6][7]={
                            1,  2,  5, 10,  5,  2,  1,
                            1,  2,  5, 10,  5,  2,  1,
                            1,  2,  5, 10,  5,  2,  1,
                            1,  2,  5, 10,  5,  2,  1,
                            1,  2,  5, 10,  5,  2,  1,
                            1,  2,  5, 10,  5,  2,  1
                        }; //heuristica 3

    return tablero_H2[i][j];
}

int Juego::EvalHeuUno(Tablero tab)                      //busca poner fichas en posiciones centrales
{
    int valorH=0;
    for (int i=0; i<=filas-1;i++)
    {
        for(int j=0; j<=columnas-1;j++)
        {
            if (tab.getColor(i,j)==rojo)
                valorH=valorH-MatrizAuxHeu1(i,j);
            else
                if (tab.getColor(i,j)== azul)
                    valorH=valorH+MatrizAuxHeu1(i,j);
        }
    }
    return valorH;
}

int Juego::EvalHeuDos(Tablero tab)               //cuenta la cantidad de fichas en linea que hay en el tablero
{
    int valorH=0;
    for (int i=0; i<=filas-1;i++)
    {
        for(int j=0; j<=columnas-1;j++)
        {
            if (tab.getColor(i,j)== rojo)
                valorH= valorH + (-20)*ContarNenLinea(tab, 4, i, j)+ (-5) * ContarNenLinea(tab, 3, i, j);
            else
                if (tab.getColor(i,j)== azul)
                    valorH= valorH + (20)*ContarNenLinea(tab, 4, i, j)+ (5) * ContarNenLinea(tab, 3, i, j);
        }
    }
    return valorH;
}

int Juego::ContarNenLinea(Tablero nuevo,int n,int fila,int columna)
{
    int suma=0;
    int contador=0;
    if (nuevo.getColor(fila,columna) != 0)
    {
        contador = cantidadFichasDerecha(fila,columna, nuevo) + 1;
        if (contador >= n)
            suma++;
        else
        {
            contador = cantidadFichasAbajo(fila, columna, nuevo) + 1;
            if (contador >= n)
               suma++;
            else
            {
                contador = cantidadFichasDiagonalInfDer(fila, columna, nuevo) + 1;
                if (contador >= n)
                   suma++;
                else
                {
                    contador = cantidadFichasDiagonalInfIzq(fila, columna, nuevo) + 1;
                    if (contador >= n)
                        suma++;
                }
            }
        }
    }
    return suma;
}

int Juego::EvalHeuTres(Tablero tab)  //busca generar posiblidades de 4 en linea de 2 formas distintas
{

    int valorH=0;
    int valorH4=0;
    for (int i=0; i<=filas-1;i++)
    {
        for(int j=0; j<=columnas-1;j++)
        {
            if (tab.getColor(i,j)==rojo)
            {
                valorH=valorH-MatrizAuxHeu3(i,j);
                valorH4= valorH4 + (-15)*ContarNenLinea(tab, 4, i, j)+ (-5) * ContarNenLinea(tab, 3, i, j) + (-1) * ContarNenLinea(tab,2,i,j) ;
            }
            else
                if (tab.getColor(i,j)== azul)
                {
                    valorH=valorH+MatrizAuxHeu3(i,j);
                    valorH4= valorH4 + (15)*ContarNenLinea(tab, 4, i, j)+ (5) * ContarNenLinea(tab, 3, i, j) + (1) * ContarNenLinea(tab,2,i,j);
                }
        }
    }
    return valorH+valorH4;
}
