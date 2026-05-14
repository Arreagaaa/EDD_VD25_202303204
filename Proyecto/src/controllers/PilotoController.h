#ifndef PILOTOCONTROLLER_H
#define PILOTOCONTROLLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../json/json.hpp"
#include "../models/Piloto.h"
#include "../estructuras/ArbolAVL.h"
#include "../estructuras/TablaHash.h"
#include "AvionController.h"

class MatrizController; // forward declaration para evitar circular includes

using json = nlohmann::json;
using namespace std;

class PilotoController
{
private:
    ArbolAVL<Piloto> *arbolHorasVuelo;
    TablaHash<Piloto> *tablaPorID;
    MatrizController *matrizController;

public:
    PilotoController()
    {
        arbolHorasVuelo = new ArbolAVL<Piloto>();
        tablaPorID = new TablaHash<Piloto>(19);
        matrizController = nullptr;
    }

    void setMatrizController(MatrizController *mc)
    {
        matrizController = mc;
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

            int contador = 0;

            for (auto &item : jsonData)
            {
                Piloto *piloto = new Piloto();

                string nombreCompleto = item["nombre"].get<string>();

                // Separar nombre y apellido
                istringstream iss(nombreCompleto);
                string nombre, apellido;
                iss >> nombre; // Primera palabra es el nombre

                // El resto es el apellido
                string resto;
                apellido = "";
                while (iss >> resto)
                {
                    if (!apellido.empty())
                        apellido += " ";
                    apellido += resto;
                }

                // Si no hay apellido, usar el nombre completo
                if (apellido.empty())
                {
                    apellido = nombre;
                }

                piloto->setId(item["numero_de_id"].get<string>());
                piloto->setNombre(nombre);
                piloto->setApellido(apellido);
                piloto->setNacionalidad(item["nacionalidad"].get<string>());
                piloto->setHorasVuelo(item["horas_de_vuelo"].get<int>());

                // Si el JSON trae un vuelo asociado, lo guardamos
                if (item.contains("vuelo"))
                    piloto->setVuelo(item["vuelo"].get<string>());

                // Estado por defecto
                piloto->setEstado("Disponible");

                arbolHorasVuelo->insertar(piloto);

                Piloto *pilotoCopia = new Piloto();
                pilotoCopia->setId(piloto->getId());
                pilotoCopia->setNombre(piloto->getNombre());
                pilotoCopia->setApellido(piloto->getApellido());
                pilotoCopia->setNacionalidad(piloto->getNacionalidad());
                pilotoCopia->setHorasVuelo(piloto->getHorasVuelo());
                pilotoCopia->setEstado(piloto->getEstado());
                pilotoCopia->setVuelo(piloto->getVuelo());

                tablaPorID->insertar(piloto->getId(), pilotoCopia);

                contador++;
            }

            cout << "\n[+] Pilotos cargados exitosamente:" << endl;
            cout << "    - En Arbol AVL (por horas): " << contador << endl;
            cout << "    - En Tabla Hash (por ID): " << contador << endl;
        }
        catch (const exception &e)
        {
            cout << "Error al cargar pilotos: " << e.what() << endl;
        }
    }

    // Asignar todos los pilotos (según su campo vuelo) a la matriz usando la ciudad destino de los aviones
    void asignarPilotosAMatriz(AvionController *avionCtrl);

    Piloto *buscarPorID(string id)
    {
        return tablaPorID->buscar(id);
    }

    void darDeBaja(string id);

    string obtenerNombreCompleto(string id)
    {
        Piloto *piloto = tablaPorID->buscar(id);
        if (piloto != nullptr)
        {
            return piloto->getNombre() + " " + piloto->getApellido();
        }
        return "";
    }

    void recorridoPreorden()
    {
        arbolHorasVuelo->preorden();
    }

    void recorridoInorden()
    {
        arbolHorasVuelo->inorden();
    }

    void recorridoPostorden()
    {
        arbolHorasVuelo->postorden();
    }

    void reporteArbolAVL()
    {
        arbolHorasVuelo->generarReporte("reports/arbolAVL_pilotos", "Arbol AVL - Pilotos por Horas de Vuelo");
    }

    void reporteTablaHash()
    {
        tablaPorID->generarReporte("reports/tablaHash_pilotos", "Tabla Hash - Pilotos por ID");
    }

    void mostrarTablaHash()
    {
        cout << "\n=== Tabla Hash de Pilotos ===" << endl;
        tablaPorID->mostrar();
    }

    ~PilotoController()
    {
        delete arbolHorasVuelo;
        delete tablaPorID;
    }
};

#endif
