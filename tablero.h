#ifndef TABLERO_H
#define TABLERO_H

unsigned char** crearTablero(int alto, int bytes);

void liberarTablero(unsigned char** tablero, int alto);

void imprimirTablero(unsigned char** tablero, int alto, int bytes);

bool validar_ancho(int ancho);
bool validar_alto(int alto);

int ingresar_ancho();
int ingresar_alto();

bool verificar_fila_llena(unsigned char** tablero, int fila, int bytes);

void eliminar_fila(unsigned char** tablero, int fila, int bytes);

void limpiarFilasCompletas(unsigned char** tablero, int alto, int bytes);

void bajar_fila(unsigned char** tablero, int fila, int bytes);

bool gameOver(unsigned char** tablero, int bytes);

void limpiarTablero(unsigned char** tablero, int alto, int bytes);

void imprimirConPieza(
    unsigned char** tablero,
    unsigned char pieza[4],
    int fila,
    int columna,
    int alto,
    int bytes);

bool hayColision(unsigned char** tablero, unsigned char pieza[4],
                 int fila, int columnaBit, int bytes,
                 int altoTablero, int anchoPieza);

#endif

