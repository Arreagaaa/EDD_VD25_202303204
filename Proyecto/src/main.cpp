#include <iostream>
#include <filesystem>
#include "controllers/AvionController.h"
#include "controllers/PilotoController.h"
#include "controllers/RutaController.h"
#include "controllers/MatrizController.h"
#include "controllers/ComandosController.h"

using namespace std;
namespace fs = std::filesystem;

void mostrarMenu();
void limpiarPantalla();

int main()
{
    system("chcp 65001 > nul");

    if (!fs::exists("reports"))
    {
        fs::create_directory("reports");
    }

    // Verificar si Graphviz (dot) está disponible
#ifdef _WIN32
    int dotRet = system("dot -V > nul 2>&1");
#else
    int dotRet = system("dot -V > /dev/null 2>&1");
#endif
    if (dotRet != 0)
    {
        cout << "[!] Aviso: Graphviz (dot) no parece estar instalado o no está en PATH. Los archivos .dot se generarán pero no se podrán convertir a PNG." << endl;
    }

    // Rutas de archivos (por defecto)
    string avionesPath = "../data/aviones.json";
    string pilotosPath = "../data/pilotos.json";
    string rutasPath = "../data/rutas.txt";
    string comandosPath = "../data/movimientos.txt";

    AvionController *avionCtrl = new AvionController();
    PilotoController *pilotoCtrl = new PilotoController();
    RutaController *rutaCtrl = new RutaController();
    MatrizController *matrizCtrl = new MatrizController(pilotoCtrl);

    pilotoCtrl->setMatrizController(matrizCtrl);

    ComandosController *comandosCtrl = new ComandosController(avionCtrl, pilotoCtrl, matrizCtrl);

    bool avionesCargados = false;
    bool pilotosCargados = false;
    bool rutasCargadas = false;
    bool comandosCargados = false;
    int opcion;

    do
    {
        mostrarMenu();
        cout << "Ingrese opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
        {
            cout << "\n=== CARGA DE AVIONES ===" << endl;
            if (!fs::exists(avionesPath))
            {
                cout << "[!] Archivo no encontrado: " << avionesPath << "\n    Coloque el archivo con ese nombre en ../data/ o ajuste el nombre del archivo en el directorio de datos." << endl;
                break;
            }
            cout << "Archivo usado: " << avionesPath << endl;
            avionCtrl->cargarDesdeJSON(avionesPath);
            avionesCargados = true;
            // Si ya están cargados los pilotos, asignarlos automáticamente a la matriz
            if (pilotosCargados)
            {
                pilotoCtrl->asignarPilotosAMatriz(avionCtrl);
            }
            break;
        }
        case 2:
        {
            cout << "\n=== CARGA DE PILOTOS ===" << endl;
            if (!fs::exists(pilotosPath))
            {
                cout << "[!] Archivo no encontrado: " << pilotosPath << "\n    Coloque el archivo con ese nombre en ../data/ o ajuste el nombre del archivo en el directorio de datos." << endl;
                break;
            }
            cout << "Archivo usado: " << pilotosPath << endl;
            pilotoCtrl->cargarDesdeJSON(pilotosPath);
            pilotosCargados = true;
            // Si ya están cargados los aviones, asignar los pilotos automáticamente a la matriz
            if (avionesCargados)
            {
                pilotoCtrl->asignarPilotosAMatriz(avionCtrl);
            }
            break;
        }
        case 3:
        {
            cout << "\n=== CARGA DE RUTAS ===" << endl;
            if (!fs::exists(rutasPath))
            {
                cout << "[!] Archivo no encontrado: " << rutasPath << "\n    Coloque el archivo con ese nombre en ../data/ o ajuste el nombre del archivo en el directorio de datos." << endl;
                break;
            }
            cout << "Archivo usado: " << rutasPath << endl;
            rutaCtrl->cargarDesdeArchivo(rutasPath);
            rutasCargadas = true;
            break;
        }
        case 4:
        {
            if (!avionesCargados && !pilotosCargados && !rutasCargadas)
            {
                cout << "\n[!] Cargue al menos los archivos necesarios antes de procesar movimientos." << endl;
                break;
            }
            cout << "\n=== CARGA DE MOVIMIENTOS ===" << endl;
            if (!fs::exists(comandosPath))
            {
                cout << "[!] Archivo no encontrado: " << comandosPath << "\n    Coloque el archivo con ese nombre en ../data/ o ajuste el nombre del archivo en el directorio de datos." << endl;
                break;
            }
            cout << "Archivo usado: " << comandosPath << endl;
            comandosCtrl->cargarDesdeArchivo(comandosPath);
            comandosCargados = true;
            break;
        }
        case 5:
        {
            if (!pilotosCargados)
            {
                cout << "\n[!] Debe cargar los pilotos primero (Opcion 2)" << endl;
                break;
            }
            cout << "\n=== CONSULTA HORAS DE VUELO (RECORRIDOS) ===" << endl;
            cout << "1. Preorden" << endl;
            cout << "2. Inorden" << endl;
            cout << "3. Postorden" << endl;
            cout << "Seleccione recorrido: ";
            int rec;
            cin >> rec;
            cin.ignore();

            switch (rec)
            {
            case 1:
                pilotoCtrl->recorridoPreorden();
                break;
            case 2:
                pilotoCtrl->recorridoInorden();
                break;
            case 3:
                pilotoCtrl->recorridoPostorden();
                break;
            default:
                cout << "Opcion invalida" << endl;
            }
            break;
        }
        case 6:
        {
            if (!rutasCargadas)
            {
                cout << "\n[!] Debe cargar las rutas primero (Opcion 3)" << endl;
                break;
            }
            string origen, destino;
            cout << "\n=== RUTA MAS CORTA ===" << endl;
            cout << "Ciudad origen: ";
            getline(cin, origen);
            cout << "Ciudad destino: ";
            getline(cin, destino);
            rutaCtrl->calcularRutaMasCorta(origen, destino);
            break;
        }
        case 7:
        {
            cout << "\n[+] Generando todos los reportes..." << endl;

            if (avionesCargados)
            {
                avionCtrl->reporteDisponibles();
                avionCtrl->reporteMantenimiento();
            }

            if (pilotosCargados)
            {
                pilotoCtrl->reporteArbolAVL();
                pilotoCtrl->reporteTablaHash();
            }

            if (rutasCargadas)
            {
                rutaCtrl->reporteGrafo();
            }

            matrizCtrl->reporteMatriz();

            cout << "[+] Todos los reportes generados!" << endl;
            break;
        }
        case 8:
            cout << "\n[!] Saliendo del sistema..." << endl;
            break;
        default:
            cout << "\n[-] Opcion invalida. Intente de nuevo." << endl;
        }

        if (opcion != 8)
        {
            cout << "\nPresione ENTER para continuar...";
            cin.get();
        }

    } while (opcion != 8);

    delete avionCtrl;
    delete pilotoCtrl;
    delete rutaCtrl;
    delete matrizCtrl;
    delete comandosCtrl;

    return 0;
}

void mostrarMenu()
{
    limpiarPantalla();
    cout << "=====================================================================" << endl;
    cout << "               FACULTAD DE INGENIERIA" << endl;
    cout << "                ESTRUCTURAS DE DATOS" << endl;
    cout << "                Carne: 202303204" << endl;
    cout << "=====================================================================" << endl;
    cout << endl;
    cout << "         SISTEMA DE GESTION DE AEROPUERTO - PROYECTO" << endl;
    cout << endl;
    cout << "=====================================================================" << endl;
    cout << "  1. Cargar Aviones" << endl;
    cout << "  2. Cargar Pilotos" << endl;
    cout << "  3. Cargar Rutas" << endl;
    cout << "  4. Cargar Movimientos" << endl;
    cout << "  5. Consulta de Horas de Vuelo (Pilotos)" << endl;
    cout << "  6. Recomendar Ruta" << endl;
    cout << "  7. Visualizar Reportes (generar todos)" << endl;
    cout << "  8. Salir" << endl;
    cout << "=====================================================================" << endl;
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
