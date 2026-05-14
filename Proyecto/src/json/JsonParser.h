#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"
#include "../models/Avion.h"

using json = nlohmann::json;
using namespace std;

/*
Este clase se encarga de leer archivos JSON y convertirlos en objetos Avion y Pasajero.
Trabaja con vectores de punteros
*/

class JsonParser
{
public:
    // Leer archivo JSON de aviones y retornar vector de punteros a Avion4
    static vector<Avion *> cargarAviones(const string &rutaArchivo) // static porque no necesito instanciar JsonParser
    {
        // vector<...> es un contenedor dinamico
        // Avion* es un tipo de dato, puntero a Avion
        vector<Avion *> aviones;
        try
        {
            // abrir el archivo
            ifstream archivo(rutaArchivo);
            if (!archivo.is_open())
            {
                // cerr es como imprimir en consola de errores
                cerr << "Error: No es posible abrir el archivo " << rutaArchivo << endl;
                return aviones;
            }

            // Parsear el JSON
            json jsonData;
            archivo >> jsonData; // leer el archivo en jsonData
            archivo.close();

            // Debo considerar y tratar como un array de objetos
            if (!jsonData.is_array())
            {
                cerr << "Error: El archivo JSON no contiene un array" << endl;
                return aviones;
            }

            // recorrer cada objeto en el array
            for (const auto &item : jsonData)
            {
                // Datos del JSON
                string vuelo = item.value("vuelo", "");
                string numero_de_registro = item.value("numero_de_registro", "");
                string modelo = item.value("modelo", "");
                string fabricante = item.value("fabricante", "");
                int ano_fabricacion = item.value("ano_fabricacion", 0);
                int capacidad = item.value("capacidad", 0);
                int peso_max_despegue = item.value("peso_max_despegue", 0);
                string aerolinea = item.value("aerolinea", "");
                string estado = item.value("estado", "Disponible");

                // Crear nuevo avion - HEAP
                Avion *avion = new Avion(
                    vuelo,
                    numero_de_registro,
                    modelo,
                    fabricante,
                    ano_fabricacion,
                    capacidad,
                    peso_max_despegue,
                    aerolinea,
                    estado);

                aviones.push_back(avion); // agregar el puntero al vector
            }

            cout << "Se cargaron " << aviones.size() << " aviones desde " << rutaArchivo << endl;
        }
        catch (const exception &e) // capturar cualquier error &e es para mostrar el error
        {
            cerr << "Error al leer el archivo JSON: " << e.what() << endl;
        }
        return aviones;
    }
};

#endif