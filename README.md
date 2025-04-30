# **Spotifind**
---
### Descripción

### Funciones del programa
El programa incluye **4 funciones principales** con las que opera.
1. `Cargar Canciones`: Permite que el usuario ingrese una ruta (``"C:/..."``, ``"\home\..."``) dentro del programa que contenga el archivo de canciones a utilizar (el proporcionado). Da la opción de ingresar la ruta proporcionada por el repositorio, pero permite elegir **cualquier ruta y nombre** en el archivo.
2. `Buscar por Género`:

#### Problemas y errores

- Al momento de `leer una opción`, el programa leerá el **primer cáracter ingresado**. Si se **agregan más carácteres** después de eso no se considerará como un "problema", pero **tampoco se leerán**.
- Si se **supera** el límite de la entrada del usuario (**200 carácteres máximo**), el programa no podrá interpretar más allá de lo que se ingrese.
- Después de usar la función de `Cargar Canciones`, no se podrá leer nuevamente la entrada (para poder por ejemplo cargar las canciones restantes si la opción utilizada es la de cargar las primeras 10.000).
- Hay ciertos **carácteres especiales** pertenecientes a un formato distinto de ASCII que no son mostrados correctamente dentro del programa.