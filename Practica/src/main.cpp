#include <iostream>
#include "Menu.h"

using namespace std;

int main()
{
    // Activar soporte UTF-8 para Windows
    system("chcp 65001 > nul");

    cout << "==============================================================" << endl;
    cout << "               FACULTAD DE INGENIERÍA                         " << endl;
    cout << "                ESTRUCTURAS DE DATOS                          " << endl;
    cout << "                Carné: 202303204                              " << endl;
    cout << "==============================================================" << endl;

    Menu menu;
    menu.ejecutar();

    return 0;
}
