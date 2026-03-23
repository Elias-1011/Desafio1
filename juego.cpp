#include "juego.h"
#include "tablero.h"
#include "piezas.h"
#include <iostream>
#include <cstdlib>

using namespace std;

char leerInput()
{
    char tecla;
    cin >> tecla;
    return tecla;
}

void ejecutarJuego()
{
    // ── Configurar tablero ─────────────────────────────────────────
    int ancho = 0, alto = 0;

    do {
        ancho = ingresar_ancho();
    } while(!validar_ancho(ancho));

    do {
        alto = ingresar_alto();
    } while(!validar_alto(alto));

    int bytes = ancho / 8;
    unsigned char** tablero = crearTablero(alto, bytes);

    int puntuacion = 0;

    // ── Loop principal ─────────────────────────────────────────────
    while(!gameOver(tablero, bytes))
    {
        unsigned char pieza[4]        = {};
        unsigned char respaldo[4]     = {};
        unsigned char piezaVisible[4] = {};
        int altoPieza     = 0;
        int anchoPieza    = 0;
        int tipoPieza     = rand() % 7;
        int filasVisibles = 1;

        crearPieza(tipoPieza, pieza, altoPieza, anchoPieza);

        int fila    = 0;
        int columna = (ancho - anchoPieza) / 2;
        bool activa = true;

        // ── Turno de la pieza ──────────────────────────────────────
        while(activa)
        {
            // Construir pieza visible
            for(int i = 0; i < 4; i++)
                piezaVisible[i] = (i < filasVisibles) ? pieza[i] : 0;

            imprimirConPieza(tablero, piezaVisible, fila, columna, alto, bytes);
            cout << "Puntuacion: " << puntuacion << "\n";
            cout << "a:izq  d:der  s:bajar  w:rotar  q:salir: ";

            char op = leerInput();

            if(op == 'd')
            {
                if(!hayColision(tablero, piezaVisible, fila, columna + 1,
                                 bytes, alto, anchoPieza))
                    moverPiezaHorizontal(columna, 1, ancho, anchoPieza);
            }
            else if(op == 'a')
            {
                if(!hayColision(tablero, piezaVisible, fila, columna - 1,
                                 bytes, alto, anchoPieza))
                    moverPiezaHorizontal(columna, -1, ancho, anchoPieza);
            }
            else if(op == 's')
            {
                if(filasVisibles < altoPieza)
                {
                    // Revelar siguiente fila
                    filasVisibles++;
                }
                else
                {
                    // Pieza completa — reconstruir visible
                    for(int i = 0; i < 4; i++)
                        piezaVisible[i] = (i < filasVisibles) ? pieza[i] : 0;

                    if(!hayColision(tablero, piezaVisible, fila + 1, columna,
                                     bytes, alto, anchoPieza))
                    {
                        // Puede bajar
                        bajarPieza(fila);
                    }
                    else
                    {
                        // No puede bajar — fijar
                        colocarPieza(tablero, piezaVisible, fila, columna, bytes, alto);

                        int lineas = 0;
                        for(int i = 0; i < alto; i++)
                            if(verificar_fila_llena(tablero, i, bytes))
                                lineas++;

                        limpiarFilasCompletas(tablero, alto, bytes);

                        if     (lineas == 1) puntuacion += 40;
                        else if(lineas == 2) puntuacion += 100;
                        else if(lineas == 3) puntuacion += 300;
                        else if(lineas == 4) puntuacion += 1200;

                        if(lineas > 0)
                            cout << ">> " << lineas << " fila(s) eliminada(s)!\n";

                        activa = false;
                    }
                }
            }
            else if(op == 'w')
            {
                // Solo rotar si pieza ya esta completa
                if(filasVisibles >= altoPieza)
                {
                    for(int i = 0; i < 4; i++) respaldo[i] = pieza[i];
                    int ah = altoPieza;
                    int aw = anchoPieza;

                    rotarPieza(pieza, altoPieza, anchoPieza);

                    if(hayColision(tablero, pieza, fila, columna,
                                    bytes, alto, anchoPieza))
                    {
                        for(int i = 0; i < 4; i++) pieza[i] = respaldo[i];
                        altoPieza  = ah;
                        anchoPieza = aw;
                    }
                    else
                    {
                        filasVisibles = altoPieza;
                    }
                }
            }
            else if(op == 'q')
            {
                cout << "Puntuacion final: " << puntuacion << "\n";
                liberarTablero(tablero, alto);
                return;
            }
        }
    }

    cout << "***  GAME OVER  ***\n";


    liberarTablero(tablero, alto);
}
