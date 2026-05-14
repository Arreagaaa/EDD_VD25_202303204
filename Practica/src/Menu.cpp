#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

Menu::Menu()
{
    avionCtrl = new AvionController();
    pasajeroCtrl = new PasajeroController();
    equipajeCtrl = new EquipajeController();
}

Menu::~Menu()
{
    delete avionCtrl;
    delete pasajeroCtrl;
    delete equipajeCtrl;
}

void Menu::mostrarMenuPrincipal()
{
    cout << "\n======================================================" << endl;
    cout << "         SISTEMA DE GESTION DE AEROPUERTO            " << endl;
    cout << "======================================================" << endl;
    cout << "1. Cargar aviones" << endl;
    cout << "2. Cargar pasajeros" << endl;
    cout << "3. Cargar movimientos" << endl;
    cout << "4. Consultar pasajero" << endl;
    cout << "5. Visualizar reportes" << endl;
    cout << "0. Salir" << endl;
    cout << "======================================================" << endl;
    cout << "Opcion: ";
}

void Menu::ejecutar()
{
    system("chcp 65001 > nul");
    int opcion = -1;

    do
    {
        mostrarMenuPrincipal();
        cin >> opcion;
        cin.ignore(); // limpiar buffer

        switch (opcion)
        {
        case 1:
        {
            cout << "\n======================================================" << endl;
            cout << "              CARGA DE AVIONES                       " << endl;
            cout << "======================================================" << endl;
            
            string rutaAviones = seleccionarArchivo("aviones", ".json");
            if (!rutaAviones.empty())
            {
                avionCtrl->cargarDatos(rutaAviones);
                avionCtrl->mostrarResumen();
            }
            
            cout << "\nPresione ENTER para continuar...";
            cin.get();
            break;
        }

        case 2:
        {
            cout << "\n======================================================" << endl;
            cout << "             CARGA DE PASAJEROS                      " << endl;
            cout << "======================================================" << endl;
            
            string rutaPasajeros = seleccionarArchivo("pasajeros", ".json");
            if (!rutaPasajeros.empty())
            {
                pasajeroCtrl->cargarDatos(rutaPasajeros);
                pasajeroCtrl->mostrarResumen();
            }
            
            cout << "\nPresione ENTER para continuar...";
            cin.get();
            break;
        }

        case 3:
        {
            cout << "\n======================================================" << endl;
            cout << "            CARGA DE MOVIMIENTOS                     " << endl;
            cout << "======================================================" << endl;
            
            string rutaMovimientos = seleccionarArchivo("movimientos", ".txt");
            if (!rutaMovimientos.empty())
            {
                MovimientosController::procesarArchivo(rutaMovimientos,
                                                       pasajeroCtrl,
                                                       equipajeCtrl,
                                                       avionCtrl);
                cout << "\n======================================================" << endl;
                cout << "         RESUMEN DESPUES DE MOVIMIENTOS              " << endl;
                cout << "======================================================" << endl;
                avionCtrl->mostrarResumen();
                pasajeroCtrl->mostrarResumen();
                equipajeCtrl->mostrarResumen();
            }
            
            cout << "\nPresione ENTER para continuar...";
            cin.get();
            break;
        }

        case 4:
        {
            cout << "\n======================================================" << endl;
            cout << "             CONSULTAR PASAJERO                      " << endl;
            cout << "======================================================" << endl;
            cout << "Ingrese numero de pasaporte: ";
            string pasaporte;
            getline(cin, pasaporte);

            Pasajero *pasajero = pasajeroCtrl->consultaPasaporte(pasaporte);

            if (pasajero != nullptr)
            {
                pasajero->mostrar();
            }

            cout << "\nPresione ENTER para continuar...";
            cin.get();
            break;
        }

        case 5:
            menuReportes();
            break;

        case 0:
            cout << "\n======================================================" << endl;
            cout << "         Gracias por usar el sistema                 " << endl;
            cout << "         Carne: 202303204                            " << endl;
            cout << "======================================================" << endl;
            break;

        default:
            cout << "\n[ERROR] Opcion invalida. Intente nuevamente.\n";
            cout << "\nPresione ENTER para continuar...";
            cin.get();
        }

    } while (opcion != 0);
}

void Menu::menuReportes()
{
    cout << "\n======================================================" << endl;
    cout << "            GENERACION DE REPORTES                   " << endl;
    cout << "======================================================" << endl;
    cout << "Generando todos los reportes Graphviz...\n"
         << endl;

    // Generar TODOS los reportes de una vez
    cout << "[1/5] Aviones Disponibles............... ";
    if (!avionCtrl->getAvionesDisponibles()->estaVacia())
    {
        avionCtrl->getAvionesDisponibles()->generarReporte(
            "../reportes-generados/aviones_disponibles",
            "Aviones Disponibles");
        cout << "OK" << endl;
    }
    else
    {
        cout << "VACIO" << endl;
    }

    cout << "[2/5] Aviones en Mantenimiento.......... ";
    if (!avionCtrl->getAvionesMantenimiento()->estaVacia())
    {
        avionCtrl->getAvionesMantenimiento()->generarReporte(
            "../reportes-generados/aviones_mantenimiento",
            "Aviones en Mantenimiento");
        cout << "OK" << endl;
    }
    else
    {
        cout << "VACIO" << endl;
    }

    cout << "[3/5] Cola de Registro................... ";
    if (!pasajeroCtrl->getColaRegistro()->estaVacia())
    {
        pasajeroCtrl->getColaRegistro()->generarReporte(
            "../reportes-generados/cola_registro",
            "Cola de Registro de Pasajeros");
        cout << "OK" << endl;
    }
    else
    {
        cout << "VACIO" << endl;
    }

    cout << "[4/5] Pasajeros Registrados.............. ";
    if (!pasajeroCtrl->getListaPasajeros()->estaVacia())
    {
        pasajeroCtrl->getListaPasajeros()->generarReporte(
            "../reportes-generados/pasajeros_registrados",
            "Pasajeros Registrados");
        cout << "OK" << endl;
    }
    else
    {
        cout << "VACIO" << endl;
    }

    cout << "[5/5] Pila de Equipajes.................. ";
    if (!equipajeCtrl->getPilaEquipaje()->estaVacia())
    {
        equipajeCtrl->getPilaEquipaje()->generarReporte(
            "../reportes-generados/pila_equipajes",
            "Pila de Equipajes");
        cout << "OK" << endl;
    }
    else
    {
        cout << "VACIO" << endl;
    }

    cout << "\n======================================================" << endl;
    cout << "Reportes generados en: reportes-generados/           " << endl;
    cout << "Archivos: .dot (Graphviz) y .png (Imagen)           " << endl;
    cout << "======================================================" << endl;
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

vector<string> Menu::buscarArchivos(const string &directorio, const string &extension, const string &filtroNombre)
{
    vector<string> archivos;
    
    try
    {
        if (fs::exists(directorio) && fs::is_directory(directorio))
        {
            for (const auto &entry : fs::directory_iterator(directorio))
            {
                if (entry.is_regular_file())
                {
                    string filename = entry.path().filename().string();
                    string ext = entry.path().extension().string();
                    
                    // Convertir a minúsculas para comparación
                    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                    string filenameLower = filename;
                    transform(filenameLower.begin(), filenameLower.end(), filenameLower.begin(), ::tolower);
                    
                    // Verificar extensión y filtro de nombre
                    bool coincideExtension = (ext == extension);
                    bool coincideNombre = filtroNombre.empty() || (filenameLower.find(filtroNombre) != string::npos);
                    
                    if (coincideExtension && coincideNombre)
                    {
                        archivos.push_back(entry.path().string());
                    }
                }
            }
        }
    }
    catch (...)
    {
        // Si hay error, devolver lista vacía
    }
    
    return archivos;
}

string Menu::seleccionarArchivo(const string &tipoArchivo, const string &extension)
{
    // Buscar archivos en data/
    // Para movimientos, aceptar CUALQUIER .txt (filtro vacío)
    // Para otros, filtrar por nombre
    string filtroNombre = "";
    if (tipoArchivo != "movimientos")
    {
        filtroNombre = tipoArchivo;
        transform(filtroNombre.begin(), filtroNombre.end(), filtroNombre.begin(), ::tolower);
    }
    vector<string> archivos = buscarArchivos("../data", extension, filtroNombre);
    
    // Si no hay archivos, pedir ruta manual
    if (archivos.empty())
    {
        cout << "\nNo se encontraron archivos " << extension << " en data/" << endl;
        cout << "Ingrese la ruta completa del archivo de " << tipoArchivo << ": ";
        string ruta;
        getline(cin, ruta);
        
        if (ruta.empty())
        {
            cout << "[ERROR] No se ingresó ninguna ruta." << endl;
            return "";
        }
        
        return ruta;
    }
    
    // Si solo hay un archivo, usarlo automáticamente
    if (archivos.size() == 1)
    {
        cout << "\nArchivo encontrado: " << archivos[0] << endl;
        return archivos[0];
    }
    
    // Si hay múltiples archivos, mostrar lista para elegir
    cout << "\nSe encontraron " << archivos.size() << " archivos " << extension << ":" << endl;
    for (size_t i = 0; i < archivos.size(); i++)
    {
        // Mostrar solo el nombre del archivo, no la ruta completa
        fs::path p(archivos[i]);
        cout << "  [" << (i + 1) << "] " << p.filename().string() << endl;
    }
    
    cout << "  [0] Ingresar ruta manualmente" << endl;
    cout << "\nSeleccione el archivo (1-" << archivos.size() << "): ";
    
    int opcion;
    cin >> opcion;
    cin.ignore();
    
    if (opcion == 0)
    {
        cout << "Ingrese la ruta completa del archivo: ";
        string ruta;
        getline(cin, ruta);
        return ruta.empty() ? "" : ruta;
    }
    
    if (opcion >= 1 && opcion <= (int)archivos.size())
    {
        return archivos[opcion - 1];
    }
    
    cout << "[ERROR] Opción inválida." << endl;
    return "";
}
