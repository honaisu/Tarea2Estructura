#include "TDAs/extras.h" // Distinto del profesor! Es propia.
#include "TDAs/list.h"
#include "TDAs/map.h"
#include "TDAs/music.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leerOpcion(char* opcion) { sscanf(leerEntrada(), "%c", opcion) ; }

void mostrarDatosArchivo(FILE* archivo) {
    char** completo = leerLineaCSV(archivo, ',') ;
    
    while ((completo = leerLineaCSV(archivo, ',')) != NULL) {
        for (int i = 0 ; completo[i] ; i++) {
            printf("%s ", completo[i]) ;
        }
        printf("\n") ;
        
    }
}

void casosDeOpciones(char* o, Map* Ge, Map* Ar, Map* Te) {
    leerOpcion(o) ;
    switch (*o) {
        //---//
        case '1': { // Cargar Canciones en CSV
            music_cargar(Ge, Ar, Te) ;
            break ;
        }
        case '2': { // Buscar por Género
            music_buscarPorGenero(Ge) ;
            break ;
        }
        case '3': { // Buscar por Artista
            music_buscarPorArtista(Ar) ;
            break ;
        }
        case '4': { // Buscar por Tempo
            music_buscarPorTempo(Te) ;
            break ;
        }
        case '0': {
            puts("Saliendo del programa...") ;
            break ;
        }
        default: {
            puts("Opción no válida. Vuelva a introducir una opción.") ;
        }
    }
    if (*o != '0') esperarEnter() ;
}

void limpiarMapas(Map* A, Map* B, Map* C) {
    map_clean(A) ;
    map_clean(B) ;
    map_clean(C) ;
    free(A) ;
    free(B) ;
    free(C) ;
}

void elegirOpciones() {
    char opcion ;
    Map* listaGeneros = map_create(is_equal_str) ;
    Map* listaArtistas = map_create(is_equal_str) ;
    Map* listaTempo = map_create(is_equal_str) ;
    //---//
    do {
        mostrarMenuPrincipal() ;
        printf("Ingrese su opción: ") ;
        casosDeOpciones(&opcion, listaGeneros, listaArtistas, listaTempo) ;
    } while (opcion != '0') ;
    //---//
    limpiarMapas(listaGeneros, listaArtistas, listaTempo) ;
    return ;
}

int main() {
    elegirOpciones() ;
    return 0 ;
}
