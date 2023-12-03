#ifndef juego_h
#define juego_h
#include <iostream>
using namespace std;

/**
 * Clase "Juego" que contendra el mapa del juego "Conecta 4" con 6 de fila y 7 de columna.
*/
class Juego{
private:
    static const int fila = 6;
    static const int columna = 7;
    int matriz[fila][columna];

public:
    Juego();
    Juego(Juego* copiaJuego);
    void dibujarJuego();
    bool hacerMovimiento(int jugador, int columna);
    bool columnaLlena(int columna);
    bool matrizLlena();
    bool verificar4Vertical(int jugador);
    bool verificar4Horizontal(int jugador);
    bool verificarDiagonalIzquierdaADerecha(int jugador, int i, int j);
    bool verificarDiagonalDerechaAIzquierda(int jugador, int i, int j);
    bool verificarDiagonales(int jugador);
    int victoria(int jugador);
    bool juegoTerminado();
    int verificarEstado();
    
    
};

/**
 * Primer constructor de "Juego" que instanciara en cada posición de la matriz
 * valor "0".
**/
Juego::Juego(){
    for(int i=0;i<fila;i++){
        for(int j=0;j<columna;j++){
            matriz[i][j] = 0;
        }
    }
}

/** 
 * Segundo constructor de "Juego" que contendra una copia de una clase "Juego" instanciada anteriormente.
 * La intención de un segundo constructor es para que la copia del mapa vaya a la clase de "Minimax.h"
**/
Juego::Juego(Juego* copiaJuego){
    for(int i=0;i<fila;i++){
        for(int j=0;j<columna;j++){
            matriz[i][j] = copiaJuego->matriz[i][j];
        }
    }
}

/**
 * Metodo que imprimira el mapa del juego "Conecta 4".
**/
void Juego::dibujarJuego(){
        for(int i=0;i<fila;i++){
            cout<<"[ ";
            for(int j=0;j<columna;j++){
                if(j > 0){
                    cout<<"[ "<<matriz[i][j]<<" ] ";
                }
                else{
                    cout<<matriz[i][j]<<" ] ";
                }
               
            }
            cout<<""<<endl;
        
        }
        
}

/**
 * Metodo que ingresara la jugada de un jugador o la "IA".
 * @return Retorna un "True" si es que se permitio la posicion en la matriz. "False" si es que la posición seleccionada
 *         esta fuera de la matriz.
*/
bool Juego::hacerMovimiento(int jugador,int columna){
    if (columna < 0 || columna >= this->columna) {
            cout << "Columna invalida"<<endl;
            return false;
        }

    for (int i = fila - 1; i >= 0; --i) {
        if (matriz[i][columna] == 0) {
            matriz[i][columna] = jugador;
            return true;
        }
    }

    return false;
    
}

/**
 * Metodo que verifica si alguna columna esta llena.
 * @return Retorna un "True" si es que la columna esta llena, "False" si es que es lo contrario.
*/
bool Juego::columnaLlena(int columna){
    if(matriz[0][columna] == 0){
        return false;
    }
    return true;
}

/**
 * Metodo que verifica si el mapa de "Conecta 4" esta llena.
 * @return Retorna "True" si es que la matriz esta llena o "False" si es lo contrario.
*/
bool Juego::matrizLlena() {
    for (int j = 0; j < columna; j++) {
        if (matriz[0][j] == 0) {
            return false;
        }
    }
    return true;
}

/**
 * Metodo que verifica si hay 4 fichas conectadas verticalmente en el mapa.
 * @return Retorna "True" si es que hay 4 fichas conectadas vertical o "False" si es lo contrario.
*/
bool Juego::verificar4Vertical(int jugador){
    int victoria = 0;
    for(int j = 0;j<columna;j++){
        for(int i=0;i<fila;i++){
            if(matriz[i][j] == jugador){
                victoria +=1;
            }else{
                victoria = 0;
            }

            if(victoria == 4) {
                return true;
            }
        }
        victoria = 0;
    }
    return false;

}

/**
 * Metodo que verifica si hay 4 fichas conectadas horizontalmente en el mapa.
 * @return Retorna "True" si es que hay 4 fichas conectadas horizontalmente o "False" si es lo contrario.
*/
bool Juego::verificar4Horizontal(int jugador){
    int victoria = 0;
    for(int i=0;i<fila;i++){
        for(int j=0;j<columna;j++){
            if(matriz[i][j] == jugador){
                victoria+=1;
            }
            else{
                victoria =0;
            }
            if(victoria == 4){
                return true;
            }
            
        }
        victoria =0;
    }
    return false;

}

/**
 * Metodo que verifica si hay 4 fichas conectadas diagonalmente de izquierda a derecha en el mapa.
 * @return Retorna "True" si es que hay 4 fichas conectadas diagonalmente o "False" si es lo contrario.
*/
bool Juego::verificarDiagonalIzquierdaADerecha(int jugador,int i,int j){
    int victoria = 0;
    for (; i < fila && j < columna; i++, j++) {
        if (matriz[i][j] == jugador) {
            victoria += 1;
        } else {
            victoria = 0;
        }

        if (victoria == 4) {
            return true;
        }
    }
    return false;
}

/**
 * Metodo que verifica si hay 4 fichas conectadas diagonalmente de derecha a izquierda en el mapa.
 * @return Retorna "True" si es que hay 4 fichas conectadas diagonalmente o "False" si es lo contrario.
*/
bool Juego::verificarDiagonalDerechaAIzquierda(int jugador,int i,int j){
    int victoria = 0;
    for (; i < fila && j >= 0; i++, j--) {
        if (matriz[i][j] == jugador) {
            victoria += 1;
        } else {
            victoria = 0;
        }

        if (victoria == 4) {
            return true;
        }
    }
    return false;
}

/**
 *  Metodo que itera sobre todas las posibles posiciones iniciales de las diagonales en el tablero,
 *  llama a las funciones anteriores para verificar las dos direcciones de cada posición inicial.
 *  @return Retorna "True" si es que hay 4 fichas conectadas diagonalmente o "False" si es lo contrario.
*/
bool Juego::verificarDiagonales(int jugador){
    for (int i = 0; i <= fila - 4; i++) {
        for (int j = 0; j <= columna - 4; j++) {
            if (verificarDiagonalIzquierdaADerecha(jugador, i, j)) {
                return true;
            }
        }
    }

    for (int i = 0; i <= fila - 4; i++) {
        for (int j = 3; j < columna; j++) {
            if (verificarDiagonalDerechaAIzquierda(jugador, i, j)) {
                return true;
            }
        }
    }

    return false;
}

/**
 * Metodo que verifica si es que hay 4 fichas conectadas con todos los sucesos posibles.
 * @return Retorna un "0" si es que no hay victoria de algun jugador o "False" si es que gano un jugador ingresado por parametro.
*/
int Juego::victoria(int jugador){
    if(verificar4Vertical(jugador) || verificar4Horizontal(jugador) || verificarDiagonales(jugador)){
        return jugador;
    }
    return 0;
}

/**
 * Metodo que verifica si el juego ha terminado ya sea con empate, victoria o matriz llena.
 * @return Retorna un "True" si es que un jugador gano o "False" si es que hay empate.
*/
bool Juego::juegoTerminado(){

    if(matrizLlena()){
        return true;
    }
    else if(victoria(1) == 1){
        return true;
    }
    else if(victoria(2) == 2){
        return true;
    }
    else{
        return false;
    } 
}

/**
 * Verifica el estado actual del juego basándose en el resultado de las funciones de victoria. 
 * @return Retorna un "1" si es que el jugador 1 gano o "-1" si es que el jugador 2 gano o "0" si es que no hay victoria.
*/
int Juego::verificarEstado(){
    if(victoria(1) == 1){
        return 1;
    }
    else if(victoria(2) == 2){
        return -1;
    }
    else {
        return 0;
    }
}

#endif
