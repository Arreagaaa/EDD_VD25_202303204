#ifndef MATRIZCONTROLLER_H
#define MATRIZCONTROLLER_H

#include <iostream>
#include <string>
#include "../estructuras/MatrizDispersa.h"
#include "../models/Piloto.h"
#include "PilotoController.h"

using namespace std;

class MatrizController
{
private:
    MatrizDispersa *matriz;
    PilotoController *pilotoController;

public:
    MatrizController(PilotoController *pc)
    {
        matriz = new MatrizDispersa();
        pilotoController = pc;
    }

    void asignarVuelo(string idPiloto, string numeroVuelo, string ciudadDestino)
    {
        Piloto *piloto = pilotoController->buscarPorID(idPiloto);
        if (piloto != nullptr)
        {
            // Insertar: ID Piloto, Vuelo, Ciudad
            matriz->insertar(idPiloto, numeroVuelo, ciudadDestino);
            cout << "[+] Vuelo asignado: Piloto " << idPiloto
                 << " -> Vuelo " << numeroVuelo
                 << " -> Ciudad " << ciudadDestino << endl;
        }
        else
        {
            cout << "[-] Piloto con ID " << idPiloto << " no encontrado" << endl;
        }
    }

    void eliminarPilotoDeMatriz(string idPiloto)
    {
        matriz->eliminarPiloto(idPiloto);
    }

    void mostrarMatriz()
    {
        matriz->mostrar();
    }

    void reporteMatriz()
    {
        matriz->generarReporte("reports/matriz_dispersa", "Matriz Dispersa - Vuelos y Ciudades");
    }

    ~MatrizController()
    {
        delete matriz;
    }
};

#endif
