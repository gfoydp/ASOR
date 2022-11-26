#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>



int main(int argc, char ** argv) {

    int fd;

    if (argc != 2) {
		printf("Usage: ./ejercicio13 <file>\n");
		return -1;
	}

    if((fd = open(argv[1], O_RDWR | O_CREAT, 0644)) == -1){
        perror("Error al abrir el fichero");
    }

    if(dup2(fd,1)==-1){
        perror("Error al redirigir la salida estandar: ");
        return -1;
    }
    if(dup2(fd,2)==-1){
        perror("Error al redirigir la salida de error: ");
        return -1;
    }


   printf("Prueba de salida estandar\n");
   fprintf(stderr,"Prueba salida de error \n");

   close(fd);

    return 0;
   
}

