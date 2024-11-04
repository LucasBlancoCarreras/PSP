#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

const char *nombre_archivo = "salidas.txt"; 

void imprimir_hora(FILE *archivo) {
    time_t tiempo_actual;
    time(&tiempo_actual); 
    struct tm *info_tiempo = localtime(&tiempo_actual); 
    //formateo para que solo salga la hora
    fprintf(archivo, "Hora: %02d:%02d:%02d\n", info_tiempo->tm_hour, info_tiempo->tm_min, info_tiempo->tm_sec);
    printf(" %02d:%02d:%02d\n", info_tiempo->tm_hour, info_tiempo->tm_min, info_tiempo->tm_sec); // Imprimir la hora
}


void manejar_sigint(int senial) {
    FILE *archivo = fopen(nombre_archivo, "a"); 
    if (archivo != NULL) {
        fprintf(archivo, "Señal SIGINT recibida a las: ");
        imprimir_hora(archivo); 
        fclose(archivo); 
    } else {
        perror("Error al abrir el archivo"); 
    }
}

int main() {
    signal(SIGINT, manejar_sigint);
    printf("Proceso iniciado a las: ");
    FILE *archivo = fopen(nombre_archivo, "a"); 
    if (archivo != NULL) {
        imprimir_hora(archivo); 
        fclose(archivo); 
    } else {
        perror("Error al abrir el archivo"); 
    }
    // Bucle infinito para mantener el programa en ejecución
    while (1) {
        sleep(1); 
    }

    return 0; // Este retorno nunca se alcanzará
}
