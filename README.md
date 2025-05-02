# **Spotifind**
---
### Descripción
**Spotifind** es una herramienta que permite **cargar una base de datos** de canciones, a partir de una ruta especificada por el usuario, y **mostrar los datos de las canciones**, ubicadas dentro, a través de una **búsqueda por filtros** (`Género`, `Artista` y `Tempo`).

### Compilación y ejecución

Para compilarlo, dentro del sistema operativo **Windows**, es necesario:
1. Descargar este **repositorio** como archivo `zip` (haciendo **click** en la sección `code`, y apretando el botón de `Descargar ZIP`).
2. Abrir el **explorador de archivos** y navegar hasta el archivo `zip` para descomprimirlo. Una vez descomprimido, abrir el directorio con los archivos del programa.
3. Abrir el archivo `main.c` del `zip` en **Visual Studio Code**.
4. Dentro de **Visual Studio Code**, abrir el **terminal** y dirigirse a la dirección del repositorio, para poder compilar el programa.
5. Ejecutar el siguiente comando: `gcc TDAs/*.c *.c -o programa.exe`.
6. Abrir el archivo `programa.exe`, o escribir la línea `./programa.exe` en **Visual Studio Code** para ejecutarlo.

Una forma alternativa de compilación, dentro de **Windows**, sería:
1. Descargar el **repositorio** como archivo `zip`.
2. Abrir el **explorador de archivos** y navegar hasta encontrar el archivo `zip` para descomprimirlo.
3. En **Windows 11**, una vez descomprimido, hacer **click derecho** en el directorio para abrir el menú de opciones y seleccionar para **abrir en Terminal**. Alternativamente, abrir **PowerShell** o **Línea de Comandos**, copiar la dirección del repositorio (la ruta `C:\Users\...`) y ejecutar el comando `cd "C:\Users\..."`.
4. Ejecutar el comando: `gcc TDAs/*.c *.c -o programa.exe`.
5. Abrir el archivo `programa.exe` o escribir en la misma **terminal** el comando `./programa.exe` para ejecutarlo (si lo permite).


### Funciones del programa
El programa incluye **2 funciones principales** con las que opera.
1. `Cargar Canciones`: Permite que el usuario ingrese una ruta (``"C:/..."``, ``"\home\..."``) dentro del programa que contenga el archivo de canciones a utilizar (el proporcionado) en formato CSV. Da la opción de ingresar la ruta proporcionada por el repositorio, pero permite elegir **cualquier ruta y nombre** en el archivo (mientras sea válido).
2. `Buscar por "filtro"`: El programa permite la búsqueda de ciertos tipos de datos específicos ubicados dentro del archivo de canciones, retornando una lista de diez canciones por *default*, y dando la posibilidad de ir cargando más canciones hasta poder llegar al final de la lista. El formato de las canciones siempre mostrará el **ID**, **Artistas involucrados**, y **Nombre**, **Álbum** y **Velocidad (Tempo)** de la canción. Se otorgan las siguientes búsquedas dentro del programa, siendo:
    - `Buscar por Género`: Permite ingresar **un género a buscar** (en minúsculas). Tomará todas las canciones con ese género aplicado y lo mostrará en pantalla. Algunos ejemplos son: `acoustic`, `anime` o `brazil`.
    - `Buscar por Artista`: Permite ingresar el **artista que se desea buscar**. Encontrará y mostrará todas las canciones en las que ese artista haya estado involucrado. Algunos ejemplos son: `Kurt Cobain`.
    - `Buscar por Tempo`: Permite ingresar un tempo (velocidad), catalogada en ciertos rangos que definirán las canciones que se buscarán. Los tempos que sean **menores a 80 BPM** serán catalogados como **lentos**; los que **estén entre 80 BPM y 120 BPM** serán **moderados**; y si son **mayores a 120 BPM** serán **rápidos**. Sólo se necesita ingresar la velocidad para la búsqueda, **sin los BPM**.

#### Problemas y errores

- Al momento de `leer una opción`, el programa leerá el **primer cáracter ingresado**. Si se **agregan más carácteres** después de eso no se considerará como un "problema", pero **tampoco se leerán**.
- Si se **supera** el límite de la entrada del usuario (**200 carácteres máximo**), el programa no podrá interpretar más allá de lo que se ingrese.
- Después de usar la función de `Cargar Canciones`, no se podrá leer nuevamente la entrada (para poder por ejemplo cargar las canciones restantes si la opción utilizada es la de cargar las primeras 10.000).
- Hay ciertos **carácteres especiales** pertenecientes a un formato distinto de ASCII que no son mostrados correctamente dentro del programa.