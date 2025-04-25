#include "extras.h"
#include "music.h"
#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char verificarCancion = '0' ;

Song* guardarDatos(char** completo) {
  Song* nuevaCancion = (Song*) malloc(sizeof(Song)) ; 
  if (nuevaCancion == NULL) return NULL ;
  // Identificador
  strcpy(nuevaCancion->id, completo[0]) ;
  // Artistas
  nuevaCancion->artists = split_string(completo[2], ";") ; 
  // Nombre del Album
  strcpy(nuevaCancion->album_name, completo[3]) ;
  // Nombre de la Canción (Track)
  strcpy(nuevaCancion->track_name, completo[4]) ;
  // Velocidad (Tempo) de la Canción
  nuevaCancion->tempo = strtol(completo[18], NULL, 10) ;
  // Género musical de la canción   
  strcpy(nuevaCancion->track_genre, completo[20]) ;
  return nuevaCancion ;
}

List* devolverLista(Map* Mapa, const Song* Cancion, const char* delim) {
  List* nuevaLista ;
  return nuevaLista ;
}

void music_cargar(Map* cancionesGenero, Map* cancionesArtistas, Map* cancionesTempo) {
  if (verificarCancion == '1') { puts("YA SE CARGARON LAS CANCIONES!") ; return ; }

  FILE* archivoCSV = fopen("Data/song_dataset_.csv", "r") ;
  if (archivoCSV == NULL) { perror("ERROR LEYENDO EL ARCHIVO") ; return ; }
  int i = 0 ;
  //---//
  char** completo = leerLineaCSV(archivoCSV, ',') ;
  while (i < 10000 && (completo = leerLineaCSV(archivoCSV, ',')) != NULL) {
    //---//
    Song* Cancion = guardarDatos(completo) ; ;
    if (Cancion == NULL) { perror("NO SE PUEDEN AGREGAR MAS CANCIONES:") ; return ; }
    //---//
    MapPair* pair ;
    // LISTA GENEROS
    pair = map_search(cancionesGenero, Cancion->track_genre) ;
    List* listaGeneros ;
    if (pair == NULL) {
      listaGeneros = list_create() ;
      map_insert(cancionesGenero, Cancion->track_genre, listaGeneros) ;
    } else {
      listaGeneros = pair->value ;
    }

    list_pushBack(listaGeneros, Cancion) ;
    
    // LISTA ARTISTAS
    List* listaArtistas ;
    char* artista = list_first(Cancion->artists) ;
    while (artista != NULL) {
      pair = map_search(cancionesArtistas, artista) ;
      if (pair == NULL) {
        listaArtistas = list_create() ;
        map_insert(cancionesArtistas, artista, listaArtistas) ;
      } else {
        listaArtistas = pair->value ;
      }
      artista = list_next(Cancion->artists) ;
    }
    
    list_pushBack(listaArtistas, Cancion) ;

    // LISTA TEMPO
    List* listaTempo ;
    char* key ;
    if (Cancion->tempo < 80) {
      key = "Lento" ;
    } else if (Cancion->tempo >= 80 && Cancion->tempo < 120) {
      key = "Moderado" ;
    } else key = "Rapido" ;

    pair = map_search(cancionesTempo, key) ;
    if (pair == NULL) {
      listaTempo = list_create() ;
      map_insert(cancionesGenero, key, listaTempo) ;
    } else {
      listaTempo = pair->value ;
    }

    list_pushBack(listaTempo, Cancion) ;
    i++ ;
  }
  //---//
  fclose(archivoCSV) ;
  verificarCancion = '1' ;
  return ;
}

void imprimirDatosCanciones(Song* cancion) {
  puts("") ;
  puts("======================") ;
  printf("ID: %s\n", cancion->id) ;
  char* artistas = list_first(cancion->artists) ;
  printf("Artista(s):\n") ;
  while (artistas != NULL) {
    printf("%s\n", artistas) ;
    artistas = list_next(cancion->artists) ;
  }
  printf("Nombre cancion: %s\n", cancion->track_name) ;
  printf("Album: %s\n", cancion->album_name) ;
  printf("Genero: %s\n", cancion->track_genre) ;
  printf("Tempo: %ld\n", cancion->tempo) ;
  puts("======================") ;
}

void music_buscarPorFiltro(Map* Mapa) {
  limpiarPantalla() ;
  MapPair* pair ;
  char* filtro = leerEntrada() ;
  pair = map_search(Mapa, filtro) ;
  if (pair == NULL) { perror("NO SE ENCONTRÓ ESE:") ; return ; }
  Song* cancion = list_first(pair->value) ;
  while (cancion != NULL) {
    imprimirDatosCanciones(cancion) ;
    cancion = list_next(pair->value) ;
  }
  free(filtro) ;
}

void music_buscarPorGenero(Map* G) { music_buscarPorFiltro(G) ; }

void music_buscarPorArtista(Map* A) { music_buscarPorFiltro(A) ; }

void music_buscarPorTempo(Map* T) { music_buscarPorFiltro(T) ; }