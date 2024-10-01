#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("CCC \n");
    
    pid_t pid = fork();
    
    if (pid > 0) {
        wait(NULL);
        printf("AAA \n");
    } 
    else if (pid == 0) {
        printf("BBB \n");
    } 
    else {
        perror("Fork fallido");
        exit(1);
    }
    exit(0);
}

