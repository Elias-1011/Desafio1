#include "piezas.h"

void crearPieza(
    int tipoPieza,
    unsigned char pieza[4],
    int &altoPieza,
    int &anchoPieza
    )
{
    for(int i = 0; i < 4; i++)
        pieza[i] = 0;

    switch(tipoPieza)
    {
    case 0: // I
        pieza[0] = 0b11110000;
        altoPieza = 1;
        anchoPieza = 4;
        break;

    case 1: // O
        pieza[0] = 0b01100000;
        pieza[1] = 0b01100000;
        altoPieza = 2;
        anchoPieza = 2;
        break;

    case 2: // T
        pieza[0] = 0b00100000;
        pieza[1] = 0b01110000;
        altoPieza = 2;
        anchoPieza = 3;
        break;

    case 3: // S
        pieza[0] = 0b01100000;
        pieza[1] = 0b11000000;
        altoPieza = 2;
        anchoPieza = 3;
        break;

    case 4: // Z
        pieza[0] = 0b11000000;
        pieza[1] = 0b01100000;
        altoPieza = 2;
        anchoPieza = 3;
        break;

    case 5: // J
        pieza[0] = 0b00100000;
        pieza[1] = 0b00100000;
        pieza[2] = 0b01100000;
        altoPieza = 3;
        anchoPieza = 2;
        break;

    case 6: // L
        pieza[0] = 0b01000000;
        pieza[1] = 0b01000000;
        pieza[2] = 0b01100000;
        altoPieza = 3;
        anchoPieza = 2;
        break;
    }
}
void colocarPieza(
    unsigned char** tablero,
    unsigned char pieza[4],
    int fila,
    int columnaBit,
    int bytes
    )
{
    int byteBase = columnaBit / 8;
    int desplazamiento = columnaBit % 8;

    for(int i = 0; i < 4; i++)
    {
        if(pieza[i] == 0) continue;

        if(byteBase < bytes)
        {
            tablero[fila + i][byteBase] |= (pieza[i] >> desplazamiento);
        }
        if(desplazamiento != 0 && byteBase + 1 < bytes)
        {
            tablero[fila + i][byteBase + 1] |= (pieza[i] << (8 - desplazamiento));
        }
    }
}

void moverPiezaHorizontal(
    int &columnaBit,
    int direccion,
    int anchoTablero,
    int anchoPieza
    )
{
    int nuevaColumna = columnaBit + direccion;

    // límites del tablero
    if(nuevaColumna < 0)
        return;

    if(nuevaColumna + anchoPieza > anchoTablero)
        return;

    columnaBit = nuevaColumna;
}

void bajarPieza(int &fila)
{
    fila++;
}



