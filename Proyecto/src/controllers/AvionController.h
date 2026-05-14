#ifndef AVIONCONTROLLER_H
#define AVIONCONTROLLER_H

#include <iostream>
#include <fstream>
#include <string>
#include "../json/json.hpp"
#include "../models/Avion.h"
#include "../estructuras/ArbolB.h"
#include "../estructuras/ListaCircularDoble.h"

using json = nlohmann::json;
using namespace std;

class AvionController
{
private:
    ArbolB<Avion> *arbolDisponibles;
    ListaCircularDoble<Avion> *listaMantenimiento;

public:
    AvionController()
    {
        arbolDisponibles = new ArbolB<Avion>(5);
        listaMantenimiento = new ListaCircularDoble<Avion>();
    }

    void cargarDesdeJSON(string rutaArchivo)
    {
        try
        {
            ifstream archivo(rutaArchivo);
            if (!archivo.is_open())
            {
                cout << "Error: No se pudo abrir el archivo " << rutaArchivo << endl;
                return;
            }

            json jsonData;
            archivo >> jsonData;
            archivo.close();

            int contadorDisponibles = 0;
            int contadorMantenimiento = 0;

            for (auto &item : jsonData)
            {
                Avion *avion = new Avion();

                // Campos obligatorios
                avion->setVuelo(item["vuelo"].get<string>());
                avion->setNumeroDeRegistro(item["numero_de_registro"].get<string>());
                avion->setModelo(item["modelo"].get<string>());
                avion->setCapacidad(item["capacidad"].get<int>());
                avion->setAerolinea(item["aerolinea"].get<string>());
                if (item.contains("ciudad_destino"))
                    avion->setCiudadDestino(item["ciudad_destino"].get<string>());
                else
                    avion->setCiudadDestino("");
                avion->setEstado(item["estado"].get<string>());

                // Campos opcionales (con valores por defecto)
                if (item.contains("fabricante"))
                {
                    avion->setFabricante(item["fabricante"].get<string>());
                }
                else
                {
                    avion->setFabricante("N/A");
                }

                if (item.contains("ano_fabricacion"))
                {
                    avion->setAnoFabricacion(item["ano_fabricacion"].get<int>());
                }
                else
                {
                    avion->setAnoFabricacion(0);
                }

                if (item.contains("peso_max_despegue"))
                {
                    avion->setPesoMaxDespegue(item["peso_max_despegue"].get<int>());
                }
                else
                {
                    avion->setPesoMaxDespegue(0);
                }

                if (avion->getEstado() == "Disponible")
                {
                    arbolDisponibles->insertar(avion);
                    contadorDisponibles++;
                }
                else if (avion->getEstado() == "Mantenimiento")
                {
                    listaMantenimiento->insertar(avion);
                    contadorMantenimiento++;
                }
            }

            cout << "\n[+] Aviones cargados exitosamente:" << endl;
            cout << "    - Disponibles (Arbol B): " << contadorDisponibles << endl;
            cout << "    - Mantenimiento (Lista Circular): " << contadorMantenimiento << endl;
        }
        catch (const exception &e)
        {
            cout << "Error al cargar aviones: " << e.what() << endl;
        }
    }

    void moverAvion(string numeroRegistro, string nuevoEstado)
    {
        if (nuevoEstado == "Disponible")
        {
            // Mover de mantenimiento a disponibles
            Avion *avion = listaMantenimiento->extraer(numeroRegistro);
            if (avion != nullptr)
            {
                // Si el avión ya existe en el árbol (por ejemplo original), actualizar su estado y eliminar la copia extraída
                Avion *existente = arbolDisponibles->buscar(numeroRegistro);
                if (existente != nullptr)
                {
                    existente->setEstado("Disponible");
                    // la copia extraída ya no es necesaria
                    delete avion;
                }
                else
                {
                    avion->setEstado("Disponible");
                    arbolDisponibles->insertar(avion);
                }
                cout << "[+] Avion " << numeroRegistro << " movido a Disponibles" << endl;
            }
            else
            {
                // Tal vez ya está en el árbol pero con estado diferente
                Avion *existente = arbolDisponibles->buscar(numeroRegistro);
                if (existente != nullptr)
                {
                    existente->setEstado("Disponible");
                    cout << "[+] Avion " << numeroRegistro << " actualizado a Disponibles en Arbol" << endl;
                }
                else
                {
                    cout << "[-] Avion " << numeroRegistro << " no encontrado en Mantenimiento" << endl;
                }
            }
        }
        else if (nuevoEstado == "Mantenimiento")
        {
            // Extraer el avion del arbol de disponibles y moverlo a la lista de mantenimiento
            Avion *avion = arbolDisponibles->extraer(numeroRegistro);
            if (avion != nullptr)
            {
                avion->setEstado("Mantenimiento");
                listaMantenimiento->insertar(avion);
                cout << "[+] Avion " << numeroRegistro << " movido a Mantenimiento" << endl;
            }
            else
            {
                cout << "[-] Avion " << numeroRegistro << " no encontrado en Disponibles" << endl;
            }
        }
    }

    void reporteDisponibles()
    {
        arbolDisponibles->generarReporte("reports/arbolB_disponibles", "Arbol B - Aviones Disponibles");
    }

    void reporteMantenimiento()
    {
        listaMantenimiento->generarReporte("reports/lista_mantenimiento", "Lista Circular - Aviones en Mantenimiento");
    }

    void mostrarDisponibles()
    {
        cout << "\n=== Aviones Disponibles ===" << endl;
        arbolDisponibles->recorrido();
    }

    void mostrarMantenimiento()
    {
        cout << "\n=== Aviones en Mantenimiento ===" << endl;
        listaMantenimiento->mostrar();
    }

    // Obtener ciudad destino a partir del código de vuelo
    string obtenerCiudadDestinoPorVuelo(const string &vuelo)
    {
        Avion *a = arbolDisponibles->buscarPorVuelo(vuelo);
        if (a != nullptr)
            return a->getCiudadDestino();
        a = listaMantenimiento->buscarPorVuelo(vuelo);
        if (a != nullptr)
            return a->getCiudadDestino();
        return string();
    }

    ~AvionController()
    {
        delete arbolDisponibles;
        delete listaMantenimiento;
    }
};

#endif
