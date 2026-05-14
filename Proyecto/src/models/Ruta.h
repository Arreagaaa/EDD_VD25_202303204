#ifndef RUTA_H
#define RUTA_H

#include <iostream>
#include <string>

using namespace std;

class Ruta
{
private:
    string origen;
    string destino;
    int distancia;

public:
    Ruta()
    {
        origen = "";
        destino = "";
        distancia = 0;
    }

    Ruta(string origen, string destino, int distancia)
    {
        this->origen = origen;
        this->destino = destino;
        this->distancia = distancia;
    }

    // Getters
    string getOrigen() { return origen; }
    string getDestino() { return destino; }
    int getDistancia() { return distancia; }

    // Setters
    void setOrigen(string origen) { this->origen = origen; }
    void setDestino(string destino) { this->destino = destino; }
    void setDistancia(int distancia) { this->distancia = distancia; }

    void mostrar()
    {
        cout << origen << " -> " << destino << " (" << distancia << " km)" << endl;
    }

    ~Ruta() {}
};

#endif