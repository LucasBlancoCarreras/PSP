#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
     pid_t
  

  pid = fork();
  

  
  if(pid==0){

printf("Lucas\n");			 
exit(0);  
  			}
   else{ 			
 
wait(NULL);
  printf("PID del proceso hijo: %d\n", pid);
    printf("PID del proceso padre: %d\n", getpid());

  			}
return 0;

}
