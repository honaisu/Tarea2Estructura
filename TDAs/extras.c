
void mostrarMenuPrincipal() {
    system("cls") ;
    imprimirSeparador("#================#", "Sistema de Tickets") ;

    puts("(1). Registrar ticket") ;
    puts("(2). Asignar prioridad") ;
    puts("(3). Mostrar lista de tickets") ;
    puts("(4). Procesar ticket") ;
    puts("(5). Buscar ticket") ;
    puts("(0). Salir") ;
}

void esperarEnter() {
    puts("Presione ENTER para continuar...") ;
    while (getchar() != '\n') ;
}

void imprimirSeparador(const char* sep, const char* string) {
    puts(sep) ;
    puts(string) ;
    puts(sep) ;
}

void limpiarPantalla() { system("cls") ; }