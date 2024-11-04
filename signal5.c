#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int fd[2];

void manejar_sigint(int senial) {
    //sin esto no funciona
}

void proceso_lector(int es_par) {
    close(fd[1]); // Cerrar el lado de escritura del pipe
    int num;
    while (1) {
        read(fd[0], &num, sizeof(int));
        if (num == 0) {
            exit(0);
        }
        if ((num % 2 == 0) == es_par) {
            printf("Número %s %d recibido por el proceso %s con pid %d\n", 
                   es_par ? "par" : "impar", num, es_par ? "P2" : "P3", getpid());
        }
    }
}

void finalizar_hijos(int sig) {
    int num = 0;
    write(fd[1], &num, sizeof(int)); // Enviar 0 a los hijos para que terminen
}

int main() {
    pid_t p2, p3;

    if (pipe(fd) == -1) {
        perror("Error al crear el pipe");
        exit(1);
    }

    if ((p2 = fork()) == 0) {
        signal(SIGINT, manejar_sigint); // Ignorar SIGINT en el proceso hijo
        proceso_lector(1); // Proceso P2 (números pares)
    } else if (p2 < 0) {
        perror("Error al crear el proceso P2");
        exit(1);
    }

    if ((p3 = fork()) == 0) {
        signal(SIGINT, manejar_sigint); // Ignorar SIGINT en el proceso hijo
        proceso_lector(0); // Proceso P3 (números impares)
    } else if (p3 < 0) {
        perror("Error al crear el proceso P3");
        exit(1);
    }

    signal(SIGINT, finalizar_hijos); 

    close(fd[0]); // Cerrar el lado de lectura del pipe en el proceso padre

    int num;
    while (1) {
        printf("Introduce número: ");
        scanf("%d", &num);
        write(fd[1], &num, sizeof(int));
        if (num == 0) {
            printf("Mandando señal de terminación al proceso hijo P2 con pid %d\n", p2);
            printf("Mandando señal de terminación al proceso hijo P3 con pid %d\n", p3);
            break;
        }
    }

    // Esperar a que terminen los hijos
    waitpid(p2, NULL, 0);
    waitpid(p3, NULL, 0);

    close(fd[1]); // Cerrar el lado de escritura del pipe

    printf("Fin proceso padre con pid %d\n", getpid());
    return 0;
}
