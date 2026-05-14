#ifndef EQUIPAJE_H
#define EQUIPAJE_H

#include <string>
#include <iostream>
using namespace std;

class Equipaje
{
private:
    string numero_de_pasaporte; // Para identificar a quién pertenece
    string nombre_pasajero;     // Nombre del dueño
    int cantidad;               // Número de piezas de equipaje (equipaje_facturado)

public:
    Equipaje(string numero_de_pasaporte, string nombre_pasajero, int cantidad)
    {
        this->numero_de_pasaporte = numero_de_pasaporte;
        this->nombre_pasajero = nombre_pasajero;
        this->cantidad = cantidad;
    }

    string getNumeroDePasaporte() { return numero_de_pasaporte; }
    string getNombrePasajero() { return nombre_pasajero; }
    int getCantidad() { return cantidad; }

    void setNumeroDePasaporte(string numero_de_pasaporte) { this->numero_de_pasaporte = numero_de_pasaporte; }
    void setNombrePasajero(string nombre_pasajero) { this->nombre_pasajero = nombre_pasajero; }
    void setCantidad(int cantidad) { this->cantidad = cantidad; }

    string getIdentificador()
    {
        return numero_de_pasaporte; // el identificador es el pasaporte del dueño
    }

    void mostrar()
    {
        cout << "\n================ EQUIPAJE ================" << endl;
        cout << "Pasaporte Dueño ........ " << numero_de_pasaporte << endl;
        cout << "Nombre Pasajero ........ " << nombre_pasajero << endl;
        cout << "Cantidad Piezas ........ " << cantidad << endl;
        cout << "==========================================" << endl;
    }

    ~Equipaje() {}
};

#endif