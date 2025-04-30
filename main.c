#include "TDAs/extras.h" // Distinto del profesor! Es propia.
#include "TDAs/music.h"
#include "TDAs/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void casosDeOpciones(char* o, Map* Mapa) {
    leerOpcion(o) ;
    switch (*o) {
        // Cargar Canciones en CSV
        case '1': { music_cargar(Mapa) ; break ; }
        // Buscar por Género
        case '2': { music_buscarPorGenero(Mapa) ; break ; }
        // Buscar por Artista
        case '3': { music_buscarPorArtista(Mapa) ; break ; }
        // Buscar por Tempo
        case '4': { music_buscarPorTempo(Mapa) ; break ; }
        // Cuando se sale del programa
        case '0': { puts("Saliendo del programa...") ; break ; }
        // Cuando no hay dato ingresado
        case '\0': { puts("Por favor, introduzca una opción válida.") ; break ; }
        // Respuesta predeterminada
        default: { puts("Opción no válida. Vuelva a introducir una opción.") ; }
    }
    if (*o != '0') esperarEnter() ;
}

void limpiarMapas() { }

void guardarMapa(Map* Mapa, char* key) {
    Map* lista = map_create(is_equal_str) ;
    map_insert(Mapa, key, lista) ;
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
    limpiarMapas() ;
    return ;
}

int main() {
    elegirOpciones() ;
    return 0 ;
}
