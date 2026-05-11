# 🎬 Sistema Multimedia Modular en C++

Proyecto académico desarrollado en C++ inspirado en plataformas tipo Netflix, aplicando arquitectura modular, Programación Orientada a Objetos (OOP), estructuras de datos personalizadas y manejo manual de memoria.

El sistema implementa funcionalidades de catálogo multimedia, autenticación, favoritos persistentes, logging, rankings y recomendaciones utilizando estructuras propias y algoritmos de ordenamiento custom.

---

# 🚀 Características

## 📚 Catálogo Multimedia

- Gestión de películas y series
- Búsqueda por título
- Filtrado por género
- Vista detallada de contenido
- Top 10 de favoritos

## 👤 Sistema de Usuarios

- Registro de usuarios
- Login/logout
- Roles:
  - USER
  - ADMIN

## ❤️ Favoritos

- Agregar contenido a favoritos
- Persistencia en archivo
- Rehidratación automática
- Ranking por popularidad

## 🎧 Reproductor

- Cola de reproducción FIFO
- Simulación de reproducción multimedia

## 📜 Logging

- Registro de acciones del sistema
- Persistencia de logs
- Auditoría básica de usuarios

## 🧠 Arquitectura y algoritmos

- Arquitectura modular por capas
- MergeSort
- HeapSort
- QuickSort
- Listas doblemente enlazadas
- Pilas y colas personalizadas
- Manejo manual de memoria
- Polimorfismo, herencia y abstracción

---

# 🏗️ Arquitectura del Proyecto

```txt
app/
core/
infra/
ui/
helpers/
data/
```

## 📦 Capas

### core/

Lógica de negocio principal:

- catálogo
- multimedia
- usuarios
- favoritos
- reproductor
- algoritmos
- estructuras de datos

### infra/

Infraestructura técnica:

- logging
- utilidades de consola
- manejo de input

### ui/

Interfaz de usuario en consola.

### data/

Persistencia mediante archivos CSV/TXT.

---

# 📂 Estructura Principal

```txt
core/
├── algorithms/
├── catalogue/
├── favorites/
├── reproductor/
├── structures/
├── users/

infra/
├── input/
├── logs/
├── utils/

ui/
└── CatalogoUI

data/
├── multimedia.csv
├── personas.csv
├── media_actors.csv
├── users.txt
├── favorites.txt
├── logs.txt
```

---

# ⚙️ Requisitos

## Windows

- MinGW32 / g++
- make

## macOS

- Xcode Command Line Tools
- clang++
- make

## Linux

- g++ o clang++
- make

---

# ▶️ Compilar y ejecutar

## Compilar

```bash
make
```

## Ejecutar

```bash
make run
```

## Limpiar archivos compilados

```bash
make clean
```

---

# 🖥️ Compatibilidad

Probado en:

- Windows (MinGW32)
- macOS (Xcode / clang++)
- Linux (make + g++/clang++)

---

# 🧩 Conceptos aplicados

- Programación Orientada a Objetos (OOP)
- Arquitectura modular
- Manejo manual de memoria
- Ownership y lifecycle
- Polimorfismo y abstracción
- Persistencia de datos
- Parsing CSV
- Algoritmos de ordenamiento
- Estructuras de datos personalizadas
- Diseño orientado a backend

---

# 👨‍💻 Objetivo del Proyecto

Aplicar fundamentos de ingeniería de software y backend development utilizando C++ desde bajo nivel, implementando un sistema modular completo sin frameworks externos.

---

# 📌 Estado del Proyecto

✅ Funcional
✅ Modularizado
✅ Persistencia implementada
✅ Sistema de usuarios
✅ Favoritos y rankings
✅ Logging
✅ Recomendaciones
✅ Compatibilidad multiplataforma

---

# 👥 Autores

Proyecto académico desarrollado para el curso de Programación Orientada a Objetos / Estructuras de Datos.

Universidad Peruana de Ciencias Aplicadas (UPC)
