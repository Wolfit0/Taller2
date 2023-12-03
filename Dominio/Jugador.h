#ifndef jugador_h
#define jugador_h
#include <iostream>

using namespace std;
/**
 * Clase "Jugador" que representa a una persona en una partida de "Conecta 4".
*/
class Jugador
{
private:
    string nombre;
    int puntaje;

public:
    Jugador();

    string getNombre();
    void setNombre(string nombre);
    int getPuntaje();
    void sumarPuntaje(int puntos);

};
/**
 * Constructor de la clase "Jugador".
*/
Jugador::Jugador()
{
}
/*
	 * Muestra el atributo "nombre" de la clase "Jugador".
	 * @return Retorna String "nombre".
*/
string Jugador::getNombre(){
    return nombre;
}
/**
 * Modifica el atributo "nombre" de la clase "Jugador".
 * @param nombre El nuevo string "nombre" que reemplazará al anterior.
 */
void Jugador::setNombre(string nombre){
    this->nombre = nombre;
}

/*
	 * Muestra el atributo "Puntaje" de la clase "Jugador".
	 * @return Retorna String "Puntaje".
*/
int Jugador::getPuntaje(){
    return puntaje;
}
/**
 * Metodo que suma puntos al jugador al ganar partidas.
*/
void Jugador::sumarPuntaje(int puntos){
    this->puntaje += puntos;
}


#endif