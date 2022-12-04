#include <stdio.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char** argv) {

    int fd[2];

    if(pipe(fd) == -1){
    perror("Error al crear el pipe: ");
    return -1;
   }
    pid_t pid;

    pid = fork();

   if(pid == -1){
    perror("Error al realizar fork: ");
    return -1;
   }
    else if(pid == 0){
        if(dup2(fd[0],0) == -1){
        perror("Error al redirigir la entrada estandar: ");
        return -1;
        }
    close(fd[0]);
    close(fd[1]);
        if(execlp(argv[3], argv[3], argv[4], NULL) == -1){
        perror("Error al ejecutar el comando: ");
        return -1;
        }
   }
   else {
       if(dup2(fd[1],1) == -1){
        perror("Error al redirigir la salida estandar: ");
        return -1;
        }
    close(fd[0]);
    close(fd[1]);
        if(execlp(argv[1], argv[1], argv[2], NULL) == -1){
        perror("Error al ejecutar el comando: ");
        return -1;
        }
   }
   
    return 0;
   
}

