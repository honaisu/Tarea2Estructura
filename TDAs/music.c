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

void cargarCanciones(char** lineaCSV, Map* Mapa) {
  //---//
  Song* Cancion = guardarDatos(lineaCSV) ;
  if (Cancion == NULL) { perror("NO SE PUEDEN AGREGAR MAS CANCIONES:") ; return ; }
  //---//
  MapPair* pair = map_search(Mapa, "Genero") ;
  //--- LISTA GENEROS ---//
  agregarAlMapa(pair->value, Cancion->track_genre, Cancion) ;
  
  //--- LISTA ARTISTAS ---//
  pair = map_search(Mapa, "Artistas") ;
  char* artista = list_first(Cancion->artists) ;
  while (artista != NULL) {
    agregarAlMapa(pair->value, artista, Cancion) ;
    artista = list_next(Cancion->artists) ;
  }

  //--- LISTA TEMPO ---//
  pair = map_search(Mapa, "Tempo") ;
  agregarAlMapa(pair->value, Cancion->categoriaTempo, Cancion) ;
}

void imprimirGato() {
  puts(" \\    /\\               |\'/-..--.") ;
  puts("  )  ( ')             / _ _   ,  ;")  ;
  puts(" (  /  )             `~=`Y'~_<._./")  ;
  puts("  \\(__)|             <`-....__.'")  ;
}

void music_cargar(Map* MapaCanciones) {
  if (verificar_cargado == '1') { puts("YA SE CARGARON LAS CANCIONES!") ; return ; }
  limpiarPantalla() ;
  char buffer[100] ;
  imprimirSeparador("Por favor, ingrese la ruta donde se ubica el archivo de canciones:") ;
  puts("Si trabaja con el repositorio, puede usar la ruta \"Data/song_dataset_.csv\"\n") ;
  printf("Ingrese la ruta del archivo con canciones, sin comillas: ") ;
  leerEntrada(buffer) ;
  if (*buffer == '\0') {
    puts("No se pudo leer su dirección") ;
    return ;
  }
  //---//
  limpiarPantalla() ;
  imprimirSeparador("Se cargarán las primeras 10.000 canciones. ¿Desea seguir? [SI/NO]") ;
  char opcion[10] ;
  leerOpcion(opcion) ;
  if (*opcion == '\0') puts("Introduzca una opción válida.") ;
  else if ((*opcion != 'S' && *opcion == 's') || *opcion == '0') return ;
  limpiarPantalla() ;
  imprimirSeparador("Cargando canciones...") ;
  imprimirGato() ;
  //---//
  FILE* archivoCSV = fopen(buffer, "r") ;
  int i = 0 ;
  //---//
  char** completo = leerLineaCSV(archivoCSV, ',') ;
  while (i < 10000 && (completo = leerLineaCSV(archivoCSV, ',')) != NULL) {
    cargarCanciones(completo, MapaCanciones) ;
    i++ ;
  }
  //---//
  if (i == 10000) {
    verificar_cargado = '1' ;
    //---//
    puts("SE CARGARON LAS PRIMERAS 10.000 CANCIONES.") ;
    esperarEnter() ;
    limpiarPantalla() ;
    imprimirSeparador("¿Desea leer todas las canciones disponibles? [S/N]") ;
    puts("Si acepta, cargará todas las canciones disponibles (puede tardar un rato).") ;
    puts("Si no, estarán cargadas las primeras 10.000 canciones.") ;
    //---//
    leerOpcion(opcion) ;
    if (*opcion != 'S' && *opcion != 's') return ;

    while ((completo = leerLineaCSV(archivoCSV, ',')) != NULL) cargarCanciones(completo, MapaCanciones) ;
    //---//
    limpiarPantalla() ;
    imprimirSeparador("SE HAN CARGADO TODAS LAS CANCIONES DISPONIBLES.") ;
  }
  //---//
  fclose(archivoCSV) ;
  return ;
}

void imprimirDatosCanciones(Song* cancion) {
  puts("") ;
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
  printf("Tempo : %.2f (%s) \n", cancion->tempo, cancion->categoriaTempo) ;
}

char es_tempo ;

MapPair* devolverPairFiltro(Map* Mapa) {
  //---//
  MapPair* pair ;
  char filtro[200] ;
  printf("Ingrese su opción: ") ;
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

void music_buscarPorFiltro(Map* Mapa, const char* str) {
  if (verificar_cargado == '0') { puts("NO HAY CANCIONES CARGADAS.") ; return ; }
  limpiarPantalla() ;
  imprimirSeparador(str) ;
  MapPair* pair = devolverPairFiltro(Mapa) ;
  if (pair == NULL) { puts("NO SE ENCONTRÓ EL DATO A BUSCAR") ; return ; }
  //---//
  int contadorCanciones = 0 ;
  char opcion[10] ;
  Song* cancion = list_first(pair->value) ;
  while (cancion != NULL) {
    imprimirDatosCanciones(cancion) ;

    if (contadorCanciones == 10 && cancion != NULL) {
      putchar('\n') ;
      imprimirSeparador("¿Desea ver más canciones? [S/N]") ;
      leerOpcion(opcion) ;
      if (*opcion == 'S' || *opcion == 's') contadorCanciones = 0 ;
      else break ;
    }

    contadorCanciones++ ;
    cancion = list_next(pair->value) ;
  }
  //---//
  if (cancion == NULL) {
    putchar('\n') ;
    imprimirSeparador("¡Llegó al final de la lista!") ;
  }

  es_tempo = '0' ;
}

void music_buscarPorGenero(Map* Mapa) {
  MapPair* pair = map_search(Mapa, "Genero") ; 
  music_buscarPorFiltro(pair->value, "Ingrese el género a buscar:") ;
}

void music_buscarPorArtista(Map* Mapa) { 
  MapPair* pair = map_search(Mapa, "Artistas") ; 
  music_buscarPorFiltro(pair->value, "Ingrese el artista a buscar:") ; 
}

void music_buscarPorTempo(Map* Mapa) { 
  es_tempo = '1' ; 
  MapPair* pair = map_search(Mapa, "Tempo") ; 
  music_buscarPorFiltro(pair->value, "Ingrese la velocidad (tempo) a buscar") ; 
}