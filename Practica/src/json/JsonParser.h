#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"
#include "../models/Avion.h"
#include "../models/Pasajero.h"

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

    // Leer archivo de pasajeros
    static vector<Pasajero *> cargarPasajeros(const string &rutaArchivo)
    {
        vector<Pasajero *> pasajeros;

        try
        {
            // Abrir archivo
            ifstream archivo(rutaArchivo);
            if (!archivo.is_open())
            {
                cerr << "Error: No se pudo abrir el archivo " << rutaArchivo << endl;
                return pasajeros;
            }

            // Parsear JSON
            json jsonData;
            archivo >> jsonData;
            archivo.close();

            // Verificar que sea un array
            if (!jsonData.is_array())
            {
                cerr << "Error: El archivo JSON no contiene un array" << endl;
                return pasajeros;
            }

            // Iterar sobre cada objeto en el array
            for (const auto &item : jsonData)
            {
                // Extraer datos del JSON
                string nombre = item.value("nombre", "");
                string nacionalidad = item.value("nacionalidad", "");
                string numero_de_pasaporte = item.value("numero_de_pasaporte", "");
                string vuelo = item.value("vuelo", "");
                int asiento = item.value("asiento", 0);
                string destino = item.value("destino", "");
                string origen = item.value("origen", "");
                int equipaje_facturado = item.value("equipaje_facturado", 0);

                // Crear nuevo pasajero
                Pasajero *pasajero = new Pasajero(
                    nombre,
                    nacionalidad,
                    numero_de_pasaporte,
                    vuelo,
                    asiento,
                    destino,
                    origen,
                    equipaje_facturado);

                pasajeros.push_back(pasajero);
            }

            cout << "Se cargaron " << pasajeros.size() << " pasajeros desde " << rutaArchivo << endl;
        }
        catch (const exception &e)
        {
            cerr << "Error al parsear JSON: " << e.what() << endl;
        }

        return pasajeros;
    }
};

#endif