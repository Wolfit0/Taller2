#include <iostream>
#include <vector>
#include "Dominio/Juego.h"
#include "Dominio/Jugador.h"
#include "Dominio/Minimax.h"
#include "Dominio/Partida.h"
 
using namespace std;

class nodoPartida
{
private:
    Partida* partida;
    nodoPartida* siguiente;
    nodoPartida* anterior;
public:
    nodoPartida();
    ~nodoPartida();
    nodoPartida* getSiguiente();
    void setSiguiente(nodoPartida* nodo);
    nodoPartida* getAnterior();
    void setAnterior(nodoPartida* nodo);
    Partida* getPartida();
    void setPartida(Partida* game);
};

nodoPartida::nodoPartida()
{
}

nodoPartida::~nodoPartida()
{
}

nodoPartida* nodoPartida::getSiguiente(){
    return this->siguiente;
}

void nodoPartida::setSiguiente(nodoPartida* nodo){
    this->siguiente = nodo;
}

nodoPartida* nodoPartida::getAnterior(){
    return this->anterior;
}

void nodoPartida::setAnterior(nodoPartida* nodo){
    this->anterior = nodo;
}

Partida* nodoPartida::getPartida(){
    return this->partida;
}

void nodoPartida::setPartida(Partida* game){
    this->partida = game;
}




class listaPartida {
private:
    nodoPartida* cabeza;
    nodoPartida* cola;
    int cantidad;

public:
    listaPartida();
    ~listaPartida();

    void agregarPartida(Partida* game);
    void mostrarPartidas();
};

listaPartida::listaPartida(){
    this->cantidad = 0;
}

listaPartida::~listaPartida() {
}

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

Partida* partidaContraIA(int contGame);
Partida* partidaContraJugador(int contGame);
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
            Partida* gameVsIA = partidaContraIA(contGame);
            if(gameVsIA->getNombrePartida() == "Partida guardada"){
                gameReanuder = gameVsIA;
                
            }
            else{
                gamesSave->agregarPartida(gameVsIA);
            }
        }
        else if(opcion == 2){
            Partida* gamerVSPlayer = partidaContraJugador(contGame);
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
           cout<<gameReanuder->getJuego()<<endl;
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



Partida* partidaContraIA(int contGame){

    int nivel = nivelDeDificultad();
    while(nivel == 0){
        nivel = nivelDeDificultad();
    }
    Jugador* jugador1 = ingresarDatosJugador();

    Juego* juego = new Juego();
    Minimax* minimax = new Minimax();

    cout<<"MAPA DEL JUEGO"<<endl;
    juego->dibujarJuego();
    cout<<"----------------------------------------"<<endl;
    while(!juego->juegoTerminado() && !juego->matrizLlena()){
        int columnaJugador1;
        cout<<"Turno del jugador humano. Ingrese columna (0-6): ";
        cin>>columnaJugador1;

        juego->hacerMovimiento(1, columnaJugador1-1);
        juego->dibujarJuego();
        cout<<"----------------------------------------"<<endl;
        if(juego->juegoTerminado() || juego->matrizLlena()){
            break;
        }

        int columnaJugador2 = minimax->minimax(juego, 0, 5, 2);
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

    Partida* partida = new Partida();
    partida->setJuego(juego);
    partida->setJugador1(jugador1);
    partida->setJugador2(nullptr);
    string nameGame = "Partida "+contGame;
    contGame++;
    return partida;


}

Partida* partidaContraJugador(int contGame){

    Jugador* jugador1 = ingresarDatosJugador();
    Jugador* jugador2 = ingresarDatosJugador();

    Juego* juego = new Juego();
    
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
    
    Partida* partida = new Partida();
    partida->setJuego(juego);
    partida->setJugador1(jugador1);
    partida->setJugador2(jugador2);
    string nameGame = "Partida "+contGame;
    contGame++;
    return partida;

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
