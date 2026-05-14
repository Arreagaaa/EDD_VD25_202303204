#ifndef AVIONCONTROLLER_H
#define AVIONCONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include "../estructuras/ListaCircularDoble.h"
#include "../models/Avion.h"
#include "../json/JsonParser.h"

using namespace std;

/*
    Controlador para gestionar aviones
    Listo:
    - mantener listas circular dobles (disp y mant)
    - cargar aviones desde JSON
    - mover / cambiar estado de aviones
    TODO:
    - test y reportes de la lista ciruclar doble
*/

class AvionController
{
private:
    ListaCircularDoble<Avion> *avionesDisponibles;   // puntero a la lista de aviones disponibles
    ListaCircularDoble<Avion> *avionesMantenimiento; // puntero a la lista de aviones en mantenimiento
public:
    AvionController()
    {
        avionesDisponibles = new ListaCircularDoble<Avion>();
        avionesMantenimiento = new ListaCircularDoble<Avion>();
    }

    // cargar aviones desde el json
    void cargarDatos(const string &rutaArchivo)
    {
        cout << "Cargando aviones desde " << rutaArchivo << "..." << endl;

        vector<Avion *> aviones = JsonParser::cargarAviones(rutaArchivo);

        if (aviones.empty())
        {
            cout << "No se cargaron aviones." << endl;
            return;
        }

        for (Avion *avion : aviones) // recorrer cada avion de aviones
        {
            if (avion->getEstado() == "Disponible")
            {
                avionesDisponibles->insertar(avion);
            }
            else if (avion->getEstado() == "Mantenimiento")
            {
                avionesMantenimiento->insertar(avion);
            }
            else
            {
                // y si no conozco el estado?, lo pongo en disponibles por defecto
                cout << "Estado desconocido para avión " << avion->getNumeroDeRegistro()
                     << ". Se asigna a Disponibles por defecto." << endl;
                avion->setEstado("Disponible");
                avionesDisponibles->insertar(avion);
            }
        }

        cout << "Se cargaron " << aviones.size() << " aviones en total." << endl;

        // puedo ver los disponibles y mantenimiento con los getters o con contar
        cout << " - Disponibles: " << avionesDisponibles->contar() << endl;
        cout << " - Mantenimiento: " << avionesMantenimiento->contar() << endl;
    }

    // Funcionalidades para mover aviones entre listas
    // funcion mover a mantenimiento - retorna un bool si se pudo o no
    bool moverMantenimiento(const string &numeroRegistro)
    {
        // Extraer (no eliminar) el avion de disponibles
        Avion *avion = avionesDisponibles->extraer(numeroRegistro);

        if (avion == nullptr)
        {
            cout << "No se encontró el avión " << numeroRegistro << " en Disponibles." << endl;
            return false;
        }

        // Cambiar estado
        avion->setEstado("Mantenimiento");

        // Insertar en mantenimiento
        avionesMantenimiento->insertar(avion);
        cout << "Avión " << numeroRegistro << " movido a Mantenimiento." << endl;
        return true;
    }

    // funcion mover a disponible - retorna un bool si se pudo o no
    bool moverDisponible(const string &numeroRegistro)
    {
        // Extraer (no eliminar) el avion de mantenimiento
        Avion *avion = avionesMantenimiento->extraer(numeroRegistro);

        if (avion == nullptr)
        {
            cout << "No se encontró el avión " << numeroRegistro << " en Mantenimiento." << endl;
            return false;
        }

        // Cambiar estado
        avion->setEstado("Disponible");

        // Insertar en disponibles
        avionesDisponibles->insertar(avion);
        cout << "Avión " << numeroRegistro << " movido a Disponibles." << endl;
        return true;
    }

    // Getters para las listas (para reportes)
    ListaCircularDoble<Avion> *getAvionesDisponibles()
    {
        return avionesDisponibles;
    }

    ListaCircularDoble<Avion> *getAvionesMantenimiento()
    {
        return avionesMantenimiento;
    }

    void mostrarResumen()
    {
        cout << "\n================== RESUMEN DE AVIONES ==================" << endl;
        cout << "Disponibles .............. " << avionesDisponibles->contar() << " avión(es)" << endl;
        cout << "En mantenimiento ......... " << avionesMantenimiento->contar() << " avión(es)" << endl;
        cout << "========================================================" << endl;
    }

    ~AvionController()
    {
        delete avionesDisponibles;
        delete avionesMantenimiento;
    }
};

#endif