#ifndef EXTRAS_H
#define EXTRAS_H
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

// LISTA PROPIA CON FUNCIONES (Que agarré o creé) //

char** leerLineaCSV(FILE*, char) ;
void limpiarPantalla() ;
void mostrarMenuPrincipal() ;
void esperarEnter() ;
void imprimirSeparador(const char*, const char*) ;
char* leerEntrada() ;

int is_equal_str(void*, void*) ;
int is_equal_int(void*, void*) ;
List *split_string(const char*, const char*) ;

#endif