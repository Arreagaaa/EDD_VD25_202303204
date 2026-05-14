#ifndef MOVIMIENTOSCONTROLLER_H
#define MOVIMIENTOSCONTROLLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "PasajeroController.h"
#include "EquipajeController.h"
#include "AvionController.h"

using namespace std;

/*
    Procesar el archivo movimientos (comandos)
    Comandos soportados:
    - IngresoEquipajes
    - MantenimientoAviones, ingreso, xxxx
    - MantenimientoAviones, salida, XXXX
*/

class MovimientosController
{
public:
    // Procesar archivo de movs
    static void procesarArchivo(const string &rutaArchivo,
                                PasajeroController *pasajeroCtrl,
                                EquipajeController *equipajeCtrl,
                                AvionController *avionCtrl)
    {
        cout << " Procesando movimientos desde " << rutaArchivo << "..." << endl;

        ifstream archivo(rutaArchivo);
        if (!archivo.is_open())
        {
            cerr << "No se pudo abrir el archivo " << rutaArchivo << endl;
            return;
        }

        string linea;
        int i = 0; // numero de lineas procesadas
        int c = 0;

        while (getline(archivo, linea)) // getline es para leer lineas completas
        {
            i++;

            // ignorar lineas vacias
            if (linea.empty() || linea == "\r" || linea == "\n")
            {
                continue;
            }

            // remover espacios y saltos de linea
            // erase quita caracteres especificos
            linea.erase(remove(linea.begin(), linea.end(), '\r'), linea.end());
            linea.erase(remove(linea.begin(), linea.end(), '\n'), linea.end());
            linea.erase(remove(linea.begin(), linea.end(), ' '), linea.end());

            if (linea.empty())
            {
                continue;
            }

            // procesando comando
            // XXXXXCtrl quiere decir puntero a controlador
            if (procesarComando(linea, pasajeroCtrl, equipajeCtrl, avionCtrl))
            {
                c++;
            }
            else
            {
                cout << "No se pudo procesar la línea " << i << ": " << linea << endl;
            }
        }

        archivo.close();

        cout << "\nProcesamiento completado. " << c << " comandos ejecutados." << endl;
    }

private:
    static bool procesarComando(const string &comando,
                                PasajeroController *pasajeroCtrl,
                                EquipajeController *equipajeCtrl,
                                AvionController *avionCtrl)
    {
        if (comando == "IngresoEquipajes;")
        {
            return procesarIngresoEquipajes(pasajeroCtrl, equipajeCtrl);
        }

        // Verificar si es MantenimientoAviones
        if (comando.find("MantenimientoAviones,") == 0)
        {
            return procesarMantenimientoAviones(comando, avionCtrl);
        }

        return false; // Comando no reconocido
    }

    // Procesos: IngresoEquipajes y MantenimientoAviones
    static bool procesarIngresoEquipajes(
        PasajeroController *pasajeroCtrl,
        EquipajeController *equipajeCtrl)
    {
        cout << "\nIngresoEquipajes" << endl;

        // Procesar siguiente pasajero (sale de cola, entra a lista)
        Pasajero *pasajero = pasajeroCtrl->procesarSiguiente();

        if (pasajero == nullptr)
        {
            return false; // No había pasajeros en cola
        }

        // Si el pasajero tiene equipaje, agregarlo a la pila
        equipajeCtrl->agregarEquipaje(pasajero);

        return true;
    }

    static bool procesarMantenimientoAviones(const string &comando, AvionController *avionCtrl)
    {
        // Parsear comando
        stringstream ss(comando); // para separar por comas
        string segmento;
        vector<string> segmentos;

        while (getline(ss, segmento, ','))
        {
            segmentos.push_back(segmento);
        }

        // verificar formato correcto
        if (segmentos.size() != 3)
        {
            cout << "Formato incorrecto para MantenimientoAviones: " << comando << endl;
            return false;
        }

        string accion = segmentos[1]; // "Ingreso" o "Salida"
        string numeroRegistro = segmentos[2];

        // validaciones (quitar el ; al final)
        numeroRegistro.erase(remove(numeroRegistro.begin(), numeroRegistro.end(), ';'), numeroRegistro.end());

        cout << "Acción: " << accion << ", Avión: " << numeroRegistro << endl;

        // ejecutar accion - mover entre listas
        if (accion == "Ingreso")
        {
            return avionCtrl->moverMantenimiento(numeroRegistro);
        }
        else if (accion == "Salida")
        {
            return avionCtrl->moverDisponible(numeroRegistro);
        }
        else
        {
            cout << "Acción desconocida para MantenimientoAviones: " << accion << endl;
            return false;
        }
    }
};

#endif