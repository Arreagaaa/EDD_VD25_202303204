#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Nodo.h"

using namespace std;

/*
Lista doble enlazada, con punteros al siguiente y al anterior.
Sirve para pasajeros, ordenados por vuelo y asiento.
*/

template <typename T>

class listaDoble
{
private:
    Nodo<T> *primero;
    Nodo<T> *ultimo;

public:
    listaDoble()
    {
        primero = nullptr;
        ultimo = nullptr;
    };

    bool estaVacia()
    {
        return (primero == nullptr && ultimo == nullptr);
    }

    // Insertar, por #vuelo, luego por asiento
    void insertar(T *dato)
    {
        Nodo<T> *nuevo = new Nodo<T>(dato);

        if (estaVacia())
        {
            primero = ultimo = nuevo;
            return;
        }

        // Buscar posición correcta
        Nodo<T> *actual = primero;

        while (actual != nullptr)
        {
            // comparar: primero por vuelo, luego por asiento
            // el vuelo del nuevo, es menor al vuelo del actual?, si es así, insertar antes
            // si son iguales, comparar por asiento
            if (dato->getVuelo() < actual->getDato()->getVuelo() ||
                (dato->getVuelo() == actual->getDato()->getVuelo() &&
                 dato->getAsiento() < actual->getDato()->getAsiento()))
            {
                // insertar antes de actual
                if (actual == primero)
                {
                    nuevo->setSiguiente(primero);
                    primero->setAnterior(nuevo);
                    primero = nuevo;
                }
                else
                {
                    // insertar en medio
                    nuevo->setAnterior(actual->getAnterior());
                    nuevo->setSiguiente(actual);
                    actual->getAnterior()->setSiguiente(nuevo);
                    actual->setAnterior(nuevo);
                }
                return;
            }
            actual = actual->getSiguiente();
        }

        // insertar al final
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        ultimo = nuevo;
    }

    // Buscar por pasaporte
    T *buscar(string pasaporte)
    {
        if (estaVacia())
        {
            return nullptr;
        }

        Nodo<T> *actual = primero;

        while (actual != nullptr)
        {
            if (actual->getDato()->getPasaporte() == pasaporte)
            {
                return actual->getDato();
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }

    // Eliminar por pasaporte
    bool eliminar(string pasaporte)
    {
        if (estaVacia())
        {
            return false;
        }

        Nodo<T> *actual = primero;

        while (actual != nullptr)
        {
            if (actual->getDato()->getPasaporte() == pasaporte)
            {
                // único nodo
                if (actual == primero && actual == ultimo)
                {
                    delete actual->getDato();
                    delete actual;
                    primero = ultimo = nullptr;
                    return true;
                }
                // eliminar el primero
                else if (actual == primero)
                {
                    primero = primero->getSiguiente();
                    primero->setAnterior(nullptr);
                    delete actual->getDato();
                    delete actual;
                    return true;
                }
                // eliminar el último
                else if (actual == ultimo)
                {
                    ultimo = ultimo->getAnterior();
                    ultimo->setSiguiente(nullptr);
                    delete actual->getDato();
                    delete actual;
                    return true;
                }
                // nodo intermedio
                else
                {
                    actual->getAnterior()->setSiguiente(actual->getSiguiente());
                    actual->getSiguiente()->setAnterior(actual->getAnterior());
                    delete actual->getDato();
                    delete actual;
                    return true;
                }
            }
            actual = actual->getSiguiente();
        }
        return false;
    }

    // Contar elementos
    int contar()
    {
        if (estaVacia())
        {
            return 0;
        }

        int contador = 0;
        Nodo<T> *actual = primero;

        while (actual != nullptr)
        {
            contador++;
            actual = actual->getSiguiente();
        }

        return contador;
    }

    // Mostrar lista
    void mostrar()
    {
        if (estaVacia())
        {
            cout << "La lista está vacía." << endl;
            return;
        }

        Nodo<T> *actual = primero;
        cout << "Contenido de la lista doble:" << endl;

        while (actual != nullptr)
        {
            actual->getDato()->mostrar();
            cout << "---" << endl;
            actual = actual->getSiguiente();
        }
    }

    void generarReporte(string nombreArchivo, string titulo)
    {
        if (estaVacia())
        {
            cout << "La lista está vacía, no se puede generar el reporte." << endl;
            return;
        }

        ofstream archivo;
        archivo.open(nombreArchivo + ".dot", ios::out);

        archivo << "digraph G {" << endl;
        archivo << "rankdir=LR;" << endl;
        archivo << "node [shape=record];" << endl;
        archivo << "label=\"" << titulo << "\";" << endl;
        archivo << "labelloc=\"t\";" << endl;
        archivo << endl;

        Nodo<T> *actual = primero;
        while (actual != nullptr)
        {
            archivo << "\"" << actual->getDato()->getIdentificador() << "\" [label=\"";
            archivo << actual->getDato()->getIdentificador();
            archivo << "\"];" << endl;
            actual = actual->getSiguiente();
        }

        archivo << endl;

        // Enlaces hacia adelante
        actual = primero;
        while (actual != nullptr && actual->getSiguiente() != nullptr)
        {
            archivo << "\"" << actual->getDato()->getIdentificador() << "\" -> ";
            archivo << "\"" << actual->getSiguiente()->getDato()->getIdentificador() << "\";" << endl;
            actual = actual->getSiguiente();
        }

        archivo << endl;

        // Enlaces hacia atrás
        actual = ultimo;
        while (actual != nullptr && actual->getAnterior() != nullptr)
        {
            archivo << "\"" << actual->getDato()->getIdentificador() << "\" -> ";
            archivo << "\"" << actual->getAnterior()->getDato()->getIdentificador() << "\" [style=dashed, color=blue];" << endl;
            actual = actual->getAnterior();
        }

        archivo << "}" << endl;
        archivo.close();

        string comando = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
        system(comando.c_str());
        
        // Abrir el PNG automáticamente
        string comandoAbrir = "start \"\" \"" + nombreArchivo + ".png\"";
        system(comandoAbrir.c_str());
    }

    ~listaDoble()
    {
        while (!estaVacia())
        {
            Nodo<T> *temporal = primero;
            primero = primero->getSiguiente();
            delete temporal->getDato();
            delete temporal;
        }
    }
};

#endif