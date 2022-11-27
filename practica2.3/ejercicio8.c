#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




int main(int argc, char **argv) {
    pid_t p;

    if (argc < 2) {
		fprintf(stderr, "Usage: %s <command>\n",argv[0]);
		return -1;
	}


    p = fork();

    if(p == -1){
        perror("Error al crear hijo");

    }
    else if(p == 0){

        int fd1 = open("/tmp/daemon.out", O_CREAT | O_RDWR | O_APPEND );
        if(fd1==-1){
            perror("Error al crear o abrir daemon.out ");
            return -1;
        }
        int fd2 = open("/tmp/daemon.err", O_CREAT | O_RDWR | O_APPEND );
        if(fd2==-1){
            perror("Error al crear o abrir daemon.err ");
            return -1;
        }
        int fd3 = open("/dev/null", O_CREAT | O_RDONLY  | O_APPEND );
        if(fd2==-1){
            perror("Error al crear o abrir daemon.err ");
            return -1;
        }

        if(dup2(fd1,1)== -1){
             perror("Error al redirigir la salida estandar ");
            return -1;
        }
        if(dup2(fd2,2)== -1){
             perror("Error al redirigir la salida de error ");
            return -1;
        }
        if(dup2(fd3,0)== -1){
             perror("Error al redirigir la entrada estandar ");
            return -1;
        }


        if(setsid()==-1){
            perror("Error al crear sesion ");
            return -1;
        }

        if(chdir("/tmp")==-1){
            perror("Error al cambiar la ruta ");
            return -1;
        }

        if(execvp(argv[1],&argv[1])== -1){
        perror("Error al ejecutar execvp ");
        return -1;
    }
        

    }
    else{
        sleep(3);
    }
   


    return 0;
   
}

