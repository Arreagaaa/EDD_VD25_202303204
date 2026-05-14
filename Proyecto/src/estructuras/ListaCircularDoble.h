#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Nodo.h"

using namespace std;

template <typename T>
class ListaCircularDoble
{
private:
    Nodo<T> *primero;
    Nodo<T> *ultimo;

public:
    ListaCircularDoble()
    {
        primero = nullptr;
        ultimo = nullptr;
    }

    bool estaVacia()
    {
        return (primero == nullptr && ultimo == nullptr);
    }

    void insertar(T *dato)
    {
        // Evitar duplicados por identificador
        if (buscar(dato->getNumeroDeRegistro()) != nullptr)
        {
            delete dato;
            return;
        }

        Nodo<T> *nuevo = new Nodo<T>(dato);

        if (estaVacia())
        {
            nuevo->setSiguiente(nuevo);
            nuevo->setAnterior(nuevo);
            primero = ultimo = nuevo;
        }
        else
        {
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(primero);
            ultimo->setSiguiente(nuevo);
            primero->setAnterior(nuevo);
            ultimo = nuevo;
        }
    }

    T *buscar(string identificador)
    {
        if (estaVacia())
        {
            return nullptr;
        }

        Nodo<T> *actual = primero;

        do
        {
            if (actual->getDato()->getNumeroDeRegistro() == identificador)
            {
                return actual->getDato();
            }
            actual = actual->getSiguiente();
        } while (actual != primero);

        return nullptr;
    }

    // Buscar por código de vuelo (campo getVuelo en T)
    T *buscarPorVuelo(const string &vuelo)
    {
        if (estaVacia())
            return nullptr;

        Nodo<T> *actual = primero;
        do
        {
            if (actual->getDato()->getVuelo() == vuelo)
                return actual->getDato();
            actual = actual->getSiguiente();
        } while (actual != primero);

        return nullptr;
    }

    bool eliminar(string identificador)
    {
        if (estaVacia())
        {
            return false;
        }

        Nodo<T> *actual = primero;

        do
        {
            if (actual->getDato()->getNumeroDeRegistro() == identificador)
            {
                // unico nodo
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
                    primero->setAnterior(ultimo);
                    ultimo->setSiguiente(primero);
                    delete actual->getDato();
                    delete actual;
                    return true;
                }
                // eliminar el ultimo
                else if (actual == ultimo)
                {
                    ultimo = ultimo->getAnterior();
                    ultimo->setSiguiente(primero);
                    primero->setAnterior(ultimo);
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
        } while (actual != primero);

        return false;
    }

    T *extraer(string identificador)
    {
        if (estaVacia())
        {
            return nullptr;
        }

        Nodo<T> *actual = primero;

        do
        {
            if (actual->getDato()->getNumeroDeRegistro() == identificador)
            {
                T *dato = actual->getDato();

                if (actual == primero && actual == ultimo)
                {
                    delete actual;
                    primero = ultimo = nullptr;
                }
                else if (actual == primero)
                {
                    primero = primero->getSiguiente();
                    primero->setAnterior(ultimo);
                    ultimo->setSiguiente(primero);
                    delete actual;
                }
                else if (actual == ultimo)
                {
                    ultimo = ultimo->getAnterior();
                    ultimo->setSiguiente(primero);
                    primero->setAnterior(ultimo);
                    delete actual;
                }
                else
                {
                    actual->getAnterior()->setSiguiente(actual->getSiguiente());
                    actual->getSiguiente()->setAnterior(actual->getAnterior());
                    delete actual;
                }

                return dato;
            }

            actual = actual->getSiguiente();
        } while (actual != primero);

        return nullptr;
    }

    int contar()
    {
        if (estaVacia())
        {
            return 0;
        }

        int i = 0;
        Nodo<T> *actual = primero;

        do
        {
            i++;
            actual = actual->getSiguiente();
        } while (actual != primero);

        return i;
    }

    void mostrar()
    {
        if (estaVacia())
        {
            cout << "La lista está vacía." << endl;
            return;
        }

        Nodo<T> *actual = primero;
        do
        {
            actual->getDato()->mostrar();
            actual = actual->getSiguiente();
        } while (actual != primero);
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
        do
        {
            archivo << "\"" << actual->getDato()->getNumeroDeRegistro() << "\" [label=\"";
            archivo << actual->getDato()->getNumeroDeRegistro();
            archivo << "\"];" << endl;
            actual = actual->getSiguiente();
        } while (actual != primero);

        archivo << endl;

        actual = primero;
        do
        {
            archivo << "\"" << actual->getDato()->getNumeroDeRegistro() << "\" -> ";
            archivo << "\"" << actual->getSiguiente()->getDato()->getNumeroDeRegistro() << "\";" << endl;
            actual = actual->getSiguiente();
        } while (actual != primero);

        archivo << endl;

        actual = primero;
        do
        {
            archivo << "\"" << actual->getDato()->getNumeroDeRegistro() << "\" -> ";
            archivo << "\"" << actual->getAnterior()->getDato()->getNumeroDeRegistro() << "\"";
            archivo << " [style=dashed, color=blue, constraint=false];" << endl;
            actual = actual->getSiguiente();
        } while (actual != primero);

        archivo << "}" << endl;
        archivo.close();

        string comando = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
        int ret = system(comando.c_str());
        if (ret != 0)
        {
            cout << "[!] Error: no se pudo ejecutar 'dot' (Graphviz). Se generó el archivo " << nombreArchivo << ".dot pero no se pudo crear/abrir el PNG." << endl;
            return;
        }

        string comandoAbrir = "start \"\" \"" + nombreArchivo + ".png\"";
        system(comandoAbrir.c_str());
    }

    ~ListaCircularDoble()
    {
        if (!estaVacia())
        {
            Nodo<T> *actual = primero;
            Nodo<T> *siguiente;

            do
            {
                siguiente = actual->getSiguiente();
                delete actual->getDato();
                delete actual;
                actual = siguiente;
            } while (actual != primero);
        }
    }
};

#endif