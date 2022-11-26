#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>



int main() {
   int fd;
   fd = open("prueba.txt", O_RDWR | O_CREAT,00645);

   if(fd == -1){
    perror("Error al abrir o crear fichero: ");
    return -1;
   }
   close(fd);
    return 0;
   
}

