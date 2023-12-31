#include <iostream>
#include <vector>
#include "Dominio/Juego.h"
#include "Dominio/Jugador.h"
#include "Dominio/Minimax.h"
#include "Dominio/Partida.h"
 
using namespace std;
/**
 * La implementación de las clases "nodoPartida" y "listaPartida" fueron agregados en el main por un problema que llevaba desde el
 * primer taller, así que para no perder tiempo, hice estas dos clases en el main.
*/


/**
 * Clase que representa un nodo de la lista de partidas
*/
class nodoPartida
{
private:
    Partida* partida;
    nodoPartida* siguiente;
    nodoPartida* anterior;
public:
    nodoPartida();
    nodoPartida* getSiguiente();
    void setSiguiente(nodoPartida* nodo);
    nodoPartida* getAnterior();
    void setAnterior(nodoPartida* nodo);
    Partida* getPartida();
    void setPartida(Partida* game);
};
/**
 * Constructor por defecto
*/
nodoPartida::nodoPartida()
{
}
/**
 * Metodo para obtener el nodo siguiente
*/
nodoPartida* nodoPartida::getSiguiente(){
    return this->siguiente;
}

/**
 * Modifica el atributo "siguiente" de la clase "nodoPartida".
 * @param nodo El nuevo nodoPartida "siguiente" que reemplazará al anterior.
 */
void nodoPartida::setSiguiente(nodoPartida* nodo){
    this->siguiente = nodo;
}

/**
 * Metodo para obtener el nodo anterior
*/
nodoPartida* nodoPartida::getAnterior(){
    return this->anterior;
}

/**
 * Modifica el atributo "anterior" de la clase "nodoPartida".
 * @param nodo El nuevo nodoPartida "anterior" que reemplazará al anterior.
 */
void nodoPartida::setAnterior(nodoPartida* nodo){
    this->anterior = nodo;
}

/**
 * Metodo para obtener el nodo partida
*/
Partida* nodoPartida::getPartida(){
    return this->partida;
}

/**
 * Modifica el atributo "partida" de la clase "nodoPartida".
 * @param game El nuevo nodoPartida "game" que reemplazará al anterior.
 */
void nodoPartida::setPartida(Partida* game){
    this->partida = game;
}

/**
 * Clase que representa una lista de partidas
*/
class listaPartida {
private:
    nodoPartida* cabeza;
    nodoPartida* cola;
    int cantidad;

public:
    listaPartida();
    void agregarPartida(Partida* game);
    void mostrarPartidas();
};

/**
 * Constructor por defecto
*/
listaPartida::listaPartida(){
    this->cantidad = 0;
}
/**
 * Método para agregar una nueva partida a la lista
*/
void listaPartida::agregarPartida(Partida* game) {
    nodoPartida* nuevoNodo = new nodoPartida();
    nuevoNodo->setPartida(game);

    if (!cabeza) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->setSiguiente(nuevoNodo);
        nuevoNodo->setAnterior(cola);
        cola = nuevoNodo;
    }
    cantidad++;
}
/**
 * Método para mostrar las partidas en la lista
*/
void listaPartida::mostrarPartidas() {
    nodoPartida* actual = cabeza;

    while (actual) {
        if(actual->getPartida() == nullptr){
            cout<<"No hay partidas guardadas"<<endl;
        }
        else{
            cout<<"Nombre de la Partida: "<<actual->getPartida()->getNombrePartida()<<endl;
            actual = actual->getSiguiente();
        }
        
    }
}

Partida* partidaContraIA(int contGame,Partida* partida);
Partida* partidaContraJugador(int contGame,Partida* partida);
string nickParaJugador();
bool verificarJugada(int columna);
int nivelDeDificultad();
Jugador* ingresarDatosJugador();
bool guardar();

int main() {
    
    bool on = true;
    listaPartida* gamesSave = new listaPartida();
    Partida* gameReanuder;
    int contGame = 0;
    while(on){
        int opcion;
        cout<<"-----BIENVENIDO-----"<<endl;
        cout<<"1.- Partida contra IA"<<endl;
        cout<<"2.- Partida contra jugador"<<endl;
        cout<<"3.- Mostrar partidas guardadas"<<endl;
        cout<<"4.- Reanudar partida"<<endl;
        cout<<"5.- Cerrar sistema"<<endl;
        cout<<"Elija una opcion: ";
        cin>>opcion;

        if(opcion == 1){
            Partida* gameVsIA = partidaContraIA(contGame,nullptr);
            if(gameVsIA->getNombrePartida() == "Partida guardada"){
                gameReanuder = gameVsIA;
                
            }
            else{
                gamesSave->agregarPartida(gameVsIA);
            }
        }
        else if(opcion == 2){
            Partida* gamerVSPlayer = partidaContraJugador(contGame,nullptr);
            if(gamerVSPlayer->getNombrePartida() == "Partida guardada"){
                gameReanuder = gamerVSPlayer;
            }
            else{
                gamesSave->agregarPartida(gamerVSPlayer);
            }
        }
        else if(opcion == 3){
            gamesSave->mostrarPartidas();
        }
        else if(opcion == 4){
            if(gameReanuder == nullptr){
                cout<<"No ha guardado ningun juego"<<endl;
            }
            else{
                if(gameReanuder->getJugador2() == nullptr){
                    partidaContraIA(contGame,gameReanuder);
                }
            }
           
        }
        else if(opcion == 5){
            cout<<"Cerrando sistema....."<<endl;
            on = false;
        }
        else{
            cout<<"Opcion no disponible......"<<endl;
        }

    }

    return 0;
}



Partida* partidaContraIA(int contGame,Partida* partida){

    int nivel = nivelDeDificultad();
    while(nivel == 0){
        nivel = nivelDeDificultad();
    }
    Jugador* jugador1 = ingresarDatosJugador();
    Juego* juego;
    if(partida != nullptr){
        juego = partida->getJuego();
    }
    else{
        juego = new Juego();
    }
    Minimax* minimax = new Minimax();

    cout<<"MAPA DEL JUEGO"<<endl;
    juego->dibujarJuego();
    cout<<"----------------------------------------"<<endl;
    while(!juego->juegoTerminado() && !juego->matrizLlena()){
        int columnaJugador1;
        cout<<"Turno del jugador humano. Ingrese columna (0-6): "<<endl;
        cin>>columnaJugador1;

        juego->hacerMovimiento(1, columnaJugador1-1);
        juego->dibujarJuego();
        cout<<"----------------------------------------"<<endl;
        if(juego->juegoTerminado() || juego->matrizLlena()){
            break;
        }

        int columnaJugador2 = minimax->minimax(juego, 0, nivel, 2);
        cout<<"Turno de la IA. Ingreos columna: "<<columnaJugador2<<endl;
        juego->hacerMovimiento(2, columnaJugador2);

        juego->dibujarJuego();
        cout<<"----------------------------------------"<<endl;

        if(guardar()){
            Partida* partida = new Partida();
            partida->setJuego(juego);
            partida->setJugador1(jugador1);
            partida->setJugador2(nullptr);
            partida->setNombrePartida("Partida guardada");
            return partida;
        }
    }

    int resultado = juego->verificarEstado();
    if(resultado == 1){
        cout<<"¡Felicidades! El jugador humano gana."<<endl;
        jugador1->sumarPuntaje(100);
    } 
    else if(resultado == -1){
        cout<<"La IA gana. ¡Inténtalo de nuevo!"<<endl;
    } 
    else{
        cout<<"El juego termina en empate."<<endl;
    }

    Partida* gamesave = new Partida();
    gamesave->setJuego(juego);
    gamesave->setJugador1(jugador1);
    gamesave->setJugador2(nullptr);
    string nameGame = "Partida "+contGame;
    contGame++;
    return gamesave;


}

Partida* partidaContraJugador(int contGame,Partida* partida){

    Jugador* jugador1 = ingresarDatosJugador();
    Jugador* jugador2 = ingresarDatosJugador();

    Juego* juego;
    if(partida != nullptr){
        juego = partida->getJuego();
    }
    else{
        juego = new Juego();
    }
    
    cout<<"MAPA DEL JUEGO"<<endl;
    juego->dibujarJuego();
    cout<<"----------------------------------------"<<endl;
    while(!juego->juegoTerminado() && !juego->matrizLlena()){
        int columnaJugador1;
        cout<<"Turno del jugador "<<jugador1->getNombre()<<" Ingrese columna (0-6): "<<endl;
        cin>>columnaJugador1;

        juego->hacerMovimiento(1, columnaJugador1-1);
        juego->dibujarJuego();
        cout<<"----------------------------------------"<<endl;
        if(juego->juegoTerminado() || juego->matrizLlena()){
            break;
        }

        int columnaJugador2;
        cout<<"Turno del jugador "<<jugador2->getNombre()<<" Ingrese columna (0-6): "<<endl;
        cin>>columnaJugador2;
        juego->hacerMovimiento(2, columnaJugador2-1);

        juego->dibujarJuego();
        cout<<"----------------------------------------"<<endl;

        if(guardar()){
            Partida* partida = new Partida();
            partida->setJuego(juego);
            partida->setJugador1(jugador1);
            partida->setJugador2(nullptr);
            partida->setNombrePartida("Partida guardada");
            return partida;
        }
    }

    int resultado = juego->verificarEstado();
    if(resultado == 1){
        cout<<"¡Felicidades! El jugador "<<jugador1->getNombre()<<" gana."<<endl;
        jugador1->sumarPuntaje(100);
        
    } 
    else if(resultado == -1){
        cout<<"¡Felicidades! El jugador "<<jugador2->getNombre()<<" gana."<<endl;
        jugador2->sumarPuntaje(100);
    } 
    else{
        cout<<"El juego termina en empate."<<endl;
    }
    
    Partida* gamesave = new Partida();
    gamesave->setJuego(juego);
    gamesave->setJugador1(jugador1);
    gamesave->setJugador2(jugador2);
    string nameGame = "Partida "+contGame;
    contGame++;
    return gamesave;

}

int nivelDeDificultad(){
    int nivel;
    cout<<"------NIVELES DE DIFICULTAD-----"<<endl;
    cout<<"1.- facil "<<endl;
    cout<<"2.- medio "<<endl;
    cout<<"3.- Dificil "<<endl;
    cout<<"Elija el nivel de dificultad: ";
    cin>> nivel;

    if(nivel == 1){
        return 5;
    }
    else if (nivel == 2)
    {
        return 10;
    }
    else if (nivel == 3)
    {
        return 15;
    }
    
    else {
        return 0;
    }
    

    
}

Jugador* ingresarDatosJugador(){
    Jugador* jugador = new Jugador();
    string name;
    cout<<"-----Bienvenido-----"<<endl;
    cout<<"Ingrese nombre para jugador : "<<endl;
    cin>>name;
    jugador->setNombre(name);
    return jugador;
}

bool guardar(){
    int opcion;
    cout<<"¿Quiere guardar la partida?"<<endl;
    cout<<"1.- Si"<<endl;
    cout<<"2.- No"<<endl;
    cin>>opcion;

    if(opcion == 1){
        return true;
    }
    else if(opcion == 2){
        return false;
    }
    return false;
}
