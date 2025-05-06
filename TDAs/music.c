#include "extras.h"
#include "music.h"
#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variable global que verifica si es que se han cargado las canciones.
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
  Song* nuevaCancion = (Song*) malloc(sizeof(Song)) ; // Asignar memoria a la cancion 
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
  // Categoría del Tempo (Lento, Moderado o Rápido).
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
  // Si es que el par es nulo (no existe un dato con esa clave):
  if (pair == NULL) { 
    lista = list_create() ; // Crea la lista y la inserta al mapa.
    map_insert(mapa, key, lista) ;
  } else {
    // Si existe una clave:
    // Hace que la lista sea igual al puntero del valor del par.
    // En otras palabras:
    // Entrega la dirección de memoria de la lista, del mapa, para usarla en la variable lista.
    lista = pair->value ; 
  }
  // Se busca el primer elemento de la lista.
  Song* existente = list_first(lista) ; 
  // Verifica si una ID se encuentra o no en la lista (evita duplicados).
  while (existente != NULL) {
      // Si la ID es la misma (ya está en la lista):
      if (strcmp(existente->id, cancion->id) == 0) { 
          return ; // No agregarla de nuevo.
      }
      // Ir recorriendo hasta llegar al último elemento de la lista.
      existente = list_next(lista) ;
  }
  // Agregar la canción a la lista.
  list_pushBack(lista, cancion) ;
}

// Carga los datos de una canción ubicada en una fila de la linea del archivo CSV.
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
  // Recorre la lista de artistas y los agrega individualmente
  char* artista = list_first(Cancion->artists) ;
  while (artista != NULL) {
    agregarAlMapa(pair->value, artista, Cancion) ;
    artista = list_next(Cancion->artists) ;
  }

  //--- LISTA TEMPO ---//
  pair = map_search(Mapa, "Tempo") ;
  agregarAlMapa(pair->value, Cancion->categoriaTempo, Cancion) ;
}

// Devuelve un elemento del mapa (la canción).
// Es el sistema de búsqueda en el mapa que los "filtros" ocupan.
MapPair* devolverPairFiltro(Map* Mapa) {
  //---//
  MapPair* pair ;
  // Entrada del usuario.
  char filtro[200] ;
  printf("Ingrese su opción: ") ;
  leerEntrada(filtro) ;
  //---//

  // Si lo que se busca es por tempo:
  if (es_tempo == '1') {
    // Convierte el filtro a un valor numérico.
    float tempo = strtof(filtro, NULL) ;
    if (!tempo) return NULL ;
    // Que se devuelve en base a las categorías del tempo (Lento, Moderado, Rápido).
    convertir(tempo, filtro) ;
  }
  //---//
  return map_search(Mapa, filtro) ;
}

// La función que hace las búsquedas de lo que el usuario ingrese.
void music_buscarPorFiltro(Map* Mapa, const char* str) {
  if (verificar_cargado == '0') { puts("NO HAY CANCIONES CARGADAS.") ; return ; }
  //---//
  limpiarPantalla() ;
  imprimirSeparador(str) ;
  //---//

  // Obtiene un pair válido (valor lista) para poder imprimir las canciones.
  MapPair* pair = devolverPairFiltro(Mapa) ;
  if (pair == NULL) { puts("NO SE ENCONTRÓ EL DATO A BUSCAR") ; return ; }
  //---//
  int contadorCanciones = 0 ;
  char opcion[10] ;
  Song* cancion = list_first(pair->value) ;
  // Recorre hasta que no hayan más canciones.
  while (cancion != NULL) {
    imprimirDatosCanciones(cancion) ;
    // Pero, si llega a 10 canciones, le pregunta al usuario si quiere mostrar más.
    if (contadorCanciones == 10 && cancion != NULL) {
      putchar('\n') ;
      imprimirSeparador("¿Desea ver más canciones? [S/N]") ;
      leerOpcion(opcion) ;
      // Si acepta, seguirá recorriendo hasta que no hayan canciones.
      if (*opcion == 'S' || *opcion == 's' || *opcion == '1') contadorCanciones = 0 ;
      else { 
        // Si no, termina la función.
        puts("Se cargaron las canciones deseadas!") ; 
        break ;
      }
    }

    contadorCanciones++ ;
    cancion = list_next(pair->value) ;
  }
  //---//
  
  // Si se llega a una posición NULL (final de la lista).
  if (cancion == NULL) {
    putchar('\n') ;
    imprimirSeparador("¡Llegó al final de la lista!") ;
  }

  // Devuelve la variable 'es_tempo' a '0' (para volver a verificar).
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
  imprimirSeparador("Se cargarán las primeras 10.000 canciones. ¿Desea seguir? [S/N]") ;
  leerOpcion(buffer) ;
  if (*buffer == '\0') puts("Introduzca una opción válida.") ;
  else if ((*buffer != 'S' && *buffer != 's' && *buffer != '1') || *buffer == '0') return ;
  limpiarPantalla() ;
  imprimirSeparador("Cargando canciones...") ;
  imprimirGato() ;
  //-----------------//
  
  int i = 0 ;
  //---//
  char** completo = leerLineaCSV(archivoCSV, ',') ;
  // Lee canciones hasta que el 'i' sea menor a 10.000
  while (i < 10000 && (completo = leerLineaCSV(archivoCSV, ',')) != NULL) {
    cargarCanciones(completo, MapaCanciones) ;
    i++ ;
  }
  //---//
  // Si el 'i' es igual a 10.000, verifica el cargado.
  // Le pregunta, también, al usuario si quiere cargar más canciones o no.
  if (i == 10000) {
    // Confirma la carga de canciones.
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
    // Si la opción es NO, lee sólo las primeras 10.000 canciones.
    if ((*buffer != 'S' && *buffer != 's') || *buffer == '0') { 
      imprimirSeparador("¡Se han cargado las primeras 10.000 canciones!") ;
      return ;
    }
    // Si no, lee las canciones que queden.
    imprimirSeparador("Cargando canciones...") ;
    imprimirGato() ;

    // Termina de leer todas las canciones.
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
  // Toma el mapa "Global" y asigna el pair al mapa género.
  MapPair* pair = map_search(mapa, "Genero") ;
  // Toma el mapa de géneros y pide buscar.
  music_buscarPorFiltro(pair->value, "Ingrese el género a buscar:") ; 
}

void music_buscarPorArtista(Map* mapa) { 
  // Del mapa "Global", asigna el pair al mapa de artistas.
  MapPair* pair = map_search(mapa, "Artistas") ; 
  // Se toma el mapa de artistas y se pide buscar.
  music_buscarPorFiltro(pair->value, "Ingrese el artista a buscar:") ; 
}

void music_buscarPorTempo(Map* mapa) { 
  // Se asigna la variable global 'es_tempo' como '1' (significa que sí es tempo).
  es_tempo = '1' ; 
  // Se toma el mapa de tempos en el mapa "Global".
  MapPair* pair = map_search(mapa, "Tempo") ; 
  // Se toma el mapa de tempos, y se pide buscar por la velocidad ingresada.
  music_buscarPorFiltro(pair->value, "Ingrese la velocidad (tempo) a buscar (valor numérico):") ; 
}