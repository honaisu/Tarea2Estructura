# **Spotifind**
---
### Descripción
**Spotifind** es una herramienta que permite **cargar una base de datos** de canciones, a partir de una ruta especificada por el usuario, y **mostrar los datos de las canciones**, ubicadas dentro, a través de una **búsqueda por filtros** (`Género`, `Artista` y `Tempo`).

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