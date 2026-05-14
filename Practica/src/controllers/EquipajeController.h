#ifndef EQUIPAJECONTROLLER_H
#define EQUIPAJECONTROLLER_H

#include <iostream>
#include "../estructuras/Pila.h"
#include "../models/Equipaje.h"
#include "../models/Pasajero.h"

using namespace std;

/*
    Controlador para gestionar equipaje.
    - Pila de equipajes: solo pasajeros con equipaje_facturado > 0
    - Se crea equipaje cuando un pasajero sale de la cola de registro
*/

class EquipajeController
{
private:
    Pila<Equipaje> *pilaEquipaje;

public:
    EquipajeController()
    {
        pilaEquipaje = new Pila<Equipaje>();
    }

    // agregar equipaje
    void agregarEquipaje(Pasajero *pasajero)
    {
        if (pasajero == nullptr)
        {
            cout << "No se encontro pasajero " << endl;
            return;
        }

        if (pasajero->getEquipajeFacturado() <= 0)
        {
            cout << "El pasajero " << pasajero->getNombre() << " no tiene equipaje facturado." << endl;
            return;
        }

        // crear equipaje (objeto)
        Equipaje *equipaje = new Equipaje(
            pasajero->getNumeroDePasaporte(),
            pasajero->getNombre(),
            pasajero->getEquipajeFacturado());

        // agregar a la pila
        pilaEquipaje->push(equipaje);

        cout << "Equipaje de " << pasajero->getNombre()
             << " agregado a la pila. (" << pasajero->getEquipajeFacturado() << " equipajes)" << endl;
    }

    Pila<Equipaje> *getPilaEquipaje()
    {
        return pilaEquipaje;
    }

    void mostrarResumen()
    {
        cout << "\n================== RESUMEN DE EQUIPAJE ==================" << endl;
        cout << "Equipajes en pila .......... " << pilaEquipaje->contar() << " registro(s)" << endl;
        cout << "=========================================================" << endl;
    }

    ~EquipajeController()
    {
        delete pilaEquipaje;
    }
};

#endif