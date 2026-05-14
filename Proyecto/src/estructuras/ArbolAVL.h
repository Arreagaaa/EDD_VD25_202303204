#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
class NodoAVL
{
public:
    T *dato;
    NodoAVL *izquierda;
    NodoAVL *derecha;
    int altura;

    NodoAVL(T *dato)
    {
        this->dato = dato;
        this->izquierda = nullptr;
        this->derecha = nullptr;
        this->altura = 1;
    }
};

template <typename T>
class ArbolAVL
{
private:
    NodoAVL<T> *raiz;

    int obtenerAltura(NodoAVL<T> *nodo)
    {
        if (nodo == nullptr)
            return 0;
        return nodo->altura;
    }

    int obtenerBalance(NodoAVL<T> *nodo)
    {
        if (nodo == nullptr)
            return 0;
        return obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha);
    }

    NodoAVL<T> *rotacionDerecha(NodoAVL<T> *y)
    {
        NodoAVL<T> *x = y->izquierda;
        NodoAVL<T> *T2 = x->derecha;

        x->derecha = y;
        y->izquierda = T2;

        y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
        x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

        return x;
    }

    NodoAVL<T> *rotacionIzquierda(NodoAVL<T> *x)
    {
        NodoAVL<T> *y = x->derecha;
        NodoAVL<T> *T2 = y->izquierda;

        y->izquierda = x;
        x->derecha = T2;

        x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
        y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

        return y;
    }

    NodoAVL<T> *insertarNodo(NodoAVL<T> *nodo, T *dato)
    {
        if (nodo == nullptr)
            return new NodoAVL<T>(dato);

        // Ordenar por horas de vuelo, y si son iguales usar ID como tie-breaker
        if (dato->getHorasVuelo() < nodo->dato->getHorasVuelo() ||
            (dato->getHorasVuelo() == nodo->dato->getHorasVuelo() && dato->getId() < nodo->dato->getId()))
            nodo->izquierda = insertarNodo(nodo->izquierda, dato);
        else if (dato->getHorasVuelo() > nodo->dato->getHorasVuelo() ||
                 (dato->getHorasVuelo() == nodo->dato->getHorasVuelo() && dato->getId() > nodo->dato->getId()))
            nodo->derecha = insertarNodo(nodo->derecha, dato);
        else
            return nodo;

        nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));

        int balance = obtenerBalance(nodo);

        // Izquierda-Izquierda
        if (balance > 1 && dato->getHorasVuelo() < nodo->izquierda->dato->getHorasVuelo())
            return rotacionDerecha(nodo);

        // Derecha-Derecha
        if (balance < -1 && dato->getHorasVuelo() > nodo->derecha->dato->getHorasVuelo())
            return rotacionIzquierda(nodo);

        // Izquierda-Derecha
        if (balance > 1 && dato->getHorasVuelo() > nodo->izquierda->dato->getHorasVuelo())
        {
            nodo->izquierda = rotacionIzquierda(nodo->izquierda);
            return rotacionDerecha(nodo);
        }

        // Derecha-Izquierda
        if (balance < -1 && dato->getHorasVuelo() < nodo->derecha->dato->getHorasVuelo())
        {
            nodo->derecha = rotacionDerecha(nodo->derecha);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    NodoAVL<T> *nodoConValorMinimo(NodoAVL<T> *nodo)
    {
        NodoAVL<T> *actual = nodo;
        while (actual->izquierda != nullptr)
            actual = actual->izquierda;
        return actual;
    }

    // Variante de eliminar que retorna el puntero al dato eliminado a traves de datoEliminado (no lo borra internamente)
    NodoAVL<T> *eliminarNodoRetornar(NodoAVL<T> *raiz, int horasVuelo, const string &id, T *&datoEliminado)
    {
        if (raiz == nullptr)
            return raiz;

        if (horasVuelo < raiz->dato->getHorasVuelo() ||
            (horasVuelo == raiz->dato->getHorasVuelo() && id < raiz->dato->getId()))
        {
            raiz->izquierda = eliminarNodoRetornar(raiz->izquierda, horasVuelo, id, datoEliminado);
        }
        else if (horasVuelo > raiz->dato->getHorasVuelo() ||
                 (horasVuelo == raiz->dato->getHorasVuelo() && id > raiz->dato->getId()))
        {
            raiz->derecha = eliminarNodoRetornar(raiz->derecha, horasVuelo, id, datoEliminado);
        }
        else
        {
            // nodo encontrado (comparando horas e id)
            // Guardar el dato original para devolverlo
            datoEliminado = raiz->dato;

            // Caso 1: un solo hijo o ninguno
            if (raiz->izquierda == nullptr || raiz->derecha == nullptr)
            {
                NodoAVL<T> *hijo = (raiz->izquierda != nullptr) ? raiz->izquierda : raiz->derecha;

                if (hijo == nullptr)
                {
                    // No children
                    delete raiz;
                    return nullptr;
                }
                else
                {
                    // Un solo hijo: reemplazar el nodo actual por su hijo
                    NodoAVL<T> *temp = raiz;
                    raiz = hijo;
                    delete temp;
                }
            }
            else
            {
                // Dos hijos: intercambiar (swap) los punteros de dato con el sucesor y eliminar físicamente el sucesor.
                // De esta forma el puntero que se elimina será el correcto (el dato físico removido), que se devolverá a través de datoEliminado.
                NodoAVL<T> *temp = nodoConValorMinimo(raiz->derecha);

                // Intercambiar punteros de datos
                T *tmpPtr = raiz->dato;
                raiz->dato = temp->dato;
                temp->dato = tmpPtr;

                // Eliminar el sucesor (ahora contiene el dato original que queremos retornar)
                raiz->derecha = eliminarNodoRetornar(raiz->derecha, temp->dato->getHorasVuelo(), temp->dato->getId(), datoEliminado);

                // Nota: no borramos datoEliminado aquí; se retorna al llamador para que gestione la liberación
            }
        }

        // Si raiz es nulo, retornamos
        if (raiz == nullptr)
            return raiz;

        // Actualizar altura y balance
        raiz->altura = 1 + max(obtenerAltura(raiz->izquierda), obtenerAltura(raiz->derecha));

        int balance = obtenerBalance(raiz);

        // Rotaciones segun balance
        if (balance > 1 && obtenerBalance(raiz->izquierda) >= 0)
            return rotacionDerecha(raiz);

        if (balance > 1 && obtenerBalance(raiz->izquierda) < 0)
        {
            raiz->izquierda = rotacionIzquierda(raiz->izquierda);
            return rotacionDerecha(raiz);
        }

        if (balance < -1 && obtenerBalance(raiz->derecha) <= 0)
            return rotacionIzquierda(raiz);

        if (balance < -1 && obtenerBalance(raiz->derecha) > 0)
        {
            raiz->derecha = rotacionDerecha(raiz->derecha);
            return rotacionIzquierda(raiz);
        }

        return raiz;
    }

    // Wrapper que mantiene compatibilidad con la implementacion anterior (no retorna el dato eliminado)
    NodoAVL<T> *eliminarNodo(NodoAVL<T> *raiz, int horasVuelo, const string &id)
    {
        T *dummy = nullptr;
        return eliminarNodoRetornar(raiz, horasVuelo, id, dummy);
    }

    void preordenRec(NodoAVL<T> *nodo)
    {
        if (nodo != nullptr)
        {
            nodo->dato->mostrar();
            preordenRec(nodo->izquierda);
            preordenRec(nodo->derecha);
        }
    }

    void inordenRec(NodoAVL<T> *nodo)
    {
        if (nodo != nullptr)
        {
            inordenRec(nodo->izquierda);
            nodo->dato->mostrar();
            inordenRec(nodo->derecha);
        }
    }

    void postordenRec(NodoAVL<T> *nodo)
    {
        if (nodo != nullptr)
        {
            postordenRec(nodo->izquierda);
            postordenRec(nodo->derecha);
            nodo->dato->mostrar();
        }
    }

    void generarDotRec(NodoAVL<T> *nodo, ofstream &archivo)
    {
        if (nodo != nullptr)
        {
            archivo << "\"" << nodo->dato->getId() << "\" [label=\"ID: " << nodo->dato->getId() << "\\nHoras: " << nodo->dato->getHorasVuelo() << "\"]" << endl;

            if (nodo->izquierda != nullptr)
            {
                archivo << "\"" << nodo->dato->getId() << "\" -> \"" << nodo->izquierda->dato->getId() << "\";" << endl;
                generarDotRec(nodo->izquierda, archivo);
            }

            if (nodo->derecha != nullptr)
            {
                archivo << "\"" << nodo->dato->getId() << "\" -> \"" << nodo->derecha->dato->getId() << "\";" << endl;
                generarDotRec(nodo->derecha, archivo);
            }
        }
    }

public:
    ArbolAVL()
    {
        raiz = nullptr;
    }

    void insertar(T *dato)
    {
        raiz = insertarNodo(raiz, dato);
    }

    // Elimina el nodo identificado por (horasVuelo, id) y devuelve el puntero al dato eliminado (no se borra el dato internamente).
    // Devuelve nullptr si no se encontró.
    T *eliminar(int horasVuelo, const string &id)
    {
        T *datoEliminado = nullptr;
        raiz = eliminarNodoRetornar(raiz, horasVuelo, id, datoEliminado);
        return datoEliminado;
    }

    void preorden()
    {
        cout << "\n=== Recorrido PREORDEN ===" << endl;
        preordenRec(raiz);
    }

    void inorden()
    {
        cout << "\n=== Recorrido INORDEN ===" << endl;
        inordenRec(raiz);
    }

    void postorden()
    {
        cout << "\n=== Recorrido POSTORDEN ===" << endl;
        postordenRec(raiz);
    }

    void generarReporte(string nombreArchivo, string titulo)
    {
        if (raiz == nullptr)
        {
            cout << "El árbol está vacío, no se puede generar el reporte." << endl;
            return;
        }

        ofstream archivo;
        archivo.open(nombreArchivo + ".dot", ios::out);

        archivo << "digraph G {" << endl;
        archivo << "label=\"" << titulo << "\";" << endl;
        archivo << "labelloc=\"t\";" << endl;
        archivo << endl;

        generarDotRec(raiz, archivo);

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

    void eliminarRecursivo(NodoAVL<T> *nodo)
    {
        if (nodo == nullptr)
            return;
        eliminarRecursivo(nodo->izquierda);
        eliminarRecursivo(nodo->derecha);
        // eliminar el dato almacenado y el nodo
        if (nodo->dato != nullptr)
            delete nodo->dato;
        delete nodo;
    }

    ~ArbolAVL()
    {
        eliminarRecursivo(raiz);
    }
};

#endif