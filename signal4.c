#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

//mis variables
int alarmas_a_sonar = 0; 
int intervalo = 0; 
int contador = 0; 
volatile sig_atomic_t alarma_activada = 0; 


void imprimir_hora() {
    time_t tiempo_actual;
    struct tm *info_tiempo;
    char buffer[9]; 

    time(&tiempo_actual);
    info_tiempo = localtime(&tiempo_actual);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", info_tiempo);//para que solo vea la hora 
    printf("Señal de alarma recibida a las: %s\n", buffer); 
}

void manejar_alarma(int senial) {
    if (contador < alarmas_a_sonar) {
        imprimir_hora(); 
        contador++; 
    } else {
        alarma_activada = 0;
    }
}


void manejar_sigint(int senial) {
    printf("\nAlarma desactivada\n");
    exit(0); 
}

int main() {
    printf("¿Cuántas veces sonará la alarma?: ");
    scanf("%d", &alarmas_a_sonar);
    
    printf("¿Cada cuántos segundos se repetirá la alarma?: ");
    scanf("%d", &intervalo);

    signal(SIGINT, manejar_sigint);
    signal(SIGALRM, manejar_alarma); 

    alarma_activada = 1; 
    printf("Alarma activada\n");

    alarm(intervalo); 
    while (alarma_activada) {
        pause(); 
        if (contador < alarmas_a_sonar) {
            alarm(intervalo); 
        }
    }

    return 0; 
}
