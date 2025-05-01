#include "TDAs/extras.h" // Distinto del profesor! Es propia.
#include "TDAs/music.h"
#include "TDAs/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void casosDeOpciones(char* o, Map* mapa) {
    leerOpcion(o) ;
    switch (*o) {
        // Cargar Canciones en CSV
        case '1': { music_cargar(mapa) ; break ; }
        // Buscar por Género
        case '2': { music_buscarPorGenero(mapa) ; break ; }
        // Buscar por Artista
        case '3': { music_buscarPorArtista(mapa) ; break ; }
        // Buscar por Tempo
        case '4': { music_buscarPorTempo(mapa) ; break ; }
        // Cuando se sale del programa
        case '0': { puts("Saliendo del programa...") ; break ; }
        // Cuando no hay dato ingresado
        case '\0': { puts("Por favor, introduzca una opción válida.") ; break ; }
        // Respuesta predeterminada
        default: { puts("Opción no válida. Vuelva a introducir una opción.") ; }
    }
    if (*o != '0') esperarEnter() ;
}

// Limpia el Mapa con valores de Mapa (Mapa de Mapas)
void limpiarMapas(Map* mapa) { 
    // Encuentra el primer valor asignado en el mapa (Mapa)
    MapPair* pair = map_first(mapa) ;
    while (pair != NULL) {
        // Limpia los datos del mapa
        map_clean(pair->value) ;
        // Libera la memoria del mapa
        free(pair->value) ;
        // Le asigna NULL para no acceder a una dirección distinta
        pair->value = NULL ;
        // Libera la memoria de la llave (clave)
        free(pair->key) ;
        // Le asigna NULL para no acceder a una dirección distinta
        pair->key = NULL ;
        // Se mueve al siguiente valor asignado
        pair = map_next(mapa) ;
    }
    // Limpia los datos del mapa
    map_clean(mapa) ;
    // Libera la memoria asignada del mapa
    free(mapa) ;
}

// Guarda un mapa con una llave dentro de otro mapa
void guardarMapa(Map* mapa, char* key) {
    Map* lista = map_create(is_equal_str) ;
    map_insert(mapa, key, lista) ;
}

void elegirOpciones() {
    char opcion ;
    Map* MapaCanciones = map_create(is_equal_str) ;
    guardarMapa(MapaCanciones, "Genero") ;
    guardarMapa(MapaCanciones, "Artistas") ;
    guardarMapa(MapaCanciones, "Tempo") ;
    //---//
    do {
        mostrarMenuPrincipal() ;
        casosDeOpciones(&opcion, MapaCanciones) ;
    } while (opcion != '0') ;
    //---//
    limpiarMapas(MapaCanciones) ;
    return ;
}

int main() {
    elegirOpciones() ;
    return 0 ;
}
