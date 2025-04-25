#ifndef MUSIC_H
#define MUSIC_H
#include "list.h"
#include "map.h"

// QUIERO HACER QUE SI MI MAPA EXISTA
// SEA COMO UN DICCIONARIO QUE BUSQUE REFERENCIAS DE CANCIONES EXISTENTES

typedef struct {
    char id[100] ;
    List* artists ;
    char album_name[200] ;
    char track_name[200] ;
    char track_genre[100] ;
    long tempo ;
} Song ;

// Carga un archivo CSV. Se ingresa una ruta del archivo CSV, y la aplicación carga los datos de ahí.
void music_cargar(Map*, Map*, Map*) ;
// Se pide buscar un género en específico, y se muestran todos los resultados con ese género.
void music_buscarPorGenero(Map*) ;
// Se pide buscar un artista. Muestra todas las canciones de un artista.
void music_buscarPorArtista(Map*) ;
// Muestra todas las canciones de un Tempo ("velocidad" de la canción) ingresado específico.
void music_buscarPorTempo(Map*) ;

#endif  