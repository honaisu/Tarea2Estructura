#include "extras.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 300

char **leerLineaCSV(FILE *archivo, char separador) {
    static char linea[MAX_LINE_LENGTH] ;
    static char *campos[MAX_FIELDS] ;
    char *ptr, *start ;
    int idx = 0 ;

    if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL) {
        return NULL; // No hay más líneas para leer
    }

    // Eliminar salto de linea
    linea[strcspn(linea, "\n")] = '\0' ;

    ptr = start = linea ;
    while (*ptr) {
        if (idx >= MAX_FIELDS - 1) break ;

        if (*ptr == '\"') { // Inicio de un campo entrecomillado
            start = ++ptr ;    // Saltar la comilla inicial
            while (*ptr && !(*ptr == '\"' && *(ptr + 1) == separador)) ptr++ ;
        } else { // Campo sin comillas
            start = ptr ;
            while (*ptr && *ptr != separador) ptr++ ;
        }

        if (*ptr) { 
            *ptr = '\0' ; // Reemplazar comilla final o separador por terminación
            ptr++ ;
            if (*ptr == separador) ptr++ ;
        }

        // Quitar comilla final si existe
        if (*(ptr - 2) == '\"') *(ptr - 2) = '\0' ;
        campos[idx++] = start ;
    }

    campos[idx] = NULL ; // Marcar el final del array
    return campos ;
}

int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0 ;
}

List *split_string(const char *str, const char *delim) {
  List *result = list_create() ;
  char *token = strtok((char *)str, delim) ;

  while (token != NULL) {
    // Eliminar espacios en blanco al inicio del token
    while (*token == ' ') {
      token++ ;
    }
    
    // Eliminar espacios en blanco al final del token
    char *end = token + strlen(token) - 1 ;
    while (*end == ' ' && end > token) {
      *end = '\0' ;
      end-- ;
    }

    // Copiar el token en un nuevo string
    char *new_token = strdup(token) ;

    // Agregar el nuevo string a la lista
    list_pushBack(result, new_token) ;

    // Obtener el siguiente token
    token = strtok(NULL, delim) ;
  }

  return result ;
}

//---//

void limpiarPantalla() {
  #ifdef _WIN32
    system("cls") ;
  #else
    system("clear") ;
  #endif
}

void imprimirSeparador(const char* mensaje) {
  int largo = strlen(mensaje) + 12 ;
  int i ;
  putchar('#') ;
  for (i = 0 ; i < largo ; i++) {
      putchar('=') ;
  }
  puts("#") ;
  printf("       %s\n", mensaje) ;
  putchar('#') ;
  for (i = 0 ; i < largo ; i++) {
      putchar('=') ;
  }
  putchar('#') ;
  putchar('\n') ;
}

void mostrarMenuPrincipal() {
    limpiarPantalla() ;
    imprimirSeparador("SPOTIFIND") ;
    puts("(1). Cargar Canciones") ;
    puts("(2). Buscar por Género") ;
    puts("(3). Buscar por Artista") ;
    puts("(4). Buscar por Tempo") ;
    puts("(0). Salir") ;
    putchar('\n') ;
}

void esperarEnter() {
    puts("Presione ENTER para continuar...") ;
    while (getchar() != '\n') ;
}

void leerEntrada(char* string) {
    char buffer[200] ;
    fgets(buffer, sizeof(buffer), stdin) ;
    buffer[strcspn(buffer, "\n")] = '\0' ;
    strcpy(string, buffer) ;
}

void leerOpcion(char* opcion) { 
  *opcion = '\0' ;
  printf("Ingrese su opción: ") ;
  char buffer[200] ;
  leerEntrada(buffer) ;
  sscanf(buffer, "%c", opcion) ; 
}