#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <fstream> // para manejo de archivos
#include <cstdlib> // para usar el system
#include <string>
#include "Nodo.h"

using namespace std;

template <typename T>

/*
    Cola FIFO, el primer elemento en entrar es el primero en salir.
*/

class Cola
{
private:
    Nodo<T> *primero; // Frente de la cola
    Nodo<T> *ultimo;  // Final de la cola
public:
    Cola()
    {
        primero = nullptr;
        ultimo = nullptr;
    }

    bool estaVacia()
    {
        return (primero == nullptr && ultimo == nullptr);
    }

    // ver el inicio de la cola
    T *frente()
    {
        if (estaVacia())
        {
            return nullptr;
        }
        return primero->getDato();
    }

    // saber la cantidad de elementos en la cola
    int contar()
    {
        if (estaVacia())
        {
            return 0;
        }

        int i = 0;
        Nodo<T> *actual = primero;

        while (actual != nullptr)
        {
            i++;
            actual = actual->getSiguiente();
        }
        return i;
    }

    void encolar(T *dato)
    {
        Nodo<T> *nuevo = new Nodo<T>(dato);

        if (estaVacia())
        {
            primero = ultimo = nuevo;
        }
        else
        {
            // cuando agrego un nuevo nodo, debo enlazar el ultimo al nuevo nodo
            ultimo->setSiguiente(nuevo);
            ultimo = nuevo;
        }
    }

    // no es un void porque debe retornar el dato desencolado
    T *desencolar()
    {
        if (estaVacia())
        {
            return nullptr;
        }

        T *dato = primero->getDato();
        Nodo<T> *temporal = primero;

        if (primero == ultimo)
        {
            primero = ultimo = nullptr;
        }
        else
        {
            primero = primero->getSiguiente();
        }

        delete temporal;
        return dato;
    }

    void mostrar()
    {
        if (estaVacia())
        {
            cout << "La cola está vacía." << endl;
            return;
        }

        Nodo<T> *actual = primero;
        cout << "Elementos en la cola:" << endl;

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
            cout << "La cola está vacía, no se puede generar el reporte." << endl;
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

        actual = primero;
        while (actual != nullptr && actual->getSiguiente() != nullptr)
        {
            archivo << "\"" << actual->getDato()->getIdentificador() << "\" -> ";
            archivo << "\"" << actual->getSiguiente()->getDato()->getIdentificador() << "\";" << endl;
            actual = actual->getSiguiente();
        }

        archivo << "}" << endl;
        archivo.close();

        string comando = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
        system(comando.c_str());
        
        // Abrir el PNG automáticamente
        string comandoAbrir = "start \"\" \"" + nombreArchivo + ".png\"";
        system(comandoAbrir.c_str());
    }

    ~Cola()
    {
        while (!estaVacia())
        {
            T *dato = desencolar();
            delete dato;
        }
    }
};

#endif