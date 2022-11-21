#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>



int main(int argc, char ** argv) {

    int fd;

    if((fd = open(argv[1], O_RDWR | O_CREAT, 0644)) == -1){
        perror("Error al abrir el fichero");
    }

    if(dup2(fd,1)==-1){
        perror("Error: ");
        return -1;
    }


   printf("Hola esto es una \n");
   printf("PRUEBA \n");

   close(fd);

    return 0;
   
}

