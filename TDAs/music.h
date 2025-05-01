#ifndef MUSIC_H
#define MUSIC_H
#include "list.h"
#include "map.h"

// Estructura Song
// Guarda todos los datos correspondientes a una canción.
typedef struct {
    char id[100]    ; // ID.
    List* artists   ; // Lista de Artistas.
    char album_name[200]    ; // Nombre de Álbum.
    char track_name[200]    ; // Nombre de la canción.
    char track_genre[100]   ; // Género de la canción.
    char categoriaTempo[10] ; // Categoría del tempo (Lento, Moderado o Rápido).
    float tempo ; // Tempo de la canción.
} Song ;

// Carga un archivo CSV. Se ingresa una ruta del archivo CSV, y la aplicación carga los datos de ahí para asignarlos a distintos mapas.
void music_cargar(Map*) ;
// Se pide buscar un género en específico, y se muestran todos los resultados con ese género.
void music_buscarPorGenero(Map*) ;
// Se pide buscar un artista. Muestra todas las canciones de un artista.
void music_buscarPorArtista(Map*) ;
// Muestra todas las canciones de un Tempo ("velocidad" de la canción) ingresado.
void music_buscarPorTempo(Map*) ;

#endif  