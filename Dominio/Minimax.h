#ifndef minimax_h
#define minimax_h
#include <iostream>
#include "Juego.h"

using namespace std;
/**
 * Clase "Minimax" que contiene el algoritmo de Minimax 
*/
class Minimax
{
private:
    int mejorPuntaje(Juego* juego,int nivelActualArbol,int limiteMaximoArbol,int jugador);
    int menorPuntaje(Juego* juego,int nivelActualArbol,int limiteMaximoArbol,int jugador);
    
public:
    Minimax();
    
    int minimax(Juego* juego,int nivelActualArbol,int limiteMaximoArbol,int jugador);
};


Minimax::Minimax()
{
}


int  Minimax::mejorPuntaje(Juego* juegoActual,int nivelActualArbol,int limiteMaximoArbol,int jugador){
    if(juegoActual->juegoTerminado() || nivelActualArbol == limiteMaximoArbol ){
        return juegoActual->verificarEstado();
    }
    int mejorPunto = -1;
    int valorAux;
    Juego* juegoAux = new Juego(juegoActual);

    for(int i=0;i<7;i++){
        juegoActual->hacerMovimiento(i,jugador);
        if(jugador == 2){
            valorAux = menorPuntaje(juegoAux,nivelActualArbol+1,limiteMaximoArbol,1);
        }
        else{
            valorAux = menorPuntaje(juegoAux,nivelActualArbol+1,limiteMaximoArbol,2);
        }

        if(valorAux >= mejorPunto){
            mejorPunto = valorAux;
        }

        *juegoActual = *juegoAux;
    }
    delete juegoAux;
    return mejorPunto;
}

int Minimax::menorPuntaje(Juego* juegoActual,int nivelActualArbol,int limiteMaximoArbol,int jugador){
    if(juegoActual->juegoTerminado() || nivelActualArbol == limiteMaximoArbol){
        return juegoActual->verificarEstado();
    }
    int mejorPunto = 100;
    int valorAux;
    Juego* juegoAux = new Juego(juegoActual);

    for(int i=0;i<7;i++){
        juegoActual->hacerMovimiento(i,jugador);
        if(jugador == 2){
            valorAux = mejorPuntaje(juegoAux,nivelActualArbol+1,limiteMaximoArbol,1);
        }
        else{
            valorAux = mejorPuntaje(juegoAux,nivelActualArbol+1,limiteMaximoArbol,2);
        }

        if(valorAux <= mejorPunto){
            mejorPunto = valorAux;
        }

        *juegoActual = *juegoAux;
        
    }
    delete juegoAux;
    return mejorPunto;


}

/**
 * Algoritmo de Minimax sin poda alfa-beta, este metodo hace una "simulación" de un arbol, implementado con recursividad de menorPuntaje
 * 
*/
int Minimax::minimax(Juego* juegoActual,int nivelActualArbol,int limiteMaximoArbol,int jugador){
    int mejorMovimiento = -100;
    int movimientoAux;
    Juego* juegoAux = new Juego(juegoActual);
    int total = -1;

    for(int i=0;i<7;i++){
        juegoActual->hacerMovimiento(i,jugador);
        if(jugador == 2){
            movimientoAux =  menorPuntaje(juegoAux,nivelActualArbol+1,limiteMaximoArbol,1);
        }
        else{
            movimientoAux = menorPuntaje(juegoAux,nivelActualArbol+1,limiteMaximoArbol,2);
        }

        if(movimientoAux > mejorMovimiento && !juegoAux->columnaLlena(i)){
            mejorMovimiento = movimientoAux;
            total = i;
        }

        *juegoActual = *juegoAux;
    }
    delete juegoAux;
    return total;
}


#endif