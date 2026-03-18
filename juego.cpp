#include "tablero.h"
#include "piezas.h"
#include <iostream>

using namespace std;

char leerInput()
{
    char tecla;
    cin >> tecla;
    return tecla;
}

void ejecutarJuego()
{
    int alto = 10;
    int ancho = 16;
    int bytes = ancho / 8;

    unsigned char** tablero = crearTablero(alto, bytes);

    unsigned char pieza[4];
    int altoPieza, anchoPieza;

    int fila = 0;
    int columnaBit = 4;

    crearPieza(2, pieza, altoPieza, anchoPieza); // 2 = T

    while(true)
    {
        limpiarTablero(tablero, alto, bytes);

        if(fila + altoPieza <= alto)
            colocarPieza(tablero, pieza, fila, columnaBit, bytes);

        imprimirTablero(tablero, alto, bytes);

        cout << "A: izq | D: der | S: bajar | Q: salir\n";

        char tecla = leerInput();

        switch(tecla)
        {
        case 'a':
        case 'A':
            moverPiezaHorizontal(columnaBit, -1, ancho, anchoPieza);
            break;

        case 'd':
        case 'D':
            moverPiezaHorizontal(columnaBit, 1, ancho, anchoPieza);
            break;

        case 's':
        case 'S':
            if(fila + altoPieza < alto)
                fila++;
            break;

        case 'q':
        case 'Q':
            return;

        default:
            break;
        }
    }
}
