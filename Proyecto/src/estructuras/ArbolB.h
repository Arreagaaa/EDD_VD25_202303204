#ifndef ARBOLB_H
#define ARBOLB_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>
class NodoB
{
public:
    T **datos;
    int n;
    NodoB **hijos;
    bool esHoja;
    int orden;

    NodoB(int orden, bool esHoja)
    {
        this->orden = orden;
        this->esHoja = esHoja;
        this->n = 0;

        datos = new T *[orden - 1];
        hijos = new NodoB *[orden];

        for (int i = 0; i < orden - 1; i++)
            datos[i] = nullptr;
        for (int i = 0; i < orden; i++)
            hijos[i] = nullptr;
    }
};

template <typename T>
class ArbolB
{
private:
    NodoB<T> *raiz;
    int orden;

    void dividirHijo(NodoB<T> *padre, int i, NodoB<T> *hijo)
    {
        int t = orden / 2;
        NodoB<T> *nuevoNodo = new NodoB<T>(orden, hijo->esHoja);
        nuevoNodo->n = t - 1;

        for (int j = 0; j < t - 1; j++)
            nuevoNodo->datos[j] = hijo->datos[j + t];

        if (!hijo->esHoja)
        {
            for (int j = 0; j < t; j++)
                nuevoNodo->hijos[j] = hijo->hijos[j + t];
        }

        hijo->n = t - 1;

        for (int j = padre->n; j >= i + 1; j--)
            padre->hijos[j + 1] = padre->hijos[j];

        padre->hijos[i + 1] = nuevoNodo;

        for (int j = padre->n - 1; j >= i; j--)
            padre->datos[j + 1] = padre->datos[j];

        padre->datos[i] = hijo->datos[t - 1];
        padre->n = padre->n + 1;
    }

    void insertarNoLleno(NodoB<T> *nodo, T *dato)
    {
        int i = nodo->n - 1;

        if (nodo->esHoja)
        {
            while (i >= 0 && dato->getNumeroDeRegistro() < nodo->datos[i]->getNumeroDeRegistro())
            {
                nodo->datos[i + 1] = nodo->datos[i];
                i--;
            }

            nodo->datos[i + 1] = dato;
            nodo->n = nodo->n + 1;
        }
        else
        {
            while (i >= 0 && dato->getNumeroDeRegistro() < nodo->datos[i]->getNumeroDeRegistro())
                i--;

            i++;
            if (nodo->hijos[i]->n == orden - 1)
            {
                dividirHijo(nodo, i, nodo->hijos[i]);

                if (dato->getNumeroDeRegistro() > nodo->datos[i]->getNumeroDeRegistro())
                    i++;
            }
            insertarNoLleno(nodo->hijos[i], dato);
        }
    }

    NodoB<T> *buscarRec(NodoB<T> *nodo, string numeroRegistro)
    {
        int i = 0;
        while (i < nodo->n && numeroRegistro > nodo->datos[i]->getNumeroDeRegistro())
            i++;

        if (i < nodo->n && numeroRegistro == nodo->datos[i]->getNumeroDeRegistro())
            return nodo;

        if (nodo->esHoja)
            return nullptr;

        return buscarRec(nodo->hijos[i], numeroRegistro);
    }

    // Buscar avión por su código de vuelo (recorrido completo)
    T *buscarPorVueloRec(NodoB<T> *nodo, const string &vuelo)
    {
        if (nodo == nullptr)
            return nullptr;

        for (int i = 0; i < nodo->n; ++i)
        {
            if (nodo->datos[i]->getVuelo() == vuelo)
                return nodo->datos[i];
        }

        if (nodo->esHoja)
            return nullptr;

        for (int i = 0; i <= nodo->n; ++i)
        {
            T *res = buscarPorVueloRec(nodo->hijos[i], vuelo);
            if (res != nullptr)
                return res;
        }

        return nullptr;
    }

    void recorridoRec(NodoB<T> *nodo)
    {
        int i;
        for (i = 0; i < nodo->n; i++)
        {
            if (!nodo->esHoja)
                recorridoRec(nodo->hijos[i]);
            nodo->datos[i]->mostrar();
        }

        if (!nodo->esHoja)
            recorridoRec(nodo->hijos[i]);
    }

    void generarDotRec(NodoB<T> *nodo, ofstream &archivo, int &contador)
    {
        if (nodo == nullptr)
            return;

        int idNodo = contador++;

        archivo << "node" << idNodo << " [label=\"";
        for (int i = 0; i < nodo->n; i++)
        {
            if (i > 0)
                archivo << "|";
            // Mostrar número de registro y estado (si está disponible/mantenimiento)
            archivo << "<f" << i << "> " << nodo->datos[i]->getNumeroDeRegistro();
            string est = nodo->datos[i]->getEstado();
            archivo << "\\n"
                    << est;
        }
        archivo << "\"]" << endl;

        if (!nodo->esHoja)
        {
            for (int i = 0; i <= nodo->n; i++)
            {
                if (nodo->hijos[i] != nullptr)
                {
                    int idHijo = contador;
                    generarDotRec(nodo->hijos[i], archivo, contador);

                    archivo << "node" << idNodo;
                    if (i < nodo->n)
                        archivo << ":f" << i;
                    archivo << " -> node" << idHijo << ";" << endl;
                }
            }
        }
    }

public:
    ArbolB(int orden)
    {
        this->orden = orden;
        raiz = nullptr;
    }

    void insertar(T *dato)
    {
        // Evitar insertar duplicados por numero de registro
        if (raiz != nullptr)
        {
            T *existente = buscar(dato->getNumeroDeRegistro());
            if (existente != nullptr)
            {
                // Actualizar estado si procede y liberar el dato entrante
                existente->setEstado(dato->getEstado());
                delete dato;
                return;
            }
        }
        if (raiz == nullptr)
        {
            raiz = new NodoB<T>(orden, true);
            raiz->datos[0] = dato;
            raiz->n = 1;
        }
        else
        {
            if (raiz->n == orden - 1)
            {
                NodoB<T> *nuevaRaiz = new NodoB<T>(orden, false);
                nuevaRaiz->hijos[0] = raiz;
                dividirHijo(nuevaRaiz, 0, raiz);

                int i = 0;
                if (nuevaRaiz->datos[0]->getNumeroDeRegistro() < dato->getNumeroDeRegistro())
                    i++;

                insertarNoLleno(nuevaRaiz->hijos[i], dato);
                raiz = nuevaRaiz;
            }
            else
            {
                insertarNoLleno(raiz, dato);
            }
        }
    }

    T *buscar(string numeroRegistro)
    {
        if (raiz == nullptr)
            return nullptr;

        NodoB<T> *nodo = buscarRec(raiz, numeroRegistro);
        if (nodo == nullptr)
            return nullptr;

        for (int i = 0; i < nodo->n; i++)
        {
            if (nodo->datos[i]->getNumeroDeRegistro() == numeroRegistro)
                return nodo->datos[i];
        }

        return nullptr;
    }

    // Buscar por vuelo (wrapper)
    T *buscarPorVuelo(const string &vuelo)
    {
        if (raiz == nullptr)
            return nullptr;
        return buscarPorVueloRec(raiz, vuelo);
    }

    // Helper: encuentra el índice de la primera clave >= numeroRegistro
    int encontrarIndice(NodoB<T> *nodo, const string &numeroRegistro)
    {
        int idx = 0;
        while (idx < nodo->n && nodo->datos[idx]->getNumeroDeRegistro() < numeroRegistro)
            ++idx;
        return idx;
    }

    // obtener puntero al predecessor (derecha maxima del subárbol izquierdo)
    T *obtenerPredecesor(NodoB<T> *nodo, int idx)
    {
        NodoB<T> *cur = nodo->hijos[idx];
        while (!cur->esHoja)
            cur = cur->hijos[cur->n];
        return cur->datos[cur->n - 1];
    }

    // obtener puntero al sucesor (izquierda minima del subárbol derecho)
    T *obtenerSucesor(NodoB<T> *nodo, int idx)
    {
        NodoB<T> *cur = nodo->hijos[idx + 1];
        while (!cur->esHoja)
            cur = cur->hijos[0];
        return cur->datos[0];
    }

    // tomar prestado del hijo previo
    void tomarPrestadoPrev(NodoB<T> *nodo, int idx)
    {
        NodoB<T> *hijo = nodo->hijos[idx];
        NodoB<T> *hermano = nodo->hijos[idx - 1];

        // mover todas las keys del hijo hacia la derecha
        for (int i = hijo->n - 1; i >= 0; --i)
            hijo->datos[i + 1] = hijo->datos[i];

        if (!hijo->esHoja)
        {
            for (int i = hijo->n; i >= 0; --i)
                hijo->hijos[i + 1] = hijo->hijos[i];
        }

        // poner la key desde el padre en hijo->datos[0]
        hijo->datos[0] = nodo->datos[idx - 1];

        if (!hijo->esHoja)
            hijo->hijos[0] = hermano->hijos[hermano->n];

        // mover la última key del hermano al padre
        nodo->datos[idx - 1] = hermano->datos[hermano->n - 1];

        hijo->n += 1;
        hermano->n -= 1;
    }

    // tomar prestado del siguiente hermano
    void tomarPrestadoNext(NodoB<T> *nodo, int idx)
    {
        NodoB<T> *hijo = nodo->hijos[idx];
        NodoB<T> *hermano = nodo->hijos[idx + 1];

        // padre key pasa al final del hijo
        hijo->datos[hijo->n] = nodo->datos[idx];

        if (!hijo->esHoja)
            hijo->hijos[hijo->n + 1] = hermano->hijos[0];

        // primera key de hermano se mueve al padre
        nodo->datos[idx] = hermano->datos[0];

        // shift hermano keys left
        for (int i = 1; i < hermano->n; ++i)
            hermano->datos[i - 1] = hermano->datos[i];

        if (!hermano->esHoja)
        {
            for (int i = 1; i <= hermano->n; ++i)
                hermano->hijos[i - 1] = hermano->hijos[i];
        }

        hijo->n += 1;
        hermano->n -= 1;
    }

    // merge hijo idx y idx+1; mover la key del padre al medio
    void mergeHijos(NodoB<T> *nodo, int idx)
    {
        NodoB<T> *hijo = nodo->hijos[idx];
        NodoB<T> *hermano = nodo->hijos[idx + 1];
        int t = orden / 2;

        // mover la key del padre a hijo
        hijo->datos[t - 1] = nodo->datos[idx];

        // copiar las keys de hermano a hijo
        for (int i = 0; i < hermano->n; ++i)
            hijo->datos[i + t] = hermano->datos[i];

        // copiar los hijos de hermano
        if (!hijo->esHoja)
        {
            for (int i = 0; i <= hermano->n; ++i)
                hijo->hijos[i + t] = hermano->hijos[i];
        }

        // mover las keys del padre hacia la izquierda
        for (int i = idx + 1; i < nodo->n; ++i)
            nodo->datos[i - 1] = nodo->datos[i];

        // mover los hijos del padre
        for (int i = idx + 2; i <= nodo->n; ++i)
            nodo->hijos[i - 1] = nodo->hijos[i];

        hijo->n = hijo->n + hermano->n + 1;
        nodo->n = nodo->n - 1;

        // liberar hermano
        delete[] hermano->datos; // free arrays inside destructor? But NodoB destructor not defined; we'll manually delete contents
        delete[] hermano->hijos;
        delete hermano;
    }

    // Asegura que el hijo en índice idx tenga al menos t keys
    void llenar(NodoB<T> *nodo, int idx)
    {
        int t = orden / 2;
        if (idx != 0 && nodo->hijos[idx - 1]->n >= t)
        {
            tomarPrestadoPrev(nodo, idx);
        }
        else if (idx != nodo->n && nodo->hijos[idx + 1]->n >= t)
        {
            tomarPrestadoNext(nodo, idx);
        }
        else
        {
            if (idx != nodo->n)
                mergeHijos(nodo, idx);
            else
                mergeHijos(nodo, idx - 1);
        }
    }

    // Eliminacion recursiva que devuelve el puntero eliminado via resultado
    NodoB<T> *eliminarClaveRec(NodoB<T> *nodo, const string &k, T *&resultado)
    {
        if (nodo == nullptr)
            return nodo;

        int idx = encontrarIndice(nodo, k);

        // caso 1: clave está en este nodo
        if (idx < nodo->n && nodo->datos[idx]->getNumeroDeRegistro() == k)
        {
            // si es hoja
            if (nodo->esHoja)
            {
                resultado = nodo->datos[idx];
                // shift keys
                for (int i = idx + 1; i < nodo->n; ++i)
                    nodo->datos[i - 1] = nodo->datos[i];
                nodo->datos[nodo->n - 1] = nullptr;
                nodo->n -= 1;
                return nodo;
            }
            else
            {
                int t = orden / 2;
                // si hijo anterior tiene al menos t keys
                if (nodo->hijos[idx]->n >= t)
                {
                    T *pred = obtenerPredecesor(nodo, idx);
                    T *toRemove = nodo->datos[idx];
                    nodo->datos[idx] = pred; // reemplazamos puntero con predecesor
                    // eliminar predecesor en hijo izquierdo
                    nodo->hijos[idx] = eliminarClaveRec(nodo->hijos[idx], pred->getNumeroDeRegistro(), resultado);
                    // resultado contiene el puntero eliminado (pred)
                    // devolvemos el original que pedimos eliminar
                    resultado = toRemove;
                    return nodo;
                }
                // si hijo siguiente tiene al menos t keys
                else if (nodo->hijos[idx + 1]->n >= t)
                {
                    T *succ = obtenerSucesor(nodo, idx);
                    T *toRemove = nodo->datos[idx];
                    nodo->datos[idx] = succ;
                    nodo->hijos[idx + 1] = eliminarClaveRec(nodo->hijos[idx + 1], succ->getNumeroDeRegistro(), resultado);
                    resultado = toRemove;
                    return nodo;
                }
                else
                {
                    // ambos hijos tienen t-1 keys, unirlos y eliminar la clave en el hijo resultante
                    mergeHijos(nodo, idx);
                    nodo->hijos[idx] = eliminarClaveRec(nodo->hijos[idx], k, resultado);
                    return nodo;
                }
            }
        }
        else
        {
            // clave no está en este nodo
            if (nodo->esHoja)
            {
                // la clave no está en el árbol
                return nodo;
            }

            bool flag = ( (idx == nodo->n) ? true : false );

            if (nodo->hijos[idx]->n < (orden/2))
            {
                llenar(nodo, idx);
            }

            if (flag && idx > nodo->n)
                nodo->hijos[idx - 1] = eliminarClaveRec(nodo->hijos[idx - 1], k, resultado);
            else
                nodo->hijos[idx] = eliminarClaveRec(nodo->hijos[idx], k, resultado);

            return nodo;
        }
    }

    // Extrae (remueve) el dato identificado por numeroRegistro del árbol y lo retorna.
    // Implementación completa con re-balanceo del B-Tree.
    T *extraer(string numeroRegistro)
    {
        if (raiz == nullptr)
            return nullptr;

        T *resultado = nullptr;
        raiz = eliminarClaveRec(raiz, numeroRegistro, resultado);

        // Si la raíz tiene 0 keys ahora, ajustar
        if (raiz != nullptr && raiz->n == 0)
        {
            NodoB<T> *tmp = raiz;
            if (raiz->esHoja)
            {
                // árbol quedó vacío
                delete[] raiz->datos;
                delete[] raiz->hijos;
                delete raiz;
                raiz = nullptr;
            }
            else
            {
                raiz = raiz->hijos[0];
                delete[] tmp->datos;
                delete[] tmp->hijos;
                delete tmp;
            }
        }

        return resultado;
    }

    void recorrido()
    {
        if (raiz != nullptr)
            recorridoRec(raiz);
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
        archivo << "node [shape=record];" << endl;
        archivo << "label=\"" << titulo << "\";" << endl;
        archivo << "labelloc=\"t\";" << endl;
        archivo << endl;

        int contador = 0;
        generarDotRec(raiz, archivo, contador);

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

    void eliminarNodoRec(NodoB<T> *nodo)
    {
        if (nodo == nullptr)
            return;

        if (!nodo->esHoja)
        {
            for (int i = 0; i <= nodo->n; i++)
            {
                if (nodo->hijos[i] != nullptr)
                    eliminarNodoRec(nodo->hijos[i]);
            }
        }

        // eliminar los datos almacenados
        for (int i = 0; i < nodo->n; i++)
        {
            if (nodo->datos[i] != nullptr)
            {
                delete nodo->datos[i];
                nodo->datos[i] = nullptr;
            }
        }

        delete[] nodo->datos;
        delete[] nodo->hijos;
        delete nodo;
    }

    ~ArbolB()
    {
        eliminarNodoRec(raiz);
    }
};

#endif
