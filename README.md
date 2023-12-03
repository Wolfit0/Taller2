# Taller2

La implementación del algoritmo minimax, en la clase "Minimax" existe el metodo "minimax". En ella
se agrego por parametros la instancia del mapa de "Conecta 4", un valor int llamado "nivelActualArbol" que es el que representa
en que nivel del arbol está, otr valor int llamado "limiteMaximoArbol" y un ultimo int que representaría la ficha de la "IA".

Dentro del metodo, tenemos un ciclo "for" que simula la cantidad de sucesos que tenemos en nuestro juego actual(desde un inicio de
una partida, el jugador "Humano" es el que comienza la primera jugada). Dentro del ciclo, tenemos recursividad del metodo "menorPunaje",
su función es hacer una simulación de turno entre los jugadores(humanovsIA), el "menorPuntaje" tiene recursividad de "mejorPuntaje" dando la representación 
de las diferentes posibilidades de juego para ambos jugadores, explorando el árbol de juego y determinando la mejor jugada posible para el jugador actual en cada nivel.






















