# Lista de tareas – Sistema de Control Vehicular

Cada tarea es pequeña. Al terminar cada una: compilar sin advertencias,
probar, hacer commit en git y marcarla aquí cambiando `[ ]` por `[x]`.

## FASE 0 – PREPARACIÓN

- [ ] **0.1** Instalar herramientas en Ubuntu: build-essential, git, libncurses-dev, libcrypt-dev. Comprobar con gcc --version.
- [ ] **0.2** Crear el repositorio git y la estructura que genere Claude.
- [ ] **0.3** Repasar: qué es un proceso, un hilo, memoria compartida y un semáforo (explicación de Claude + mis propias notas).

## FASE 1 – BASES EN C Y MAKEFILE

- [ ] **1.1** "Hola mundo" compilado a mano con gcc y las banderas -Wall -Wextra -Wpedantic -Werror -std=c11.
- [ ] **1.2** Entender compilación por partes: gcc -c (archivo .o) y enlazado.
- [ ] **1.3** Escribir MI Makefile: regla por cada .o, reglas servidor, cliente, all y clean.
- [ ] **1.4** comun.h: definir las estructuras Propietario, Vehiculo, Usuario y Movimiento, y las constantes de tamaño.
- [ ] **1.5** Aprender expresiones regulares: qué significan ^ $ [ ] { } + * ? | ( ) y las clases [[:digit:]], [[:alpha:]], [[:alnum:]]. Practicar escribiendo patrones en papel y probarlos.
- [ ] **1.6** Programa mínimo con <regex.h>: compilar un patrón con regcomp (usando REG_EXTENDED | REG_NOSUB), probar textos con regexec y liberar con regfree. Entender qué regresa cada función y cómo mostrar el error con regerror.
- [ ] **1.7** comun.c: una función general "coincide(texto, patron)" y, encima de ella, las validaciones con regex:
    - teléfono: exactamente 10 dígitos
    - boleta / identificador: 3 a 20 letras o números
    - nombre y apellidos: solo letras (con acentos y ñ), espacios y guion
    - correo: usuario@dominio.ext
    - placa: letras, números y guion (5 a 10 caracteres)
    - año: 4 dígitos (y además revisar rango 1900–2100)
    - nombre de usuario: 4 a 31 letras, números, . _ -
    - contraseña: revisar mayúscula, minúscula, número y símbolo (pista: con varias regex sencillas)

    Ningún campo puede contener el carácter "|" (es el separador de los .txt).
- [ ] **1.8** Llamar a setlocale(LC_ALL, "") al inicio para que las regex acepten acentos y ñ, y comprobarlo.
- [ ] **1.9** Programa de prueba que llame a cada validación con datos buenos y malos (mis propias pruebas).

## FASE 2 – ARCHIVOS DE TEXTO (lo usará solo el servidor)

- [ ] **2.1** Definir el formato de cada archivo en datos/: propietarios.txt, vehiculos.txt, usuarios.txt, movimientos.txt (un registro por línea, campos separados por "|"). Escribirlo en el README.
- [ ] **2.2** archivos.c: guardar un Propietario como una línea al final del archivo (fopen "a", fprintf).
- [ ] **2.3** Leer todos los propietarios: leer línea por línea con fgets, quitar el salto de línea y separar los campos (strtok o sscanf). Cuidar los campos vacíos (por ejemplo teléfono opcional): entender por qué strtok los salta y cómo evitarlo.
- [ ] **2.4** Lo mismo para Vehiculo, Usuario y Movimiento.
- [ ] **2.5** Al leer, validar cada línea (número de campos correcto) y saltar o reportar las líneas dañadas.
- [ ] **2.6** Modificar un registro: leer todo, cambiar uno y reescribir en un archivo temporal, luego rename.
- [ ] **2.7** Eliminar un usuario del archivo (misma técnica).
- [ ] **2.8** Probar todo con un programa de prueba y revisar los .txt con un editor antes de seguir.

## FASE 3 – MEMORIA COMPARTIDA Y SEMÁFOROS (lo más importante de la materia)

- [ ] **3.1** Programa mínimo: un proceso escribe un texto en memoria compartida (shm_open, ftruncate, mmap) y otro lo lee.
- [ ] **3.2** Añadir dos semáforos con nombre (sem_open): "petición" y "respuesta", para que uno espere al otro.
- [ ] **3.3** Diseñar la estructura de la memoria compartida (operación, datos de entrada, datos de respuesta, correcto, mensaje).
- [ ] **3.4** memoria.c del SERVIDOR: crear la memoria y semáforos, y borrarlos al salir (munmap, shm_unlink, sem_unlink).
- [ ] **3.5** memoria.c del CLIENTE: abrir la memoria; si no existe, mostrar "Primero ejecuta ./servidor".
- [ ] **3.6** Primera petición real: el cliente pide "lista de propietarios" y el servidor responde.
- [ ] **3.7** Espera con límite de tiempo (sem_timedwait) para detectar que el servidor se cayó → mensaje de conexión perdida.

## FASE 4 – SERVIDOR CON HILOS Y VARIOS CLIENTES

- [ ] **4.1** Repasar pthread_create, pthread_join / pthread_detach.
- [ ] **4.2** Memoria de "control" donde cada cliente se registra al conectarse (tabla de clientes con su PID).
- [ ] **4.3** Cada cliente crea SU propia memoria compartida y semáforos; el servidor crea UN HILO por cliente que lo atiende.
- [ ] **4.4** Proteger los archivos entre hilos (mutex o rwlock) y explicar por qué es necesario.
- [ ] **4.5** Detectar cliente desconectado (su PID ya no existe) y liberar sus recursos.
- [ ] **4.6** Cierre ordenado del servidor con Ctrl+C (signal, esperar hilos, borrar memoria).
- [ ] **4.7** Bitácora: imprimir en terminal cada petición y guardarla con fecha y hora en control_vehicular.log.

## FASE 5 – USUARIOS Y SEGURIDAD

- [ ] **5.1** Crear el usuario administrador inicial si no hay usuarios.
- [ ] **5.2** Guardar contraseñas con hash (crypt con SHA-512 y sal), nunca en texto plano. Entender por qué es "hash" y no "cifrado".
- [ ] **5.3** Operación INICIAR_SESION y CERRAR_SESION en el servidor; la sesión se guarda por cliente (por hilo).
- [ ] **5.4** Aplicar la validación de contraseña segura de la tarea 1.7 (8+ caracteres, mayúscula, minúscula, número y símbolo) al crear y modificar cuentas. El hash se guarda en usuarios.txt (nunca la contraseña).
- [ ] **5.5** Revisar permisos por rol en el servidor en CADA petición.

## FASE 6 – INTERFAZ CON NCURSES (cliente)

- [ ] **6.1** Programa mínimo de ncurses: initscr, imprimir, getch, endwin, colores.
- [ ] **6.2** Programa mínimo RESPONSIVO: mostrar el tamaño actual (LINES x COLS) centrado en pantalla y redibujarlo cuando getch regrese KEY_RESIZE (al agrandar o achicar la ventana).
- [ ] **6.3** Funciones de diseño reutilizables que calculen posiciones con LINES y COLS: encabezado de ancho completo, texto centrado, barra de ayuda siempre en la penúltima línea, área de mensajes siempre arriba de la barra de ayuda.
- [ ] **6.4** Tamaño mínimo (por ejemplo 80x24): si la ventana es más pequeña, mostrar solo "Agranda la ventana de la terminal" y esperar a que la agranden.
- [ ] **6.5** Función de menú con flechas, ENTER y ESC, centrada, que se redibuje sola con KEY_RESIZE sin perder la opción elegida.
- [ ] **6.6** Función para leer texto (con borrar) y para leer contraseña mostrando asteriscos; el texto escrito se conserva si se cambia el tamaño de la ventana mientras se escribe.
- [ ] **6.7** Función de formulario de varios campos que se acomode al espacio disponible y mensaje de resultado (verde correcto / rojo error).
- [ ] **6.8** Tablas responsivas (propietarios, vehículos, historial): el ancho de las columnas depende de COLS, los textos largos se recortan con "...", y si hay más filas que espacio se puede desplazar con flechas / RePág / AvPág, mostrando "filas X–Y de Z".
- [ ] **6.9** Pantallas: bienvenida, inicio de sesión, panel según rol, todas usando las funciones anteriores.

## FASE 7 – FUNCIONES DEL SISTEMA (cliente + servidor)

- [ ] **7.1** Registrar propietario (validar con regex en cliente Y en servidor; evitar identificador repetido).
- [ ] **7.2** Consultar propietarios.
- [ ] **7.3** Registrar vehículo (buscar propietario; placa obligatoria solo para autos/motos; folio automático si no tiene placa; evitar placa repetida).
- [ ] **7.4** Consultar vehículos (el usuario solo ve los suyos).
- [ ] **7.5** Modificar propietario y vehículo (admin).
- [ ] **7.6** Gestión de cuentas (admin): crear, consultar, modificar, eliminar (no eliminar al último admin ni a sí mismo).
- [ ] **7.7** Mi perfil (usuario): ver datos, modificar datos personales, cambiar usuario o contraseña.
- [ ] **7.8** Control de acceso: registrar entrada y salida (no permitir doble entrada ni salida sin entrada).
- [ ] **7.9** Historial de movimientos y reporte por día / semana / mes.

## FASE 8 – PRUEBAS Y ENTREGA

- [ ] **8.1** Probar con 2 o 3 clientes al mismo tiempo.
- [ ] **8.2** Probar casos de error: datos inválidos, servidor apagado, cliente cerrado de golpe, archivos vacíos.
- [ ] **8.2b** Probar la interfaz en distintos tamaños: ventana pequeña, normal, pantalla completa y cambiando el tamaño en medio de un menú, un formulario y una tabla.
- [ ] **8.3** Compilar desde cero con make clean && make: cero advertencias.
- [ ] **8.4** Tomar capturas de compilación y ejecución para el reporte.
- [ ] **8.5** Comentar el código (qué hace cada función) y actualizar el README.
- [ ] **8.6** Preparar la explicación oral: recorrido de una petición (cliente → memoria → semáforo → hilo del servidor → archivo → respuesta) y respuestas a preguntas del profesor.
