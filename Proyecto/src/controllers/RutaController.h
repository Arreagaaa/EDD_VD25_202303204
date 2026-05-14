#ifndef RUTACONTROLLER_H
#define RUTACONTROLLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../models/Ruta.h"
#include "../estructuras/Grafo.h"

using namespace std;

class RutaController
{
private:
    Grafo *grafo;

public:
    RutaController()
    {
        grafo = new Grafo();
    }

    void cargarDesdeArchivo(string rutaArchivo)
    {
        try
        {
            ifstream archivo(rutaArchivo);
            if (!archivo.is_open())
            {
                cout << "Error: No se pudo abrir el archivo " << rutaArchivo << endl;
                return;
            }

            string linea;
            int contador = 0;

            while (getline(archivo, linea))
            {
                // Formato: Origen/Destino/Distancia;
                size_t pos1 = linea.find('/');
                size_t pos2 = linea.find('/', pos1 + 1);
                size_t pos3 = linea.find(';');

                if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos)
                {
                    string origen = linea.substr(0, pos1);
                    string destino = linea.substr(pos1 + 1, pos2 - pos1 - 1);
                    string distanciaStr = linea.substr(pos2 + 1, pos3 - pos2 - 1);

                    int distancia = stoi(distanciaStr);

                    grafo->agregarRuta(origen, destino, distancia);
                    contador++;
                }
            }

            archivo.close();

            cout << "\n[+] Rutas cargadas exitosamente: " << contador << " rutas" << endl;
        }
        catch (const exception &e)
        {
            cout << "Error al cargar rutas: " << e.what() << endl;
        }
    }

    void calcularRutaMasCorta(string origen, string destino)
    {
        grafo->rutaMasCorta(origen, destino);
    }

    void mostrarRutas()
    {
        grafo->mostrar();
    }

    void reporteGrafo()
    {
        grafo->generarReporte("reports/grafo_rutas", "Grafo Dirigido - Rutas entre Ciudades");
    }

    ~RutaController()
    {
        delete grafo;
    }
};

#endif
