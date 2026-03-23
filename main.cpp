#include <iostream>
#include "juego.h"
#include "main.h"
#include "piezas.h"
#include "tablero.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    ejecutarJuego();
    return 0;
}
