#include "tablero.h"
#include <iostream>

using namespace std;

void imprimirTablero(unsigned char** tablero, int alto, int bytes)
{
    for(int i = 0; i < alto; i++)
    {
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
        cout << endl;
    }
}
