#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>
#include <iostream>
using namespace std;

class Pasajero
{
private:
    string nombre;
    string nacionalidad;
    string numero_de_pasaporte;
    string vuelo;
    int asiento;
    string destino;
    string origen;
    int equipaje_facturado;

public:
    Pasajero(string nombre, string nacionalidad, string numero_de_pasaporte,
             string vuelo, int asiento, string destino, string origen,
             int equipaje_facturado)
    {
        this->nombre = nombre;
        this->nacionalidad = nacionalidad;
        this->numero_de_pasaporte = numero_de_pasaporte;
        this->vuelo = vuelo;
        this->asiento = asiento;
        this->destino = destino;
        this->origen = origen;
        this->equipaje_facturado = equipaje_facturado;
    }

    string getNombre() { return nombre; }
    string getNacionalidad() { return nacionalidad; }
    string getNumeroDePasaporte() { return numero_de_pasaporte; }
    string getVuelo() { return vuelo; }
    int getAsiento() { return asiento; }
    string getDestino() { return destino; }
    string getOrigen() { return origen; }
    int getEquipajeFacturado() { return equipaje_facturado; }

    void setNombre(string nombre) { this->nombre = nombre; }
    void setNacionalidad(string nacionalidad)
    {
        this->nacionalidad = nacionalidad;
    }
    void setNumeroDePasaporte(string numero_de_pasaporte)
    {
        this->numero_de_pasaporte = numero_de_pasaporte;
    }
    void setVuelo(string vuelo) { this->vuelo = vuelo; }
    void setAsiento(int asiento) { this->asiento = asiento; }
    void setDestino(string destino) { this->destino = destino; }
    void setOrigen(string origen) { this->origen = origen; }
    void setEquipajeFacturado(int equipaje_facturado) { this->equipaje_facturado = equipaje_facturado; }

    string getIdentificador()
    {
        return numero_de_pasaporte;
    }

    string getPasaporte()
    {
        return numero_de_pasaporte;
    }

    void mostrar()
    {
        cout << "\n================ PASAJERO ================" << endl;
        cout << "Nombre .................. " << nombre << endl;
        cout << "Nacionalidad ............ " << nacionalidad << endl;
        cout << "Pasaporte ............... " << numero_de_pasaporte << endl;
        cout << "Vuelo .................... " << vuelo << endl;
        cout << "Asiento .................. " << asiento << endl;
        cout << "Destino .................. " << destino << endl;
        cout << "Origen ................... " << origen << endl;
        cout << "Equipaje Facturado ....... " << equipaje_facturado << " pieza(s)" << endl;
        cout << "==========================================" << endl;
    }

    ~Pasajero(){}
};

#endif