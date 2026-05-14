#ifndef PASAJEROCONTROLLER_H
#define PASAJEROCONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include "../estructuras/Cola.h"
#include "../estructuras/ListaDoble.h"
#include "../models/Pasajero.h"
#include "../json/JsonParser.h"

using namespace std;

/*

Controlador para gestionar pasajeros.
 - cola de registro
 - uso de la lista doble para pasajeros ya registrados
 - cargar pasajeros desde JSON
*/

class PasajeroController
{
private:
    Cola<Pasajero> *colaRegistro;         // Cola de llegada (no registrados)
    listaDoble<Pasajero> *listaPasajeros; // Lista ordenada (ya registrados)
public:
    PasajeroController(/* args */)
    {
        colaRegistro = new Cola<Pasajero>();
        listaPasajeros = new listaDoble<Pasajero>();
    };

    // Carga de pasajeros desde el json
    // debo agregarlos a la cola de registro
    void cargarDatos(const string &ruta)
    {
        cout << "Cargando pasajeros desde" << ruta << "..." << endl;

        vector<Pasajero *> pasajeros = JsonParser::cargarPasajeros(ruta);

        if (pasajeros.empty())
        {
            cout << "No se cargaron pasajeros." << endl;
            return;
        }
        else
        {
            // encolar cada pasajero en la cola de registro
            for (Pasajero *pasajero : pasajeros)
            {
                colaRegistro->encolar(pasajero);
            }

            cout << pasajeros.size() << " pasajeros agregados a la cola de registro." << endl;
        }
    }

    // Procesar el siguiente pasajero
    // flujo de la cola a la lista doble
    Pasajero *procesarSiguiente()
    {
        if (colaRegistro->estaVacia())
        {
            cout << "No hay pasajeros en la cola de registro." << endl;
            return nullptr;
        }

        // Desencolar pasajero
        Pasajero *pasajero = colaRegistro->desencolar();

        if (pasajero == nullptr)
        {
            cout << "Error al desencolar pasajero." << endl;
            return nullptr;
        }

        // Insertar en lista doble (~ordenado por vuelo y asiento)
        listaPasajeros->insertar(pasajero);

        cout << "\nPasajero registrado" << endl;
        cout << "Nombre ............... " << pasajero->getNombre() << endl;
        cout << "Pasaporte ............ " << pasajero->getPasaporte() << endl;
        cout << "Vuelo ................ " << pasajero->getVuelo() << endl;
        cout << "Asiento .............. " << pasajero->getAsiento() << endl;
        cout << "--------------------------------------------------------" << endl;

        return pasajero; // Retornar para que EquipajeController lo use
    }

    // consultar pasajero por pasaporte en la lista doble
    Pasajero *consultaPasaporte(const string &numeroPasaporte)
    {
        if (listaPasajeros->estaVacia())
        {
            cout << "No hay pasajeros registrados." << endl;
            return nullptr;
        }

        Pasajero *pasajero = listaPasajeros->buscar(numeroPasaporte);

        if (pasajero == nullptr)
        {
            cout << "Pasajero con pasaporte " << numeroPasaporte << " no encontrado." << endl;
            return nullptr;
        }

        return pasajero;
    }

    Cola<Pasajero> *getColaRegistro()
    {
        return colaRegistro;
    }

    listaDoble<Pasajero> *getListaPasajeros()
    {
        return listaPasajeros;
    }

    void mostrarResumen()
    {
        cout << "\n================== RESUMEN DE PASAJEROS ==================" << endl;
        cout << "En cola de registro ........ " << colaRegistro->contar() << " pasajero(s)" << endl;
        cout << "Ya registrados ............. " << listaPasajeros->contar() << " pasajero(s)" << endl;
        cout << "==========================================================" << endl;
    }

    ~PasajeroController()
    {
        delete colaRegistro;
        delete listaPasajeros;
    };
};

#endif