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

void bajar_fila(unsigned char** tablero, int fila, int bytes){
    for(int i = fila; i > 0; i--){
        tablero[i] = tablero[i-1];
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


