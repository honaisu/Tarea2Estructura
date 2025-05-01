#ifndef EXTRAS_H
#define EXTRAS_H
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

//--- LISTA PROPIA CON FUNCIONES (Que agarré o creé) ---//

//--- Funciones (de ejemplos y la base): ---//
// Separa el contenido de un string con un delimitador, y lo devuelve en formato List.
List *split_string(const char*, const char*) ;
// Agarra un archivo, y por cada línea que pasa va leyendo su contenido. Lo devuelve en formato de doble puntero a char (lista de strings).
char** leerLineaCSV(FILE*, char) ;
// Compara strings, y da un resultado si es que comprueba si es igual o no. Función útil para la creación de mapas.
int is_equal_str(void*, void*) ;

//--- Funciones propias: ---//
// Optimizado para funcionar en otros OS. Limpia el contenido mostrado en la terminal.
void limpiarPantalla() ;
// Menú simple que muestra distintas opciones para elegir.
void mostrarMenuPrincipal() ;
// Espera que el input del usuario sea un ENTER (salto de línea) para continuar.
void esperarEnter() ;
// (Magnus Opus) Imprime un mensaje con un separador automático.
void imprimirSeparador(const char*) ;
// Lee lo que el usuario ingrese y modifica un string.
void leerEntrada(char*) ;
// Lee lo que el usuario ingrese, pero asigna sólo el primer carácter a una opción.
void leerOpcion(char*) ;

#endif