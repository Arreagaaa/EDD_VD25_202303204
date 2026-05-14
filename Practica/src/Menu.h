#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include "controllers/AvionController.h"
#include "controllers/PasajeroController.h"
#include "controllers/EquipajeController.h"
#include "controllers/MovimientosController.h"

using namespace std;

class Menu
{
private:
    AvionController *avionCtrl;
    PasajeroController *pasajeroCtrl;
    EquipajeController *equipajeCtrl;

    void menuReportes();
    vector<string> buscarArchivos(const string &directorio, const string &extension, const string &filtroNombre = "");
    string seleccionarArchivo(const string &tipoArchivo, const string &extension);

public:
    Menu();
    ~Menu();

    void mostrarMenuPrincipal();
    void ejecutar();
};

#endif