#ifndef PIEZAS_H
#define PIEZAS_H

// 0 = I, 1 = O, 2 = T, 3 = S, 4 = Z, 5 = J, 6 = L

void crearPieza(
    int tipoPieza,
    unsigned char pieza[4],
    int &altoPieza,
    int &anchoPieza
    );

void colocarPieza(unsigned char** tablero, unsigned char pieza[4],
                  int fila, int columnaBit, int bytes, int altoTablero);


void moverPiezaHorizontal(
    int &columnaBit,
    int direccion,
    int anchoTablero,
    int anchoPieza
    );

void bajarPieza(int &fila);

void rotarPieza(unsigned char pieza[4], int &altoPieza, int &anchoPieza);

#endif
