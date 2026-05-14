#ifndef PILOTO_H
#define PILOTO_H

#include <iostream>
#include <string>

using namespace std;

class Piloto
{
private:
    string id;
    string nombre;
    string apellido;
    string nacionalidad;
    int horasVuelo;
    string estado;
    string vuelo; // codigo de vuelo asignado

public:
    void setVuelo(string v) { this->vuelo = v; }
    string getVuelo() { return vuelo; }

public:
    Piloto()
    {
        id = "";
        nombre = "";
        apellido = "";
        nacionalidad = "";
        horasVuelo = 0;
        estado = "Disponible";
    }

    Piloto(string id, string nombre, string apellido, string nacionalidad, int horasVuelo, string estado)
    {
        this->id = id;
        this->nombre = nombre;
        this->apellido = apellido;
        this->nacionalidad = nacionalidad;
        this->horasVuelo = horasVuelo;
        this->estado = estado;
    }

    // Getters
    string getId() { return id; }
    string getNombre() { return nombre; }
    string getApellido() { return apellido; }
    string getNacionalidad() { return nacionalidad; }
    int getHorasVuelo() { return horasVuelo; }
    string getEstado() { return estado; }

    // Setters
    void setId(string id) { this->id = id; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setApellido(string apellido) { this->apellido = apellido; }
    void setNacionalidad(string nacionalidad) { this->nacionalidad = nacionalidad; }
    void setHorasVuelo(int horasVuelo) { this->horasVuelo = horasVuelo; }
    void setEstado(string estado) { this->estado = estado; }

    void mostrar()
    {
        cout << "ID: " << id << " | Nombre: " << nombre << " " << apellido;
        cout << " | Horas: " << horasVuelo << " | Vuelo: " << vuelo << " | Estado: " << estado << endl;
    }

    ~Piloto() {}
};

#endif