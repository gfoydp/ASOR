#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>




int main(int argc, char** argv) {

	fd_set set;

    int pipe1 = open("pipe",O_RDONLY | O_NONBLOCK);
    int pipe2 = open("pipe2",O_RDONLY |O_NONBLOCK);
    int bytes;
    int pmax;
    char buffer[256];

    if(pipe1 == -1){
    perror("Error al abrir pipe: ");
    return -1;
   }

   if(pipe2 == -1){
    perror("Error al abrir pipe2: ");
    return -1;
   }

   if(pipe1>pipe2) pmax = pipe1;
   else pmax = pipe2;

   FD_ZERO(&set);
   FD_SET(pipe1,&set);
   FD_SET(pipe2,&set);

   if((select(pmax + 1,&set,NULL,NULL,NULL)) == -1){
        perror("Error al realizar select: ");
        return -1;
   }

    if (FD_ISSET(pipe1, &set)) {
			bytes = read(pipe1, buffer, 256);
            if(bytes == 0){
            close(pipe1);
			pipe1 = open("pipe", O_RDONLY | O_NONBLOCK);
            }
			buffer[bytes] = '\0';
			printf("Leyendo de pipe2: %s", buffer);
		}
	else {
			bytes = read(pipe2, buffer, 256);
            if(bytes == 0){
            close(pipe2);
			pipe2 = open("pipe2", O_RDONLY | O_NONBLOCK);
            }
			buffer[bytes] = '\0';
			printf("Leyendo de pipe2: %s", buffer);
		}
   
    close(pipe1);
    close(pipe2);

    return 0;
   
}

