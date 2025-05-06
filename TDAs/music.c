#include "extras.h"
#include "music.h"
#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variable global que verifica si es que se han cargado las canciones
char verificar_cargado = '0' ;

// Variable global encargada de verificar si es que, al buscar por filtro, se busca por tempo o no.
char es_tempo = '0' ;

//--- Funciones de impresión ---//

// Solo imprime gatitos.
void imprimirGato() {
  puts(" \\    /\\               |\'/-..--.") ;
  puts("  )  ( ')             / _ _   ,  ;")  ;
  puts(" (  /  )             `~=`Y'~_<._./")  ;
  puts("  \\(__)|             <`-....__.'")  ;
}

// Imprime los datos de las canciones
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
  printf("Tempo : %.2f BPM (%s) \n", cancion->tempo, cancion->categoriaTempo) ;
}

//--- Funciones varias (No las principales) ---//

// Convierte una llave a ciertos rangos dependiendo del tempo asignado.
void convertir(const float tempo, char* key) {
  // String que guardará el "valor" del tempo
  char* valor ;
  if (tempo < 80) {
    // Si el tempo está debajo de 80, el valor es Lento.
    valor = "Lento" ;
  } else if (tempo >= 80 && tempo <= 120) {
    // Si el tempo está entre 80 y 120, el valor es Moderado.
    valor = "Moderado" ;
  } else valor = "Rapido" ; // Si es mayor a 120, es Rapido.
  // Copia este valor a la llave que queremos modificar.
  strcpy(key, valor) ;
  //---//
}

// Guarda los datos de una cancion con la estructura Song.
Song* guardarDatos(char** completo) {
  // Asignar memoria a la cancion
  Song* nuevaCancion = (Song*) malloc(sizeof(Song)) ; 
  if (nuevaCancion == NULL) return NULL ;
  // ID.
  strcpy(nuevaCancion->id, completo[0]) ;
  // Artistas.
  nuevaCancion->artists = split_string(completo[2], ";") ; 
  // Nombre del Album.
  strcpy(nuevaCancion->album_name, completo[3]) ;
  // Nombre de la Canción (Track).
  strcpy(nuevaCancion->track_name, completo[4]) ;
  // Velocidad (Tempo) de la Canción.
  nuevaCancion->tempo = strtof(completo[18], NULL) ;
  convertir(nuevaCancion->tempo, nuevaCancion->categoriaTempo) ;
  // Género musical de la canción.
  strcpy(nuevaCancion->track_genre, completo[20]) ;
  return nuevaCancion ;
}

// Agrega una canción con una clave a un mapa.
void agregarAlMapa(Map* mapa, char* key, Song* cancion) {
  MapPair* pair = map_search(mapa, key) ; // Se busca un par con una clave específica.
  List* lista ; // Lista a agregar al mapa.
  //---//
  if (pair == NULL) { // Si es que el par es nulo (no existe un dato con esa clave). Crea la lista y la inserta al mapa.
    lista = list_create() ;
    map_insert(mapa, key, lista) ;
  } else lista = pair->value ; // Si existe una clave, hace que la lista sea igual al puntero del valor del par.

  Song* existente = list_first(lista) ; // Se busca el primer elemento de la lista.
  
  while (existente != NULL) {
      if (strcmp(existente->id, cancion->id) == 0) { // Si la ID es la mismá (ya está en la lista)
          return ; // No agregarla de nuevo.
      }
      existente = list_next(lista) ;
  }

  list_pushBack(lista, cancion) ;
}

void cargarCanciones(char** lineaCSV, Map* Mapa) {
  //---//
  Song* Cancion = guardarDatos(lineaCSV) ;
  if (Cancion == NULL) { perror("NO SE PUEDEN AGREGAR MAS CANCIONES") ; return ; }
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

//--- Funciones Principales ---//

void music_cargar(Map* MapaCanciones) {
  if (verificar_cargado == '1') { puts("YA SE CARGARON LAS CANCIONES!") ; return ; }
  //--- IMPRESIÓN ---//
  limpiarPantalla() ;
  imprimirSeparador("Por favor, ingrese la ruta donde se ubica el archivo de canciones:") ;
  puts("Si trabaja con el repositorio, puede usar la ruta \"Data/song_dataset_.csv\"\n") ;
  printf("Ingrese la ruta del archivo con canciones, sin comillas: ") ;
  //-----------------//
  char buffer[100] ;
  leerEntrada(buffer) ;
  FILE* archivoCSV = fopen(buffer, "r") ;
  if (archivoCSV == NULL) { perror("La ruta proporcionada no es válida") ; return ; }
  //--- IMPRESIÓN ---//
  limpiarPantalla() ;
  imprimirSeparador("Se cargarán las primeras 10.000 canciones. ¿Desea seguir? [SI/NO]") ;
  leerOpcion(buffer) ;
  if (*buffer == '\0') puts("Introduzca una opción válida.") ;
  else if ((*buffer != 'S' && *buffer != 's') || *buffer == '0') return ;
  limpiarPantalla() ;
  imprimirSeparador("Cargando canciones...") ;
  imprimirGato() ;
  //-----------------//
  
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
    //--- IMPRESIÓN ---//
    puts("SE CARGARON LAS PRIMERAS 10.000 CANCIONES.") ;
    esperarEnter() ;
    limpiarPantalla() ;
    imprimirSeparador("¿Desea leer todas las canciones disponibles? [S/N]") ;
    puts("Si acepta, cargará todas las canciones disponibles (puede tardar un rato).") ;
    puts("Si no, estarán cargadas las primeras 10.000 canciones.") ;
    //-----------------//
    leerOpcion(buffer) ;
    limpiarPantalla() ;
    if ((*buffer != 'S' && *buffer != 's') || *buffer == '0') { 
      imprimirSeparador("¡Se han cargado las primeras 10.000 canciones!") ;
      return ;
    }
    imprimirSeparador("Cargando canciones...") ;
    imprimirGato() ;

    while ((completo = leerLineaCSV(archivoCSV, ',')) != NULL) cargarCanciones(completo, MapaCanciones) ;
    //-----------------//
    limpiarPantalla() ;
    imprimirSeparador("SE HAN CARGADO TODAS LAS CANCIONES DISPONIBLES.") ;
  }
  //---//
  fclose(archivoCSV) ;
  return ;
}

void music_buscarPorGenero(Map* mapa) {
  MapPair* pair = map_search(mapa, "Genero") ; // Toma el mapa "Global" y asigna el pair al mapa género.
  music_buscarPorFiltro(pair->value, "Ingrese el género a buscar:") ; // Toma el mapa de géneros y pide buscar.
}

void music_buscarPorArtista(Map* mapa) { 
  MapPair* pair = map_search(mapa, "Artistas") ; // Del mapa "Global", asigna el pair al mapa de artistas.
  music_buscarPorFiltro(pair->value, "Ingrese el artista a buscar:") ; // Se toma el mapa de artistas y se pide buscar.
}

void music_buscarPorTempo(Map* mapa) { 
  es_tempo = '1' ; // Se asigna la variable global es_tempo como '1' (Significa que sí es tempo).
  MapPair* pair = map_search(mapa, "Tempo") ; // Se toma el mapa de tempos en el mapa "Global".
  music_buscarPorFiltro(pair->value, "Ingrese la velocidad (tempo) a buscar") ; // Se toma el mapa de tempos, y se pide buscar por la velocidad ingresada.
}