#include <stdio.h>
#include <unistd.h>




int main() {

    printf("Numero maximo de argumentos: %ld \n", pathconf("/home/cursoredes/Desktop/P1/ASOR/",_PC_LINK_MAX));
    printf("Numero maximo de hijos: %ld \n", pathconf("/home/cursoredes/Desktop/P1/ASOR/",_PC_PATH_MAX));
    printf("Numero maximo de archivos abiertos: %ld \n", pathconf("/home/cursoredes/Desktop/P1/ASOR/",_PC_NAME_MAX));

   return 1;
}

