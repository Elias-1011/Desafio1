#include "tablero.h"
#include <iostream>

using namespace std;

unsigned char** crearTablero(int alto, int bytes)
{
    unsigned char** tablero = new unsigned char*[alto];

    for(int i = 0; i < alto; i++)
    {
        tablero[i] = new unsigned char[bytes];

        for(int j = 0; j < bytes; j++)
        {
            tablero[i][j] = 0;
        }
    }

    return tablero;
}

void liberarTablero(unsigned char** tablero, int alto){
    for(int i = 0; i < alto; i++){
        delete[] tablero[i];
    }
    delete[] tablero;
}

void imprimirTablero(unsigned char** tablero, int alto, int bytes)
{
    for(int i = 0; i < alto; i++)
    {
        cout << "|";
        for(int j = 0; j < bytes; j++)
        {
            for(int b = 7; b >= 0; b--)
            {
                if(tablero[i][j] & (1 << b))
                    cout << "[]";
                else
                    cout << " .";
            }
        }
        cout << "|";
        cout << endl;
    }
}

void imprimirConPieza(
    unsigned char** tablero,
    unsigned char pieza[4],
    int fila,
    int columnaBit,
    int alto,
    int bytes
    )
{
    for(int i = 0; i < alto; i++)
    {
        cout << "|";

        for(int j = 0; j < bytes; j++)
        {
            unsigned char temp = tablero[i][j];

            int filaPieza = i - fila;

            //  SOLO SE IMPRIME SI LA PIEZA ESTÁ EN ESA FILA
            if(filaPieza >= 0 && filaPieza < 4 && pieza[filaPieza] != 0)
            {
                int byteBase       = columnaBit / 8;
                int desplazamiento = columnaBit % 8;

                if(j == byteBase)
                    temp |= (pieza[filaPieza] >> desplazamiento);

                if(desplazamiento != 0 && j == byteBase + 1)
                    temp |= (pieza[filaPieza] << (8 - desplazamiento));
            }

            for(int b = 7; b >= 0; b--)
                cout << ((temp & (1 << b)) ? "[]" : " .");
        }

        cout << "|" << endl;
    }
}

bool validar_ancho(int ancho){
    if((ancho >= 8) && (ancho % 8) == 0 ){
        return true;
    }
    else{
        return false;
    }
}


bool validar_alto(int alto){
    if(alto >= 8){
        return true;
    }
    else{
        return false;
    }
}

int ingresar_ancho(){
    int ancho;

    cout << "Ingrese el ancho (8, 16, 24, 32,...): ";
    cin >> ancho;
    return ancho;
}

int ingresar_alto(){
    int alto;

    cout << "Ingrese el alto (8, 9, 10,...): ";
    cin >> alto;
    return alto;
}

bool verificar_fila_llena(unsigned char** tablero, int fila, int bytes){
    for (int i = 0; i < bytes; i++){
        if(tablero[fila][i] != 255){
            return false;
        }
    }
    return true;
}

void eliminar_fila(unsigned char** tablero, int fila, int bytes){
    for (int i = 0; i < bytes; i++){
        tablero[fila][i] = 0;
    }
}

void limpiarFilasCompletas(unsigned char** tablero, int alto, int bytes){
    for(int i = 0; i < alto; i++){
        if(verificar_fila_llena(tablero, i, bytes)){
            bajar_fila(tablero, i, bytes);
            i--; //  revisar de nuevo la misma fila
        }
    }
}

void bajar_fila(unsigned char** tablero, int fila, int bytes){
    for(int i = fila; i > 0; i--){
        for(int j = 0; j < bytes; j++){
            tablero[i][j] = tablero[i-1][j];
        }
    }

    for(int j = 0; j < bytes; j++)
        tablero[0][j] = 0;
}

bool gameOver(unsigned char** tablero, int bytes){
    for(int j = 0; j < bytes; j++)
    {
        if(tablero[0][j] != 0)
            return true;
    }
    return false;
}

void limpiarTablero(unsigned char** tablero, int alto, int bytes)
{
    for(int i = 0; i < alto; i++)
        for(int j = 0; j < bytes; j++)
            tablero[i][j] = 0;
}

bool hayColision(
    unsigned char** tablero,
    unsigned char pieza[4],
    int fila,
    int columnaBit,
    int bytes,
    int altoTablero,
    int anchoPieza)
{
    if(columnaBit < 0) return true;
    if(columnaBit + anchoPieza > bytes * 8) return true;

    int byteBase       = columnaBit / 8;
    int desplazamiento = columnaBit % 8;

    for(int i = 0; i < 4; i++)
    {
        if(pieza[i] == 0) continue;

        if(fila + i >= altoTablero) return true;

        // Byte donde cae la parte izquierda
        if(byteBase < bytes)
        {
            unsigned char parte = (pieza[i] >> desplazamiento);
            if(tablero[fila + i][byteBase] & parte)
                return true;
        }

        // Byte donde desborda la parte derecha
        if(desplazamiento != 0 && byteBase + 1 < bytes)
        {
            unsigned char parte = (pieza[i] << (8 - desplazamiento));
            if(tablero[fila + i][byteBase + 1] & parte)
                return true;
        }
    }

    return false;
}
