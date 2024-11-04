#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// cuando haces control C
void manejar_sigint(int senial) {
    printf("\nPrograma finalizado.\n");
    exit(0); 
}

int main() {
    int segundos = 0;
    if (signal(SIGINT, manejar_sigint) == SIG_ERR) {
        fprintf(stderr, "Error al registrar el manejador de señal.\n");
        return 1; 
    }
    
    // Bucle infinito
    while (1) {
        segundos += 5; 
        printf("Han transcurrido: %d segundos\n", segundos); // Mostrar el tiempo transcurrido
        
        sleep(5); // Esperar 5 segundos
    }
    return 0; 
}
