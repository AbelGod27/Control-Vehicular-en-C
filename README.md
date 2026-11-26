# Sistema de Control Vehicular

Proyecto de la materia **Sistemas Operativos** – ESCOM (IPN).
Autor: Abel Pineda Godinez.

Sistema en lenguaje C para Linux (Ubuntu) que registra propietarios (alumnos,
docentes, PAAE, visitantes, etc.), sus vehículos (autos, motos, bicicletas,
scooters) y las entradas y salidas del plantel.

## Arquitectura

- Cliente–servidor **sin sockets y sin base de datos**.
- Comunicación entre procesos con **memoria compartida POSIX** y **semáforos**.
- El servidor atiende a cada cliente con un **hilo** (pthreads).
- Solo el servidor lee y escribe los **archivos de texto** de `datos/` y la bitácora.
- Validación de todos los campos con **expresiones regulares** (`<regex.h>`).
- Cliente con interfaz **ncurses responsiva** (se adapta al tamaño de la terminal).

## Archivos

| Archivo | Qué contiene |
|---|---|
| `comun.h` / `comun.c` | Estructuras, constantes y validaciones con regex |
| `memoria.h` / `memoria.c` | Memoria compartida y semáforos |
| `archivos.h` / `archivos.c` | Lectura y escritura de los .txt (solo servidor) |
| `interfaz.h` / `interfaz.c` | Funciones reutilizables de ncurses (cliente) |
| `servidor.c` | Programa servidor |
| `cliente.c` | Programa cliente |
| `pruebas/` | Programas de prueba propios |
| `datos/` | Archivos de datos .txt (no se suben a git) |
| `Makefile` | Reglas de compilación (pendiente, tarea 1.3) |

## Requisitos

En Ubuntu (o WSL):

```
sudo apt install build-essential git libncurses-dev libcrypt-dev
```

## Cómo compilar y ejecutar

Se compila con `make`, sin advertencias (`-Wall -Wextra -Wpedantic -Werror -std=c11`):

```
make            # compila servidor y cliente
./servidor      # en una terminal
./cliente       # en otra terminal (puede haber varios)
make clean      # borra ejecutables y archivos .o
```

## Formato de los archivos de datos

Un registro por línea, campos separados por `|`. Ejemplo de `propietarios.txt`:

```
1|ALUMNO|2023630145|Abel|Pineda Godinez|5512345678|abel@ipn.mx|ESCOM
```

(El formato completo de cada archivo se documenta en la tarea 2.1.)
