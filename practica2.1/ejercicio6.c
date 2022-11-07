#include <stdio.h>
#include <unistd.h>




int main() {

    long arg,child, files;
    if((arg = sysconf(_SC_ARG_MAX)) == -1){
        perror("Error al obtener el numero maximo de argumentos");
        return -1;
    }
    if((child = sysconf(_SC_CHILD_MAX)) == -1){
        perror("Error al obtener el numero maximo de hijos");
        return -1;
    }
    if((files = sysconf(_SC_OPEN_MAX)) == -1){
        perror("Error al obtener el numero maximo de archivos abiertos");
        return -1;
    }
    printf("Numero maximo de argumentos: %ld \n", arg);
    printf("Numero maximo de hijos: %ld \n", child);
    printf("Numero maximo de archivos abiertos: %ld \n", files);

   return 1;
}

