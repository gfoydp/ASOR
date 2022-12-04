#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(int argc, char** argv) {

     if(argc != 2) {
    fprintf(stderr, "Usage: %s <arg>",argv[0]);
    }

    int fd = open("pipe",O_WRONLY);
   
    if(fd == -1){
    perror("Error al abrir pipe: ");
    return -1;
   }

   if((write(fd,argv[1],strlen(argv[1]) + 1)) == -1){
    perror("Error al escribir en pipe: ");
    return -1;
   }


    return 0;
   
}

