#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>



int main(int argc, char ** argv) {

    time_t t;
    char buffer[50];
    struct tm *lt;
    t = time(&t);
    int fd;

    if (argc != 2) {
		printf("Usage: ./ejercicio15 <file>\n");
		return -1;
	}

    if((lt=localtime(&t)) == NULL){
        perror("Error: ");
        return -1;
    }

    setlocale(LC_ALL,"es_ES");

    if(strftime(buffer,50,"%H:%M:%S",lt)==0){
        perror("Error: ");
        return -1;
    }


    if((fd = open(argv[1], O_RDWR | O_CREAT, 0644)) == -1){
        perror("Error al abrir el fichero");
    }

    if(lockf(fd,F_TLOCK,0)==-1){
        perror("Error al bloquear: ");
        return -1;
    }
    else {
		printf("Tiempo: %s\n", buffer);
		sleep(10);
		lockf(fd, F_ULOCK, 0);
        sleep(10);
    }



   close(fd);

    return 0;
   
}

