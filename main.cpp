#include <iostream>
#include "juego.h"
#include "main.h"
#include "piezas.h"
#include "tablero.h"

using namespace std;

int main(){

    int ancho;
    int alto;
    int bytes;
    int altoPieza, anchoPieza;

    ancho = ingresar_ancho();
    while(!validar_ancho(ancho)){
        cout << "Error: Ingrese un numero valido" << endl;
        ancho = ingresar_ancho();
    }
    alto = ingresar_alto();
    while(!validar_alto(alto)){
        cout << "Error: Ingrese un numero valido" << endl;
        alto = ingresar_alto();
    }


    bytes = ancho / 8;
    unsigned char** tablero;
    unsigned char pieza[4];

    tablero = crearTablero(alto, bytes);
    imprimirTablero(tablero, alto, bytes);
    crearPieza(0, pieza, altoPieza, anchoPieza);
    colocarPieza(tablero, pieza, 1, 3, bytes);

    imprimirTablero(tablero, alto, bytes);
    cout << endl;
    liberarTablero(tablero, alto);

    return 0;
}

