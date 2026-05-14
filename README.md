# 📚 Estructuras de Datos - EDD VD25

**Universidad de San Carlos de Guatemala**  
**Facultad de Ingeniería**  
**Escuela de Ciencias y Sistemas**  
**Curso:** Estructuras de Datos - Sección A  
**Carné:** 202303204  
**Ciclo:** Segundo Semestre 2025

---

## 📖 Descripción del Curso

Este repositorio contiene todos los trabajos y proyectos desarrollados en el curso **Estructuras de Datos (EDD)**, donde se estudian las estructuras de datos fundamentales en ciencias de la computación y sus aplicaciones prácticas mediante proyectos en **C++**.

### Objetivos del Curso
✅ Comprender los conceptos fundamentales de estructuras de datos  
✅ Implementar estructuras de datos desde cero (sin STL)  
✅ Analizar la complejidad temporal y espacial de algoritmos  
✅ Aplicar estructuras de datos en proyectos reales  
✅ Generar reportes visuales usando Graphviz  

---

## 🎓 Temas Principales Aprendidos

### 1. **Estructuras Lineales**
- **Listas Simples** - Inserción, eliminación, búsqueda
- **Listas Dobles** - Navegación bidireccional
- **Listas Circulares** - Conexiones cíclicas
- **Listas Circulares Dobles** - Combinación de ambas características

### 2. **Estructuras Especializadas**
- **Colas (Queue)** - FIFO (First In, First Out)
- **Pilas (Stack)** - LIFO (Last In, First Out)
- **Operaciones:** Push, Pop, Peek, isEmpty, isFull

### 3. **Manejo de Datos**
- Parsing de archivos JSON con `nlohmann/json`
- Lectura y procesamiento de archivos de entrada
- Almacenamiento y serialización de estructuras

### 4. **Visualización de Datos**
- Generación de archivos `.dot` (Graphviz)
- Convertir grafos a imágenes PNG
- Representación visual de estructuras de datos
- Apertura automática de reportes

### 5. **Programación en C++**
- Templates y programación genérica
- Manejo de memoria (new, delete)
- Punteros y referencias
- Archivos batch para compilación

---

## 📁 Estructura del Repositorio

```
EDD_VD25_202303204/
│
├── Practica/
│   ├── src/                    # Código fuente (C++)
│   │   ├── estructuras/        # Implementación de estructuras de datos
│   │   ├── models/             # Modelos de datos (Avion, Pasajero, etc)
│   │   ├── controllers/        # Controladores de lógica
│   │   └── main.cpp            # Punto de entrada
│   ├── data/                   # Archivos de entrada (JSON, TXT)
│   ├── reportes-generados/     # Reportes visuales (PNG, DOT)
│   ├── docs/                   # Documentación técnica
│   └── README.md               # Documentación de la práctica
│
├── Proyecto/
│   ├── src/                    # Código fuente del proyecto final
│   ├── data/                   # Datos de prueba
│   ├── reportes/               # Reportes generados
│   └── README.md               # Documentación del proyecto
│
└── README.md                   # Este archivo (resumen general)
```

---

## 🛫 Proyectos Incluidos

### **Práctica - Sistema de Gestión de Aeropuerto**

**Descripción:** Sistema completo de aeropuerto que gestiona aviones, pasajeros y equipajes usando estructuras de datos lineales.

**Características principales:**
- 🛩️ Gestión de aviones (Disponibles/Mantenimiento) - Listas Circulares Dobles
- 👥 Registro de pasajeros - Cola + Lista Doble Ordenada
- 🧳 Gestión de equipajes - Pila
- 📊 5 tipos de reportes visuales automáticos
- 📝 Procesamiento de archivos JSON

**Estructuras usadas:**
- `ListaCircularDoble<T>` - Aviones
- `Cola<T>` - Pasajeros pendientes
- `ListaDoble<T>` - Pasajeros registrados
- `Pila<T>` - Equipajes

**Ubicación:** [Practica/](Practica/)

---

### **Proyecto Final - [Nombre del Proyecto]**

**Descripción:** [Por completar con detalles del proyecto final]

**Ubicación:** [Proyecto/](Proyecto/)

---

## 🛠️ Tecnologías Utilizadas

| Tecnología | Descripción | Versión |
|-----------|-------------|---------|
| **C++** | Lenguaje de programación | C++17 |
| **MinGW-w64** | Compilador | GCC |
| **Graphviz** | Visualización de grafos | 2.44+ |
| **nlohmann/json** | Procesamiento JSON | v3.11+ |
| **Batch** | Scripts de compilación | Windows |

---

## 💡 Conceptos Clave Aprendidos

### Complejidad Computacional
- **Análisis O(n)** - Operaciones en estructuras lineales
- **Operaciones O(1)** - Colas y pilas (frente/tope)
- **Búsqueda y ordenamiento** - Impacto en rendimiento

### Patrones de Diseño
- **Patrón MVC** - Separación Modelo-Vista-Controlador
- **Templates en C++** - Código genérico y reutilizable
- **Gestión de memoria** - Pointers y dynamic allocation

### Mejores Prácticas
- ✅ Código modular y bien organizado
- ✅ Documentación clara de estructuras
- ✅ Implementación sin STL (aprendizaje desde cero)
- ✅ Validación y manejo de errores
- ✅ Generación de reportes visuales

---

## 🚀 Cómo Usar Este Repositorio

### Explorar la Práctica
```bash
cd Practica
cat README.md  # Ver documentación completa
```

### Compilar y ejecutar
```bash
cd Practica/src
compile.bat  # Windows
# o
g++ -std=c++17 main.cpp Menu.cpp -o aeropuerto.exe
./aeropuerto.exe
```

### Ver reportes
Los reportes PNG se generan automáticamente en `reportes-generados/`

---

## 📊 Resumen de Aprendizaje

### ✅ Competencias Desarrolladas
1. **Implementación de estructuras de datos** desde cero
2. **Programación orientada a objetos** en C++
3. **Procesamiento de datos** desde archivos externos
4. **Visualización de datos** con Graphviz
5. **Análisis de algoritmos** y complejidad

### ✅ Habilidades Prácticas
- Compilación y depuración en C++
- Trabajo con templates y genéricos
- Manejo de archivos JSON
- Generación de reportes visuales
- Documentación técnica profesional

### ✅ Entrega de Proyectos
| Proyecto | Estado | Documentación |
|----------|--------|---------------|
| Práctica - Aeropuerto | ✅ Completo | [Ver](Practica/README.md) |
| Proyecto Final | 🔄 Desarrollo | [Ver](Proyecto/README.md) |

---

## 📚 Recursos y Referencias

- [Graphviz Documentation](https://graphviz.org/documentation/)
- [nlohmann/json - GitHub](https://github.com/nlohmann/json)
- [C++ Reference](https://en.cppreference.com/)
- [Análisis de Complejidad](https://en.wikipedia.org/wiki/Big_O_notation)

---

## 👨‍💻 Información

**Estudiante:** Arreagaaa  
**Carné:** 202303204  
**Catedrático:** Rene Ornelis  
**Auxiliar:** Daniel Monterroso  
**Ciclo:** Segundo Semestre 2025  
**Fecha de Actualización:** Mayo 2026

---

## 📄 Licencia

Este proyecto es de carácter académico desarrollado con fines educativos para el curso de Estructuras de Datos de la Universidad de San Carlos de Guatemala.

---

**¡Repositorio de aprendizaje en Estructuras de Datos completado! 🎓📚**
