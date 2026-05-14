#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class NodoMatriz
{
public:
    int x;
    int y;
    string dato; // ID del piloto
    NodoMatriz *arriba;
    NodoMatriz *abajo;
    NodoMatriz *izquierda;
    NodoMatriz *derecha;

    NodoMatriz(int x, int y, string dato)
    {
        this->x = x;
        this->y = y;
        this->dato = dato;
        this->arriba = nullptr;
        this->abajo = nullptr;
        this->izquierda = nullptr;
        this->derecha = nullptr;
    }
};

class NodoCabecera
{
public:
    int id;
    string nombre;
    NodoCabecera *siguiente;
    NodoCabecera *anterior;
    NodoMatriz *acceso;

    NodoCabecera(int id, string nombre)
    {
        this->id = id;
        this->nombre = nombre;
        this->siguiente = nullptr;
        this->anterior = nullptr;
        this->acceso = nullptr;
    }
};

class MatrizDispersa
{
private:
    NodoCabecera *cabeceraFilas;    // Vuelos (eje Y)
    NodoCabecera *cabeceraColumnas; // Ciudades (eje X)
    int contadorFilas;
    int contadorColumnas;

    NodoCabecera *buscarCabeceraFila(string nombre)
    {
        NodoCabecera *actual = cabeceraFilas;
        while (actual != nullptr)
        {
            if (actual->nombre == nombre)
                return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    NodoCabecera *buscarCabeceraColumna(string nombre)
    {
        NodoCabecera *actual = cabeceraColumnas;
        while (actual != nullptr)
        {
            if (actual->nombre == nombre)
                return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    NodoCabecera *insertarCabeceraFila(string nombre)
    {
        NodoCabecera *existe = buscarCabeceraFila(nombre);
        if (existe != nullptr)
            return existe;

        NodoCabecera *nueva = new NodoCabecera(contadorFilas++, nombre);

        if (cabeceraFilas == nullptr)
        {
            cabeceraFilas = nueva;
        }
        else
        {
            NodoCabecera *actual = cabeceraFilas;
            while (actual->siguiente != nullptr)
                actual = actual->siguiente;
            actual->siguiente = nueva;
            nueva->anterior = actual;
        }

        return nueva;
    }

    NodoCabecera *insertarCabeceraColumna(string nombre)
    {
        NodoCabecera *existe = buscarCabeceraColumna(nombre);
        if (existe != nullptr)
            return existe;

        NodoCabecera *nueva = new NodoCabecera(contadorColumnas++, nombre);

        if (cabeceraColumnas == nullptr)
        {
            cabeceraColumnas = nueva;
        }
        else
        {
            NodoCabecera *actual = cabeceraColumnas;
            while (actual->siguiente != nullptr)
                actual = actual->siguiente;
            actual->siguiente = nueva;
            nueva->anterior = actual;
        }

        return nueva;
    }

    void insertarEnFila(NodoCabecera *cabecera, NodoMatriz *nuevo)
    {
        if (cabecera->acceso == nullptr)
        {
            cabecera->acceso = nuevo;
            return;
        }

        NodoMatriz *actual = cabecera->acceso;
        NodoMatriz *anterior = nullptr;

        while (actual != nullptr && actual->y < nuevo->y)
        {
            anterior = actual;
            actual = actual->derecha;
        }

        if (anterior == nullptr)
        {
            nuevo->derecha = cabecera->acceso;
            cabecera->acceso->izquierda = nuevo;
            cabecera->acceso = nuevo;
        }
        else
        {
            anterior->derecha = nuevo;
            nuevo->izquierda = anterior;
            nuevo->derecha = actual;
            if (actual != nullptr)
                actual->izquierda = nuevo;
        }
    }

    void insertarEnColumna(NodoCabecera *cabecera, NodoMatriz *nuevo)
    {
        if (cabecera->acceso == nullptr)
        {
            cabecera->acceso = nuevo;
            return;
        }

        NodoMatriz *actual = cabecera->acceso;
        NodoMatriz *anterior = nullptr;

        while (actual != nullptr && actual->x < nuevo->x)
        {
            anterior = actual;
            actual = actual->abajo;
        }

        if (anterior == nullptr)
        {
            nuevo->abajo = cabecera->acceso;
            cabecera->acceso->arriba = nuevo;
            cabecera->acceso = nuevo;
        }
        else
        {
            anterior->abajo = nuevo;
            nuevo->arriba = anterior;
            nuevo->abajo = actual;
            if (actual != nullptr)
                actual->arriba = nuevo;
        }
    }

    void eliminarCabeceraFilaHuerfana(string nombreFila)
    {
        NodoCabecera *cabecera = buscarCabeceraFila(nombreFila);
        if (cabecera == nullptr || cabecera->acceso != nullptr)
            return;

        if (cabecera->anterior != nullptr)
            cabecera->anterior->siguiente = cabecera->siguiente;
        else
            cabeceraFilas = cabecera->siguiente;

        if (cabecera->siguiente != nullptr)
            cabecera->siguiente->anterior = cabecera->anterior;

        delete cabecera;
    }

    void eliminarCabeceraColumnaHuerfana(string nombreColumna)
    {
        NodoCabecera *cabecera = buscarCabeceraColumna(nombreColumna);
        if (cabecera == nullptr || cabecera->acceso != nullptr)
            return;

        if (cabecera->anterior != nullptr)
            cabecera->anterior->siguiente = cabecera->siguiente;
        else
            cabeceraColumnas = cabecera->siguiente;

        if (cabecera->siguiente != nullptr)
            cabecera->siguiente->anterior = cabecera->anterior;

        delete cabecera;
    }

public:
    MatrizDispersa()
    {
        cabeceraFilas = nullptr;
        cabeceraColumnas = nullptr;
        contadorFilas = 0;
        contadorColumnas = 0;
    }

    // Insertar: Vuelo (fila), Ciudad (columna), ID Piloto (dato)
    void insertar(string idPiloto, string vuelo, string ciudad)
    {
        NodoCabecera *fila = insertarCabeceraFila(vuelo);        // Vuelo en filas
        NodoCabecera *columna = insertarCabeceraColumna(ciudad); // Ciudad en columnas

        // Verificar si ya existe un nodo en esta posición
        NodoMatriz *actual = fila->acceso;
        while (actual != nullptr)
        {
            if (actual->y == columna->id)
            {
                actual->dato = idPiloto; // Actualizar piloto
                return;
            }
            actual = actual->derecha;
        }

        // Crear nuevo nodo con ID del piloto
        NodoMatriz *nuevo = new NodoMatriz(fila->id, columna->id, idPiloto);

        insertarEnFila(fila, nuevo);
        insertarEnColumna(columna, nuevo);
    }

    // Eliminar todos los nodos donde aparezca este ID de piloto
    void eliminarPiloto(string idPiloto)
    {
        bool encontrado = false;

        // Recorrer todas las filas buscando el piloto
        NodoCabecera *fila = cabeceraFilas;
        while (fila != nullptr)
        {
            NodoMatriz *actual = fila->acceso;
            NodoMatriz *siguiente = nullptr;

            while (actual != nullptr)
            {
                siguiente = actual->derecha;

                if (actual->dato == idPiloto)
                {
                    encontrado = true;

                    // Desconectar de la fila
                    if (actual->izquierda != nullptr)
                        actual->izquierda->derecha = actual->derecha;
                    else
                        fila->acceso = actual->derecha;

                    if (actual->derecha != nullptr)
                        actual->derecha->izquierda = actual->izquierda;

                    // Desconectar de la columna
                    if (actual->arriba != nullptr)
                        actual->arriba->abajo = actual->abajo;
                    if (actual->abajo != nullptr)
                        actual->abajo->arriba = actual->arriba;

                    // Actualizar cabecera de columna si es necesario
                    NodoCabecera *col = cabeceraColumnas;
                    while (col != nullptr)
                    {
                        if (col->id == actual->y && col->acceso == actual)
                        {
                            col->acceso = actual->abajo;
                            // Verificar si la columna quedó huérfana
                            if (col->acceso == nullptr)
                                eliminarCabeceraColumnaHuerfana(col->nombre);
                            break;
                        }
                        col = col->siguiente;
                    }

                    delete actual;
                }

                actual = siguiente;
            }

            NodoCabecera *sigFila = fila->siguiente;
            // Verificar si la fila quedó huérfana
            if (fila->acceso == nullptr)
                eliminarCabeceraFilaHuerfana(fila->nombre);

            fila = sigFila;
        }

        if (encontrado)
            cout << "[+] Piloto " << idPiloto << " eliminado de la matriz" << endl;
        else
            cout << "[-] Piloto " << idPiloto << " no encontrado en matriz" << endl;
    }

    void mostrar()
    {
        cout << "\n=== Matriz Dispersa ===" << endl;
        cout << "Vuelo -> Ciudades: Piloto" << endl;

        NodoCabecera *fila = cabeceraFilas;
        while (fila != nullptr)
        {
            cout << fila->nombre << " -> ";
            NodoMatriz *nodo = fila->acceso;
            while (nodo != nullptr)
            {
                // Buscar nombre de columna
                NodoCabecera *col = cabeceraColumnas;
                while (col != nullptr && col->id != nodo->y)
                    col = col->siguiente;

                if (col != nullptr)
                    cout << "[" << col->nombre << ": " << nodo->dato << "] ";

                nodo = nodo->derecha;
            }
            cout << endl;
            fila = fila->siguiente;
        }
    }

    void generarReporte(string nombreArchivo, string titulo)
    {
        ofstream archivo;
        archivo.open(nombreArchivo + ".dot", ios::out);

        archivo << "digraph G {" << endl;
        archivo << "rankdir=LR;" << endl; // ← CAMBIO PRINCIPAL: Horizontal en vez de vertical
        archivo << "node [shape=box];" << endl;
        archivo << "label=\"" << titulo << "\";" << endl;
        archivo << "labelloc=\"t\";" << endl;
        archivo << endl;

        // Nodo raíz
        archivo << "raiz [label=\"Matriz\"];" << endl;

        // Cabeceras de columnas (ciudades)
        NodoCabecera *col = cabeceraColumnas;
        while (col != nullptr)
        {
            archivo << "col" << col->id << " [label=\"" << col->nombre << "\"];" << endl;
            col = col->siguiente;
        }

        // Cabeceras de filas (vuelos)
        NodoCabecera *fila = cabeceraFilas;
        while (fila != nullptr)
        {
            archivo << "fila" << fila->id << " [label=\"" << fila->nombre << "\"];" << endl;
            fila = fila->siguiente;
        }

        // Enlaces entre cabeceras de columnas (mantener en línea horizontal)
        col = cabeceraColumnas;
        NodoCabecera *colAnterior = nullptr;
        while (col != nullptr)
        {
            if (colAnterior == nullptr)
                archivo << "raiz -> col" << col->id << ";" << endl;
            else
                archivo << "col" << colAnterior->id << " -> col" << col->id << ";" << endl;

            colAnterior = col;
            col = col->siguiente;
        }

        // Enlaces entre cabeceras de filas (verticales desde raíz)
        fila = cabeceraFilas;
        NodoCabecera *filaAnterior = nullptr;
        while (fila != nullptr)
        {
            if (filaAnterior == nullptr)
                archivo << "raiz -> fila" << fila->id << ";" << endl;
            else
                archivo << "fila" << filaAnterior->id << " -> fila" << fila->id << ";" << endl;

            filaAnterior = fila;
            fila = fila->siguiente;
        }

        // Nodos internos (pilotos)
        fila = cabeceraFilas;
        while (fila != nullptr)
        {
            NodoMatriz *nodo = fila->acceso;
            while (nodo != nullptr)
            {
                archivo << "nodo" << nodo->x << "_" << nodo->y
                        << " [label=\"" << nodo->dato << "\"];" << endl;
                nodo = nodo->derecha;
            }
            fila = fila->siguiente;
        }

        // Enlaces de filas a nodos (horizontales)
        fila = cabeceraFilas;
        while (fila != nullptr)
        {
            NodoMatriz *nodo = fila->acceso;
            if (nodo != nullptr)
                archivo << "fila" << fila->id << " -> nodo" << nodo->x << "_" << nodo->y << ";" << endl;

            while (nodo != nullptr)
            {
                if (nodo->derecha != nullptr)
                    archivo << "nodo" << nodo->x << "_" << nodo->y
                            << " -> nodo" << nodo->derecha->x << "_" << nodo->derecha->y << ";" << endl;
                nodo = nodo->derecha;
            }
            fila = fila->siguiente;
        }

        // Enlaces de columnas a nodos (verticales) con constraint=false para mejor layout
        col = cabeceraColumnas;
        while (col != nullptr)
        {
            NodoMatriz *nodo = col->acceso;
            if (nodo != nullptr)
                archivo << "col" << col->id << " -> nodo" << nodo->x << "_" << nodo->y
                        << " [constraint=false];" << endl;

            while (nodo != nullptr)
            {
                if (nodo->abajo != nullptr)
                    archivo << "nodo" << nodo->x << "_" << nodo->y
                            << " -> nodo" << nodo->abajo->x << "_" << nodo->abajo->y
                            << " [constraint=false];" << endl;
                nodo = nodo->abajo;
            }
            col = col->siguiente;
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

    ~MatrizDispersa() {}
};

#endif
