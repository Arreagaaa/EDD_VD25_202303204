#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../models/Piloto.h"

using namespace std;

template <typename T>
class NodoHash
{
public:
    string clave;
    T *dato;
    NodoHash *siguiente;

    NodoHash(string clave, T *dato)
    {
        this->clave = clave;
        this->dato = dato;
        this->siguiente = nullptr;
    }
};

template <typename T>
class TablaHash
{
private:
    NodoHash<T> **tabla;
    int capacidad;

    int funcionHash(string id)
    {
        // Función hash: h(#id) = sumatoria(#id) Mod(19)
        // Suma todos los dígitos del ID y hace módulo M
        int suma = 0;
        for (char c : id)
        {
            if (isdigit(static_cast<unsigned char>(c)))
            {
                suma += (c - '0');  // Sumar cada dígito
            }
        }

        return suma % capacidad;
    }

public:
    TablaHash(int capacidad)
    {
        this->capacidad = capacidad;
        tabla = new NodoHash<T> *[capacidad];

        for (int i = 0; i < capacidad; i++)
            tabla[i] = nullptr;
    }

    void insertar(string clave, T *dato)
    {
        int indice = funcionHash(clave);
        NodoHash<T> *nuevo = new NodoHash<T>(clave, dato);

        if (tabla[indice] == nullptr)
        {
            tabla[indice] = nuevo;
        }
        else
        {
            NodoHash<T> *actual = tabla[indice];
            while (actual->siguiente != nullptr)
            {
                if (actual->clave == clave)
                {
                    if (actual->dato != nullptr)
                        delete actual->dato;
                    actual->dato = dato;
                    delete nuevo;
                    return;
                }
                actual = actual->siguiente;
            }

            if (actual->clave == clave)
            {
                if (actual->dato != nullptr)
                    delete actual->dato;
                actual->dato = dato;
                delete nuevo;
            }
            else
            {
                actual->siguiente = nuevo;
            }
        }
    }

    T *buscar(string clave)
    {
        int indice = funcionHash(clave);
        NodoHash<T> *actual = tabla[indice];

        while (actual != nullptr)
        {
            if (actual->clave == clave)
                return actual->dato;
            actual = actual->siguiente;
        }

        return nullptr;
    }

    bool eliminar(string clave)
    {
        int indice = funcionHash(clave);
        NodoHash<T> *actual = tabla[indice];
        NodoHash<T> *anterior = nullptr;

        while (actual != nullptr)
        {
            if (actual->clave == clave)
            {
                if (anterior == nullptr)
                    tabla[indice] = actual->siguiente;
                else
                    anterior->siguiente = actual->siguiente;

                delete actual->dato;
                delete actual;
                return true;
            }

            anterior = actual;
            actual = actual->siguiente;
        }

        return false;
    }

    void mostrar()
    {
        for (int i = 0; i < capacidad; i++)
        {
            cout << "[" << i << "] -> ";
            NodoHash<T> *actual = tabla[i];

            while (actual != nullptr)
            {
                cout << actual->clave << " -> ";
                actual = actual->siguiente;
            }
            cout << "NULL" << endl;
        }
    }

    vector<T*> obtenerTodos()
    {
        vector<T*> res;
        for (int i = 0; i < capacidad; i++)
        {
            NodoHash<T> *actual = tabla[i];
            while (actual != nullptr)
            {
                if (actual->dato != nullptr)
                    res.push_back(actual->dato);
                actual = actual->siguiente;
            }
        }
        return res;
    }

    void generarReporte(string nombreArchivo, string titulo)
    {
        ofstream archivo;
        archivo.open(nombreArchivo + ".dot", ios::out);

        archivo << "digraph G {" << endl;
        archivo << "rankdir=LR;" << endl;
        archivo << "node [shape=record];" << endl;
        archivo << "label=\"" << titulo << "\";" << endl;
        archivo << "labelloc=\"t\";" << endl;
        archivo << endl;

        archivo << "tabla [label=\"";
        for (int i = 0; i < capacidad; i++)
        {
            if (i > 0)
                archivo << "|";
            archivo << "<f" << i << "> " << i;
        }
        archivo << "\"];" << endl;
        archivo << endl;

        for (int i = 0; i < capacidad; i++)
        {
            NodoHash<T> *actual = tabla[i];
            int contador = 0;

            while (actual != nullptr)
            {
                string nodoId = "nodo" + to_string(i) + "_" + to_string(contador);

                archivo << nodoId << " [label=\"" << actual->clave << "\"];" << endl;

                if (contador == 0)
                    archivo << "tabla:f" << i << " -> " << nodoId << ";" << endl;
                else
                {
                    string nodoAnterior = "nodo" + to_string(i) + "_" + to_string(contador - 1);
                    archivo << nodoAnterior << " -> " << nodoId << ";" << endl;
                }

                actual = actual->siguiente;
                contador++;
            }
        }

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

    ~TablaHash()
    {
        for (int i = 0; i < capacidad; i++)
        {
            NodoHash<T> *actual = tabla[i];
            while (actual != nullptr)
            {
                NodoHash<T> *temp = actual;
                actual = actual->siguiente;
                delete temp->dato;
                delete temp;
            }
        }
        delete[] tabla;
    }
};

#endif
