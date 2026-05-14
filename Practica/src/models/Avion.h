#ifndef AVION_H // Directiva para evitar inclusiones múltiples
#define AVION_H // Directiva para evitar inclusiones múltiples

#include <string>
#include <iostream>
using namespace std;

class Avion
{
private:
    string vuelo;
    string numero_de_registro;
    string modelo;
    string fabricante;
    int ano_fabricacion;
    int capacidad;
    int peso_max_despegue;
    string aerolinea;
    string estado; // "Disponible" o "Mantenimiento"
public:
    Avion(string vuelo, string numero_de_registro, string modelo, string fabricante,
          int ano_fabricacion, int capacidad, int peso_max_despegue,
          string aerolinea, string estado)
    {

        this->vuelo = vuelo;
        this->numero_de_registro = numero_de_registro;
        this->modelo = modelo;
        this->fabricante = fabricante;
        this->ano_fabricacion = ano_fabricacion;
        this->capacidad = capacidad;
        this->peso_max_despegue = peso_max_despegue;
        this->aerolinea = aerolinea;
        this->estado = estado;
    };

    // Getters
    string getVuelo() { return vuelo; }
    string getNumeroDeRegistro() { return numero_de_registro; }
    string getModelo() { return modelo; }
    string getFabricante() { return fabricante; }
    int getAnoFabricacion() { return ano_fabricacion; }
    int getCapacidad() { return capacidad; }
    int getPesoMaxDespegue() { return peso_max_despegue; }
    string getAerolinea() { return aerolinea; }
    string getEstado() { return estado; }

    // Setters
    void setVuelo(string vuelo) { this->vuelo = vuelo; }
    void setNumeroDeRegistro(string numero_de_registro)
    {
        this->numero_de_registro = numero_de_registro;
    }
    void setModelo(string modelo) { this->modelo = modelo; }
    void setFabricante(string fabricante) { this->fabricante = fabricante; }
    void setAnoFabricacion(int ano_fabricacion) { this->ano_fabricacion = ano_fabricacion; }
    void setCapacidad(int capacidad) { this->capacidad = capacidad; }
    void setPesoMaxDespegue(int peso_max_despegue) { this->peso_max_despegue = peso_max_despegue; }
    void setAerolinea(string aerolinea) { this->aerolinea = aerolinea; }
    void setEstado(string estado) { this->estado = estado; }

    // Debo crear un metodo para las estructuras, es identificador unico, es rerquerido por las estructuras
    string getIdentificador()
    {
        return numero_de_registro;
    }

    // Metodo para mostrar la info
    void mostrar()
    {
        cout << "\n================== AVIÓN ==================" << endl;
        cout << "Vuelo ................. " << vuelo << endl;
        cout << "Registro .............. " << numero_de_registro << endl;
        cout << "Modelo ................ " << modelo << endl;
        cout << "Fabricante ............ " << fabricante << endl;
        cout << "Año Fabricación ....... " << ano_fabricacion << endl;
        cout << "Capacidad ............. " << capacidad << " pasajeros" << endl;
        cout << "Peso Máx Despegue ..... " << peso_max_despegue << " kg" << endl;
        cout << "Aerolínea ............. " << aerolinea << endl;
        cout << "Estado ................ " << estado << endl;
        cout << "===========================================" << endl;
    }

    ~Avion(){}
};

#endif