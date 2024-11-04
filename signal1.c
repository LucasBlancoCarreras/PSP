#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

// Función para mostrar la fecha
void imprimir_fecha_hora() {
    time_t tiempo_actual;
    time(&tiempo_actual);
    printf("%s", ctime(&tiempo_actual));
}

void manejar_sigint(int senial) {
    printf("\nPrograma finalizado: ");
    imprimir_fecha_hora();
    exit(0); 
}

int main() {
    signal(SIGINT, manejar_sigint);

    printf("Proceso iniciado: ");
    imprimir_fecha_hora();
    // Bucle infinito para mantener el programa en ejecución
    //control C para terminar el programa
    while (1) {
        sleep(1); 
    }

    return 0; // aqui nunca llega
}
