#ifndef NODO_H
#define NODO_H // Directiva para evitar inclusiones múltiples

#include <iostream>
using namespace std;

template <typename T> // Declaración de la clase plantilla Nodo

/*
    "T" es un parámetro de plantilla que representa el tipo de dato que almacenará el nodo.
    El T lo que devuelve es un nuevo tipo de dato. En vez de tener int, aquí tengo T, que lo que va a devolver es un puntero al tipo del nodo."
*/

class Nodo
{
private:
    T *dato;
    Nodo<T> *siguiente;
    Nodo<T> *anterior;

public:
    Nodo(T *dato)
    {
        this->dato = dato;
        this->siguiente = nullptr;
        this->anterior = nullptr;
    };

    T *getDato()
    {
        return this->dato;
    }

    void setDato(T *dato)
    {
        this->dato = dato;
    }

    // Nodo <T> es la forma de referirse a la clase plantilla dentro de su propia definición
    Nodo<T> *getSiguiente()
    {
        return this->siguiente;
    };

    void setSiguiente(Nodo<T> *siguiente)
    {
        this->siguiente = siguiente;
    };

    Nodo<T> *getAnterior()
    {
        return this->anterior;
    };

    void setAnterior(Nodo<T> *anterior)
    {
        this->anterior = anterior;
    };

    ~Nodo() {}
};

#endif