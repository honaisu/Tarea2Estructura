#include "TDAs/extras.h" // Distinto del profesor! Es propia.
#include "TDAs/music.h"
#include "TDAs/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void casosDeOpciones(char* o, Map* Mapa) {
    leerOpcion(o) ;
    switch (*o) {
        //---//
        case '1': { // Cargar Canciones en CSV
            music_cargar(Mapa) ;
            break ;
        }
        case '2': { // Buscar por Género
            music_buscarPorGenero(Mapa) ;
            break ;
        }
        case '3': { // Buscar por Artista
            music_buscarPorArtista(Mapa) ;
            break ;
        }
        case '4': { // Buscar por Tempo
            music_buscarPorTempo(Mapa) ;
            break ;
        }
        case '0': {
            puts("Saliendo del programa...") ;
            break ;
        }
        case '\0': {
            puts("Por favor, introduzca una opción válida.") ;
            break ;
        }
        default: {
            puts("Opción no válida. Vuelva a introducir una opción.") ;
        }
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
