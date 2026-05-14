# 🛫 Sistema de Gestión de Aeropuerto

**Universidad de San Carlos de Guatemala**  
**Facultad de Ingeniería**  
**Escuela de Ciencias y Sistemas**  
**Estructuras de Datos - Sección A**  
**Carné:** 202303204  
**Proyecto:** Práctica EDD - Sistema de Gestión de Aeropuerto

---

## 📋 Descripción General

Sistema de gestión aeroportuaria desarrollado en C++ que simula las operaciones de un aeropuerto, permitiendo administrar aviones, pasajeros y equipajes mediante estructuras de datos lineales implementadas desde cero. El sistema procesa archivos de entrada, ejecuta movimientos operacionales y genera reportes gráficos automáticos utilizando Graphviz.

---

## ✨ Características Principales

### Gestión de Aviones
- ✅ Carga de aviones desde archivo JSON
- ✅ Clasificación automática por estado (Disponible/Mantenimiento)
- ✅ Listas circulares dobles para cada estado
- ✅ Movimientos entre listas mediante comandos
- ✅ Visualización bidireccional de conexiones

### Gestión de Pasajeros
- ✅ Carga masiva desde archivo JSON
- ✅ Cola de registro simulando ventanilla
- ✅ Lista doble ordenada de pasajeros registrados
- ✅ Ordenamiento automático por número de vuelo y asiento
- ✅ Consulta rápida por número de pasaporte

### Gestión de Equipajes
- ✅ Pila de equipajes por orden de llegada
- ✅ Procesamiento automático desde cola de pasajeros
- ✅ Validación de pasajeros sin equipaje
- ✅ Contador de piezas por pasajero

### Sistema de Reportes
- ✅ Generación automática de archivos `.dot` (Graphviz)
- ✅ Conversión automática a imágenes `.png`
- ✅ **Apertura automática de reportes** desde la aplicación
- ✅ 5 tipos de reportes visuales:
  - Aviones disponibles
  - Aviones en mantenimiento
  - Cola de registro
  - Pila de equipajes
  - Pasajeros registrados

---

## 🛠️ Requisitos del Sistema

### Software Necesario
- **Sistema Operativo:** Windows 10/11
- **Compilador:** MinGW-w64 con soporte C++17 (`g++`)
- **Graphviz:** Versión 2.44 o superior
- **Git:** Para control de versiones (opcional)

### Dependencias Incluidas
- `nlohmann/json` (header-only) - Procesamiento de archivos JSON
- Estructuras de datos personalizadas (implementación propia)

---

## 📁 Estructura del Proyecto

```
202303204_EDD_Practica/
├── data/                          # Archivos de entrada
│   ├── aviones.json              # Catálogo de aviones
│   ├── pasajeros.json            # Registro de pasajeros
│   └── movimientos.txt           # Comandos de operación
├── docs/                          # Documentación
│   ├── MANUAL_TECNICO.md         # Manual técnico detallado
│   └── GUIA_CONVERSION_PDF.md    # Guía de conversión a PDF
├── reportes-generados/            # Reportes Graphviz
│   ├── aviones_disponibles.dot/.png
│   ├── aviones_mantenimiento.dot/.png
│   ├── cola_registro.dot/.png
│   ├── pasajeros_registrados.dot/.png
│   └── pila_equipajes.dot/.png
├── src/                           # Código fuente
│   ├── main.cpp                  # Punto de entrada
│   ├── Menu.h / Menu.cpp         # Interfaz de usuario
│   ├── compile.bat               # Script de compilación
│   ├── controllers/              # Controladores
│   │   ├── AvionController.h
│   │   ├── PasajeroController.h
│   │   ├── EquipajeController.h
│   │   └── MovimientosController.h
│   ├── models/                   # Modelos de datos
│   │   ├── Avion.h
│   │   ├── Pasajero.h
│   │   └── Equipaje.h
│   ├── estructuras/              # Estructuras de datos
│   │   ├── Nodo.h
│   │   ├── ListaCircularDoble.h
│   │   ├── ListaDoble.h
│   │   ├── Cola.h
│   │   └── Pila.h
│   └── json/                     # Utilidades JSON
│       ├── json.hpp
│       └── JsonParser.h
└── README.md                      # Este archivo
```

---

## 🚀 Compilación y Ejecución

### Opción 1: Script de Compilación (Recomendado)
```bash
cd src
compile.bat
```

### Opción 2: Compilación Manual
```bash
cd src
g++ -std=c++17 -fdiagnostics-color=always -g ^
    main.cpp Menu.cpp ^
    -o aeropuerto.exe
```

### Ejecución
```bash
aeropuerto.exe
```

---

## 📖 Guía de Uso

### Menú Principal
Al ejecutar el sistema, se presenta el siguiente menú:

```
======================================================
         SISTEMA DE GESTION DE AEROPUERTO
======================================================
1. Cargar aviones
2. Cargar pasajeros
3. Cargar movimientos
4. Consultar pasajero
5. Visualizar reportes
0. Salir
======================================================
```

### Flujo Recomendado
1. **Cargar aviones** (Opción 1)
   - Busca automáticamente archivos con "avion" en `../data/`
   - Clasifica por estado: Disponible/Mantenimiento

2. **Cargar pasajeros** (Opción 2)
   - Busca automáticamente archivos con "pasajero" en `../data/`
   - Agrega a cola de registro

3. **Cargar movimientos** (Opción 3)
   - Busca automáticamente archivos con "movimiento" en `../data/`
   - Ejecuta comandos:
     - `IngresoEquipajes`: Registra pasajero y apila equipaje
     - `MantenimientoAviones;Ingreso/Salida;N50XXX`: Mueve avión entre listas

4. **Consultar pasajero** (Opción 4)
   - Ingrese número de pasaporte (ej: `P90000000`)
   - Muestra información completa si está registrado

5. **Visualizar reportes** (Opción 5)
   - Genera y **abre automáticamente** los 5 reportes PNG

---

## 🧩 Estructuras de Datos Implementadas

### 1. Lista Circular Doble (`ListaCircularDoble<T>`)
- **Uso:** Aviones disponibles y en mantenimiento
- **Características:**
  - Navegación bidireccional
  - Conexión circular (último → primero)
  - Inserción/eliminación O(n)
  - Reporte con flechas azules para enlaces inversos

### 2. Cola (`Cola<T>`)
- **Uso:** Pasajeros en espera de registro
- **Características:**
  - FIFO (First In, First Out)
  - Operaciones: encolar, desencolar, frente
  - Complejidad O(1) en ambas operaciones

### 3. Lista Doble Ordenada (`ListaDoble<T>`)
- **Uso:** Pasajeros registrados
- **Características:**
  - Ordenamiento automático por vuelo + asiento
  - Búsqueda por pasaporte
  - Navegación bidireccional

### 4. Pila (`Pila<T>`)
- **Uso:** Equipajes de pasajeros
- **Características:**
  - LIFO (Last In, First Out)
  - Operaciones: apilar, desapilar, tope
  - Complejidad O(1)

---

## 📊 Formatos de Archivos de Entrada

### aviones.json
```json
[
  {
    "vuelo": "A100",
    "numero_de_registro": "N50000",
    "modelo": "Boeing 747",
    "fabricante": "Boeing",
    "ano_fabricacion": 2015,
    "capacidad": 416,
    "peso_max_despegue": 412775,
    "aerolinea": "AeroGT",
    "estado": "Disponible"
  }
]
```

### pasajeros.json
```json
[
  {
    "nombre": "Carlos García",
    "nacionalidad": "Guatemalteco",
    "numero_de_pasaporte": "P90000000",
    "vuelo": "A100",
    "asiento": 15,
    "destino": "Madrid",
    "origen": "Guatemala",
    "equipaje_facturado": 2
  }
]
```

### movimientos.txt
```
MantenimientoAviones;Salida;N50030
MantenimientoAviones;Ingreso;N50008
IngresoEquipajes
IngresoEquipajes
MantenimientoAviones;Ingreso;N50012
```

---

## 📸 Reportes Generados

Los reportes se almacenan en `reportes-generados/` con doble formato:

| Reporte | Archivo DOT | Archivo PNG |
|---------|-------------|-------------|
| Aviones disponibles | `aviones_disponibles.dot` | `aviones_disponibles.png` |
| Aviones mantenimiento | `aviones_mantenimiento.dot` | `aviones_mantenimiento.png` |
| Cola de registro | `cola_registro.dot` | `cola_registro.png` |
| Pasajeros registrados | `pasajeros_registrados.dot` | `pasajeros_registrados.png` |
| Pila de equipajes | `pila_equipajes.dot` | `pila_equipajes.png` |

**Nota:** Los reportes PNG se abren automáticamente al generarse.

---

## 🎯 Cumplimiento de Requisitos

| Requisito | Estado |
|-----------|--------|
| Lenguaje C++ | ✅ |
| Estructuras propias (no STL) | ✅ |
| Graphviz para reportes | ✅ |
| Apertura automática de reportes | ✅ |
| Listas circulares dobles | ✅ |
| Colas y pilas | ✅ |
| Ordenamiento de pasajeros | ✅ |
| Procesamiento JSON | ✅ |
| Manual técnico | ✅ |

---

## 👨‍💻 Información del Desarrollador

**Estudiante:** [Nombre completo]  
**Carné:** 202303204  
**Curso:** Estructuras de Datos - Sección A  
**Catedrático:** Rene Ornelis  
**Auxiliar:** Daniel Monterroso  
**Ciclo:** Segundo Semestre 2025  
**Fecha:** Diciembre 2025

---

## 📄 Licencia

Este proyecto es de carácter académico y se desarrolla con fines educativos para el curso de Estructuras de Datos de la Universidad de San Carlos de Guatemala.

---

## 🔗 Referencias

- [Graphviz Documentation](https://graphviz.org/documentation/)
- [nlohmann/json GitHub](https://github.com/nlohmann/json)
- [C++ Reference](https://en.cppreference.com/)

---

**¡Proyecto completado exitosamente! ✈️**
