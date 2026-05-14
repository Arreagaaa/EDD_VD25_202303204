#include "PilotoController.h"
#include "MatrizController.h"
#include "AvionController.h"

#include <iostream>
using namespace std;

void PilotoController::darDeBaja(string id)
{
    Piloto *pilotoHash = tablaPorID->buscar(id);
    if (pilotoHash != nullptr)
    {
        int horasVuelo = pilotoHash->getHorasVuelo();
        string nombreCompleto = pilotoHash->getNombre() + " " + pilotoHash->getApellido();

        // Eliminar del Arbol AVL y obtener el puntero al Piloto eliminado para liberarlo
        Piloto *pilotoAVL = arbolHorasVuelo->eliminar(horasVuelo, id);

        // Eliminar la copia en la tabla hash (esto liberará la copia allí almacenada)
        tablaPorID->eliminar(id);

        // Si la eliminación del AVL devolvió un puntero, liberarlo para evitar fugas
        if (pilotoAVL != nullptr)
        {
            delete pilotoAVL;
        }

        cout << "[+] Piloto " << id << " (" << nombreCompleto << ") dado de baja de AVL y Hash" << endl;
        cout << "    [Nota] Matriz se actualizara si esta configurada" << endl;
        if (matrizController != nullptr)
        {
            matrizController->eliminarPilotoDeMatriz(id);
        }
    }
    else
    {
        cout << "[-] Piloto " << id << " no encontrado" << endl;
    }
}

void PilotoController::asignarPilotosAMatriz(AvionController *avionCtrl)
{
    if (matrizController == nullptr)
    {
        cout << "[!] Matriz no configurada, no se pueden asignar pilotos." << endl;
        return;
    }

    auto pilotos = tablaPorID->obtenerTodos();
    int asignados = 0;
    for (auto p : pilotos)
    {
        if (p == nullptr)
            continue;
        string vuelo = p->getVuelo();
        if (vuelo.empty())
            continue;

        string ciudad = avionCtrl->obtenerCiudadDestinoPorVuelo(vuelo);
        if (!ciudad.empty())
        {
            matrizController->asignarVuelo(p->getId(), vuelo, ciudad);
            asignados++;
        }
    }

    cout << "[+] Pilotos asignados a matriz: " << asignados << endl;
}