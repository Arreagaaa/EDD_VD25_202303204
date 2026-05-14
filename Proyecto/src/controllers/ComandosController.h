#ifndef COMANDOSCONTROLLER_H
#define COMANDOSCONTROLLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "AvionController.h"
#include "PilotoController.h"
#include "MatrizController.h"

using namespace std;

class ComandosController
{
private:
    AvionController *avionController;
    PilotoController *pilotoController;
    MatrizController *matrizController;

public:
    ComandosController(AvionController *ac, PilotoController *pc, MatrizController *mc)
    {
        avionController = ac;
        pilotoController = pc;
        matrizController = mc;
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

            cout << "\n=== Procesando comandos ===" << endl;

            while (getline(archivo, linea))
            {
                if (linea.empty())
                    continue;

                procesarComando(linea);
                contador++;
            }

            archivo.close();

            cout << "\n[+] Comandos procesados: " << contador << endl;
        }
        catch (const exception &e)
        {
            cout << "Error al procesar comandos: " << e.what() << endl;
        }
    }

    void procesarComando(string comando)
    {
        string c = comando;
        for (char &ch : c)
            if (ch == ';')
                ch = ' ';
        for (char &ch : c)
            if (ch == ',' || ch == '(' || ch == ')')
                ch = ' ';

        istringstream issNorm(c);
        string token0;
        if (!(issNorm >> token0))
            return;

        if (token0 == "MantenimientoAviones")
        {
            string estadoToken, numeroRegistro;
            issNorm >> estadoToken >> numeroRegistro;

            string estadoFinal = estadoToken;
            if (estadoToken == "Ingreso")
                estadoFinal = "Mantenimiento";
            else if (estadoToken == "Salida")
                estadoFinal = "Disponible";

            cout << "\n[CMD] " << comando << endl;
            avionController->moverAvion(numeroRegistro, estadoFinal);
            return;
        }
        else if (token0 == "AsignarVuelo")
        {
            string idPiloto, numeroVuelo, ciudad;
            issNorm >> idPiloto >> numeroVuelo;
            // Leer el resto de la linea como ciudad (soporta espacios)
            getline(issNorm, ciudad);
            // trim espacios al inicio y final
            auto trim = [](string &s)
            {
                // left trim
                size_t start = s.find_first_not_of(" \t\r\n");
                if (start == string::npos)
                {
                    s = "";
                    return;
                }
                size_t end = s.find_last_not_of(" \t\r\n");
                s = s.substr(start, end - start + 1);
            };
            trim(ciudad);

            cout << "\n[CMD] " << comando << endl;
            matrizController->asignarVuelo(idPiloto, numeroVuelo, ciudad);
            return;
        }
        else if (token0 == "DarDeBaja")
        {
            string idPiloto;
            issNorm >> idPiloto;
            if (idPiloto.empty())
            {
                size_t pos1 = comando.find('(');
                size_t pos2 = comando.find(')');
                if (pos1 != string::npos && pos2 != string::npos)
                    idPiloto = comando.substr(pos1 + 1, pos2 - pos1 - 1);
            }
            if (!idPiloto.empty())
            {
                cout << "\n[CMD] " << comando << endl;

                // Eliminar de estructuras de pilotos (PilotoController se encargará de actualizar la matriz)
                pilotoController->darDeBaja(idPiloto);

                return;
            }
        }
        else
        {
            cout << "[-] Comando no reconocido: " << comando << endl;
        }
    }

    ~ComandosController() {}
};

#endif
