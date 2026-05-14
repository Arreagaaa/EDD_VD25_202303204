#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Nodo.h"

using namespace std;

template <typename T>

class Pila
{
private:
    Nodo<T> *cima;

public:
    Pila(/* args */)
    {
        cima = nullptr;
    };

    bool estaVacia()
    {
        return (cima == nullptr);
    }

    // Ver CIMA y contar elementos
    T *top()
    {
        if (estaVacia())
        {
            return nullptr;
        }
        return cima->getDato();
    }

    int contar()
    {
        if (estaVacia())
        {
            return 0;
        }

        int contador = 0;
        Nodo<T> *actual = cima;

        while (actual != nullptr)
        {
            contador++;
            actual = actual->getSiguiente();
        }

        return contador;
    }

    void push(T *dato)
    {
        Nodo<T> *nuevo = new Nodo<T>(dato);

        if (estaVacia())
        {
            cima = nuevo;
        }
        else
        {
            nuevo->setSiguiente(cima);
            cima = nuevo;
        }
    }

    T *pop()
    {
        if (estaVacia())
        {
            return nullptr;
        }

        T *dato = cima->getDato();   // gurado el dato antes de borrar
        Nodo<T> *temporal = cima;    // guardo el nodo a eliminar
        cima = cima->getSiguiente(); // movemos cima al siguiente nodo

        delete temporal; // eliminamos el nodo superior
        return dato;     // retornamos el dato almacenado
    }

    void mostrar()
    {
        if (estaVacia())
        {
            cout << "La pila está vacía." << endl;
            return;
        }

        Nodo<T> *actual = cima;
        cout << "Contenido de la pila:" << endl;

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
            cout << "La pila está vacía, no se puede generar el reporte." << endl;
            return;
        }

        ofstream archivo;
        archivo.open(nombreArchivo + ".dot", ios::out);

        archivo << "digraph G {" << endl;
        archivo << "rankdir=TB;" << endl;
        archivo << "node [shape=record];" << endl;
        archivo << "label=\"" << titulo << "\";" << endl;
        archivo << "labelloc=\"t\";" << endl;
        archivo << endl;

        Nodo<T> *actual = cima;
        while (actual != nullptr)
        {
            archivo << "\"" << actual->getDato()->getIdentificador() << "\" [label=\"";
            archivo << actual->getDato()->getIdentificador();
            archivo << "\"];" << endl;
            actual = actual->getSiguiente();
        }

        archivo << endl;

        actual = cima;
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

    ~Pila()
    {
        while (!estaVacia())
        {
            pop();
        }
    };
};

#endif