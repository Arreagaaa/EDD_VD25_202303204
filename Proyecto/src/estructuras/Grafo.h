#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include <queue>
#include <functional>

using namespace std;

class Arista
{
public:
    string destino;
    int peso;
    Arista *siguiente;

    Arista(string destino, int peso)
    {
        this->destino = destino;
        this->peso = peso;
        this->siguiente = nullptr;
    }
};

class NodoGrafo
{
public:
    string ciudad;
    Arista *adyacentes;
    NodoGrafo *siguiente;

    NodoGrafo(string ciudad)
    {
        this->ciudad = ciudad;
        this->adyacentes = nullptr;
        this->siguiente = nullptr;
    }
};

class Grafo
{
private:
    NodoGrafo *vertices;

    NodoGrafo *buscarVertice(string ciudad)
    {
        NodoGrafo *actual = vertices;
        while (actual != nullptr)
        {
            if (actual->ciudad == ciudad)
                return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    NodoGrafo *insertarVertice(string ciudad)
    {
        NodoGrafo *existe = buscarVertice(ciudad);
        if (existe != nullptr)
            return existe;

        NodoGrafo *nuevo = new NodoGrafo(ciudad);

        if (vertices == nullptr)
        {
            vertices = nuevo;
        }
        else
        {
            NodoGrafo *actual = vertices;
            while (actual->siguiente != nullptr)
                actual = actual->siguiente;
            actual->siguiente = nuevo;
        }

        return nuevo;
    }

    void insertarArista(NodoGrafo *origen, string destino, int peso)
    {
        Arista *nueva = new Arista(destino, peso);

        if (origen->adyacentes == nullptr)
        {
            origen->adyacentes = nueva;
        }
        else
        {
            Arista *actual = origen->adyacentes;
            while (actual->siguiente != nullptr)
                actual = actual->siguiente;
            actual->siguiente = nueva;
        }
    }

public:
    Grafo()
    {
        vertices = nullptr;
    }

    void agregarRuta(string origen, string destino, int distancia)
    {
        NodoGrafo *nodoOrigen = insertarVertice(origen);
        insertarVertice(destino);
        insertarArista(nodoOrigen, destino, distancia);
    }

    void mostrar()
    {
        cout << "\n=== Grafo de Rutas ===" << endl;

        NodoGrafo *actual = vertices;
        while (actual != nullptr)
        {
            cout << actual->ciudad << " -> ";
            Arista *arista = actual->adyacentes;
            while (arista != nullptr)
            {
                cout << arista->destino << "(" << arista->peso << "km) ";
                arista = arista->siguiente;
            }
            cout << endl;
            actual = actual->siguiente;
        }
    }

    void rutaMasCorta(string origen, string destino)
    {
        // Validar existencia de origen y destino
        if (buscarVertice(origen) == nullptr)
        {
            cout << "No existe la ciudad origen: " << origen << endl;
            return;
        }
        if (buscarVertice(destino) == nullptr)
        {
            cout << "No existe la ciudad destino: " << destino << endl;
            return;
        }

        // Dijkstra usando priority_queue (min-heap)
        map<string, int> dist;
        map<string, string> prev;

        NodoGrafo *actual = vertices;
        while (actual != nullptr)
        {
            dist[actual->ciudad] = numeric_limits<int>::max();
            prev[actual->ciudad] = "";
            actual = actual->siguiente;
        }

        using Par = pair<int, string>;
        priority_queue<Par, vector<Par>, greater<Par>> pq;

        dist[origen] = 0;
        pq.push(make_pair(0, origen));

        while (!pq.empty())
        {
            auto [d, ciudad] = pq.top();
            pq.pop();

            if (d > dist[ciudad])
                continue;

            if (ciudad == destino)
                break;

            NodoGrafo *nodo = buscarVertice(ciudad);
            if (nodo == nullptr)
                continue;

            Arista *ar = nodo->adyacentes;
            while (ar != nullptr)
            {
                int nd = d + ar->peso;
                if (nd < dist[ar->destino])
                {
                    dist[ar->destino] = nd;
                    prev[ar->destino] = ciudad;
                    pq.push(make_pair(nd, ar->destino));
                }
                ar = ar->siguiente;
            }
        }

        if (dist[destino] == numeric_limits<int>::max())
        {
            cout << "No existe ruta entre " << origen << " y " << destino << endl;
            return;
        }

        cout << "\n=== Ruta más corta ===" << endl;
        cout << "Distancia total: " << dist[destino] << " km" << endl;
        cout << "Ruta: ";

        vector<string> ruta;
        string u = destino;
        while (u != "")
        {
            ruta.push_back(u);
            u = prev[u];
        }

        for (int i = ruta.size() - 1; i >= 0; i--)
        {
            cout << ruta[i];
            if (i > 0)
                cout << " -> ";
        }
        cout << endl;
    }

    void generarReporte(string nombreArchivo, string titulo)
    {
        if (vertices == nullptr)
        {
            cout << "El grafo está vacío, no se puede generar el reporte." << endl;
            return;
        }

        ofstream archivo;
        archivo.open(nombreArchivo + ".dot", ios::out);

        archivo << "digraph G {" << endl;
        archivo << "rankdir=LR;" << endl;
        archivo << "node [shape=circle];" << endl;
        archivo << "label=\"" << titulo << "\";" << endl;
        archivo << "labelloc=\"t\";" << endl;
        archivo << endl;

        NodoGrafo *actual = vertices;
        while (actual != nullptr)
        {
            Arista *arista = actual->adyacentes;
            while (arista != nullptr)
            {
                archivo << "\"" << actual->ciudad << "\" -> \"" << arista->destino << "\"";
                archivo << " [label=\"" << arista->peso << "km\"];" << endl;
                arista = arista->siguiente;
            }
            actual = actual->siguiente;
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

    ~Grafo() {}
};

#endif
