#include "extras.h"
#include "music.h"
#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertir(const float tempo, char* key) {
  char* valor ;
  if (tempo < 80) {
    valor = "Lento" ;
  } else if (tempo >= 80 && tempo <= 120) {
    valor = "Moderado" ;
  } else valor = "Rapido" ;
  strcpy(key, valor) ;
  //---//
}

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
  nuevaCancion->tempo = strtof(completo[18], NULL) ;
  convertir(nuevaCancion->tempo, nuevaCancion->categoriaTempo) ;
  // Género musical de la canción   
  strcpy(nuevaCancion->track_genre, completo[20]) ;
  return nuevaCancion ;
}

void agregarAlMapa(Map* mapa, char* key, Song* cancion) {
  MapPair* pair = map_search(mapa, key) ;
  List* lista ;
  //---//
  if (pair == NULL) {
    lista = list_create() ;
    map_insert(mapa, key, lista) ;
  } else lista = pair->value ;

  Song* existente = list_first(lista);
    while (existente != NULL) {
        if (strcmp(existente->id, cancion->id) == 0) {
            return; // La canción ya está en la lista, no agregarla de nuevo
        }
        existente = list_next(lista);
    }

  list_pushBack(lista, cancion) ;
}

char verificar_cargado = '0' ;

void cargarCanciones(const char** lineaCSV, Map* Mapa) ;

void music_cargar(Map* cancionesGenero, Map* cancionesArtistas, Map* cancionesTempo) {
  if (verificar_cargado == '1') { puts("YA SE CARGARON LAS CANCIONES!") ; return ; }
  limpiarPantalla() ;
  //---//
  imprimirSeparador("Se cargarán las primeras 10.000 canciones. ¿Desea seguir? [SI/NO]") ;
  char* opcion ;
  leerOpcion(opcion) ;
  if (*opcion == 'N') return ;
  limpiarPantalla() ;
  imprimirSeparador("Cargando canciones...") ;
  //---//
  FILE* archivoCSV = fopen("Data/song_dataset_.csv", "r") ;
  int i = 0 ;
  //---//
  char** completo = leerLineaCSV(archivoCSV, ',') ;
  while (i < 10000 && (completo = leerLineaCSV(archivoCSV, ',')) != NULL) {
    //---//
    Song* Cancion = guardarDatos(completo) ;
    if (Cancion == NULL) { perror("NO SE PUEDEN AGREGAR MAS CANCIONES:") ; return ; }
    //---//

    //--- LISTA GENEROS ---//
    agregarAlMapa(cancionesGenero, Cancion->track_genre, Cancion) ;
    
    //--- LISTA ARTISTAS ---//
    char* artista = list_first(Cancion->artists) ;
    while (artista != NULL) {
      agregarAlMapa(cancionesArtistas, artista, Cancion) ;
      artista = list_next(Cancion->artists) ;
    }

    //--- LISTA TEMPO ---//
    agregarAlMapa(cancionesTempo, Cancion->categoriaTempo, Cancion) ;
    i++ ;
  }
  //---//
  if (i == 10000) {
    verificar_cargado = '1' ;
    puts("SE CARGARON LAS PRIMERAS 10.000 CANCIONES.") ;
    esperarEnter() ;
    limpiarPantalla() ;
    imprimirSeparador("¿Desea leer todas las canciones disponibles? [S/N]") ;
    puts("Cargará todas las canciones disponibles y podrá trabajar con ellas.") ;
    puts("Si no, estarán cargadas las primeras 10.000 canciones.") ;
    leerOpcion(opcion) ;
    if (*opcion == 'N') return ;

    puts("SE HAN CARGADO TODAS LAS CANCIONES DISPONIBLES.");
  }
  //---//
  fclose(archivoCSV) ;
  return ;
}

void imprimirDatosCanciones(Song* cancion) {
  printf("ID: %s %40s", cancion->id, "Artistas(s): [") ;
  //--- IMPRIMIR ARTISTAS ---//
  char* artistas = list_first(cancion->artists) ;
  printf("%s", artistas) ;
  artistas = list_next(cancion->artists) ;
  while (artistas != NULL) {
    printf(", %s", artistas) ;
    artistas = list_next(cancion->artists) ;
  }
  printf("]\n") ;
  //-------------------------//
  printf("Nombre: \"%s\"\n", cancion->track_name) ;
  printf("Album : \"%s\"\n", cancion->album_name) ;
  printf("Genero: \"%s\"\n", cancion->track_genre) ;
  printf("Tempo : %.2f\n", cancion->tempo) ;
  puts("============================") ;
}

char es_tempo ;

MapPair* devolverPairFiltro(Map* Mapa) {
  //---//
  MapPair* pair ;
  char filtro[200] ;
  leerEntrada(filtro) ;
  //---//
  if (es_tempo == '1') {
    float tempo = strtof(filtro, NULL) ;
    if (!tempo) return NULL ;
    convertir(tempo, filtro) ;
  }
  //---//
  return map_search(Mapa, filtro) ;
}

void music_buscarPorFiltro(Map* Mapa) {
  if (verificar_cargado == '0') { puts("NO HAY CANCIONES CARGADAS.") ; return ; }
  limpiarPantalla() ;
  MapPair* pair = devolverPairFiltro(Mapa) ;
  if (pair == NULL) { puts("NO SE ENCONTRÓ EL DATO A BUSCAR") ; return ; }
  //---//
  Song* cancion = list_first(pair->value) ;
  while (cancion != NULL) {
    imprimirDatosCanciones(cancion) ;
    cancion = list_next(pair->value) ;
  }
  //---//
  es_tempo = '0' ;
  free(pair) ;
}

void music_buscarPorGenero(Map* G) { music_buscarPorFiltro(G) ; }

void music_buscarPorArtista(Map* A) { music_buscarPorFiltro(A) ; }

void music_buscarPorTempo(Map* T) { es_tempo = '1' ; music_buscarPorFiltro(T) ; }