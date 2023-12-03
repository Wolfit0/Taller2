
#include <iostream>
#include "Jugador.h"
#include "Juego.h"

/**
 * Clase "Partida" que contiene un partida jugada entre un jugador y otro jugador.
*/
class Partida
{
private:
    string nombrePartida;
    Juego* juego;
    Jugador* jugador1;
    Jugador* jugador2;
    
public:
    Partida();
    string getNombrePartida();
    void setNombrePartida(string nombre);
    Juego* getJuego();
    void setJuego(Juego* juego);
    Jugador* getJugador1();
    void setJugador1(Jugador* jugador);
    Jugador* getJugador2();
    void setJugador2(Jugador* Jugador);
    

};

/**
 * Constructor de la clase "Partida".
*/
Partida::Partida()
{
    this->nombrePartida = "";
    this->juego = nullptr;
    this->jugador1 = nullptr;
    this->jugador2 = nullptr;
}

/**
 * Metodo que mostrará el nombre de la partida jugada.
*/
string Partida::getNombrePartida(){
    return this->nombrePartida;
}

/**
 * Modifica el atributo "nombrePartida" de la clase "Partida".
 * @param nombre El nuevo string "nombrePartida" que reemplazará al anterior.
 */
void Partida::setNombrePartida(string nombre){
    this->nombrePartida = nombre;
}

/**
 * Metodo que mostrará la instancia de Juego.
*/
Juego* Partida::getJuego(){
    return juego;
}

/**
 * Modifica el atributo "juego" de la clase "Partida".
 * @param juego El nuevo Juego "juego" que reemplazará al anterior.
 */
void Partida::setJuego(Juego* juego){
    this->juego = juego;
}

/**
 * Metodo que mostrará la instancia de jugador1.
*/
Jugador* Partida::getJugador1(){
    return this->jugador1;
}

/**
 * Modifica el atributo "jugador1" de la clase "Partida".
 * @param jugador El nuevo Jugador "jugador1" que reemplazará al anterior.
 */
void Partida::setJugador1(Jugador* jugador){
    this->jugador1 = jugador;
}

/**
 * Metodo que mostrará la instancia de jugador2.
*/
Jugador* Partida::getJugador2(){
    return this->jugador2;
}

/**
 * Modifica el atributo "jugador2" de la clase "Partida".
 * @param jugador El nuevo Jugador "jugador2" que reemplazará al anterior.
 */
void Partida::setJugador2(Jugador* jugador){
    this->jugador2 = jugador;
}



