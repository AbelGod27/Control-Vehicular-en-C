/*
 * servidor.c
 * Sistema de Control Vehicular - ESCOM (IPN), Sistemas Operativos
 * Autor: Abel Pineda Godinez
 *
 * Programa servidor: crea la memoria de control, atiende a cada
 * cliente con un hilo (pthreads), protege los archivos entre hilos,
 * revisa permisos por rol, escribe la bitacora y se cierra en orden
 * con Ctrl+C.
 * (Fases 3, 4 y 5)
 */
